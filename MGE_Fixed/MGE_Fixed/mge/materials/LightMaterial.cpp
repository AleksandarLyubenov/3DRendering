#include "../../glm.hpp"
#include "LightMaterial.hpp"
#include "../core/Texture.hpp"
#include "../core/Light.hpp"
#include "../core/World.hpp"
#include "../core/Mesh.hpp"
#include "../core/GameObject.hpp"
#include "../core/ShaderProgram.hpp"
#include "../config.hpp"
#include "../core/Camera.hpp"


ShaderProgram* LightMaterial::_shader = nullptr;

// Uniform locations
GLint LightMaterial::_uMVPMatrix = 0;
GLint LightMaterial::_uDiffuseTexture = 0;
GLint LightMaterial::_uAmbientLightColor = 0;
GLint LightMaterial::_uAmbientIntensity = 0;
GLint LightMaterial::_uLightPosition = 0;
GLint LightMaterial::_uDiffuseColor = 0;
GLint LightMaterial::_uLightColor = 0;

// Attribute locations
GLint LightMaterial::_aVertex = 0;
GLint LightMaterial::_aNormal = 0;
GLint LightMaterial::_aUV = 0;

LightMaterial::LightMaterial(Texture* pDiffuseTexture)
    : _diffuseTexture(pDiffuseTexture) {
    _lazyInitializeShader();
}

LightMaterial::~LightMaterial() {}

void LightMaterial::_lazyInitializeShader() {
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "light.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "light.fs");
        _shader->finalize();

        _uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
        _uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");
        _uAmbientLightColor = _shader->getUniformLocation("ambientLightColor");
        _uAmbientIntensity = _shader->getUniformLocation("ambientIntensity");
        _uLightPosition = _shader->getUniformLocation("lightPosition");
        _uDiffuseColor = _shader->getUniformLocation("diffuseColor");

        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV = _shader->getAttribLocation("uv");
        _uLightColor = _shader->getUniformLocation("lightColor");
    }
}

void LightMaterial::setDiffuseTexture(Texture* pDiffuseTexture) {
    _diffuseTexture = pDiffuseTexture;
}

void LightMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
    if (!_diffuseTexture) return;

    _shader->use(); // Without this it doesn't work

    // Diffuse
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
    glUniform1i(_uDiffuseTexture, 0);

    // Ambient
    glm::vec3 ambientLightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    float ambientIntensity = 0.5f;
    glUniform3fv(_uAmbientLightColor, 1, glm::value_ptr(ambientLightColor));
    glUniform1f(_uAmbientIntensity, ambientIntensity);

    if (pWorld->getLightCount() > 0) {
        Light* light = dynamic_cast<Light*>(pWorld->getLightAt(0));

        if (light) {
            glUniform1f(glGetUniformLocation(_shader->getProgramId(), "c1"), light->getConstantAttenuation());
            glUniform1f(glGetUniformLocation(_shader->getProgramId(), "c2"), light->getLinearAttenuation());
            glUniform1f(glGetUniformLocation(_shader->getProgramId(), "c3"), light->getQuadraticAttenuation());
            //glUniform1f(glGetUniformLocation(_shader->getProgramId(), "lightColor"), light->getLightColor());
        }

        glm::vec3 lightPosition = light->getWorldPosition();
        glm::vec3 lightColor = glm::vec3(1.0f, 0.0f, 1.0f);
        glm::vec3 specularColor = glm::vec3(1.0f, 1.0f, 1.0f);

        glUniform3fv(_uLightPosition, 1, glm::value_ptr(lightPosition));
        glUniform3fv(_uDiffuseColor, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
        glUniform3fv(_uLightColor, 1, glm::value_ptr(lightColor));
        glUniform3fv(glGetUniformLocation(_shader->getProgramId(), "specularColor"), 1, glm::value_ptr(specularColor));

        // Camera position
        glm::vec3 cameraPosition = pWorld->getMainCamera()->getWorldPosition();
        glUniform3fv(glGetUniformLocation(_shader->getProgramId(), "cameraPosition"), 1, glm::value_ptr(cameraPosition));

        // Shininess
        float shininess = 4.0f;
        glUniform1f(glGetUniformLocation(_shader->getProgramId(), "shininess"), shininess);

        // Attenuation (OLD)
        //glUniform1f(glGetUniformLocation(_shader->getProgramId(), "c1"), 1.0f);  // Constant
        //glUniform1f(glGetUniformLocation(_shader->getProgramId(), "c2"), 0.09f); // Linear
        //glUniform1f(glGetUniformLocation(_shader->getProgramId(), "c3"), 0.032f); // Quadratic
    }

    // Set MVP matrix
    glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
    glm::mat4 modelMatrix = pModelMatrix;
    glUniformMatrix4fv(_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
    glUniformMatrix4fv(glGetUniformLocation(_shader->getProgramId(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Stream data to OpenGL
    pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}



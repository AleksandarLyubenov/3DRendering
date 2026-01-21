#include "glm.hpp"
#include "MultipleLightMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"
#include "mge/core/Camera.hpp"

// Initialize the static shader pointer
ShaderProgram* MultipleLightMaterial::_shader = nullptr;

// Uniform locations
GLint MultipleLightMaterial::_uMVPMatrix = 0;
GLint MultipleLightMaterial::_uDiffuseTexture = 0;
GLint MultipleLightMaterial::_uAmbientLightColor = 0;
GLint MultipleLightMaterial::_uAmbientIntensity = 0;
GLint MultipleLightMaterial::_uLightPosition = 0;
GLint MultipleLightMaterial::_uLightColor = 0;

// Attribute locations
GLint MultipleLightMaterial::_aVertex = 0;
GLint MultipleLightMaterial::_aNormal = 0;
GLint MultipleLightMaterial::_aUV = 0;

MultipleLightMaterial::MultipleLightMaterial(Texture* pDiffuseTexture)
    : _diffuseTexture(pDiffuseTexture) {
    _lazyInitializeShader();
}

MultipleLightMaterial::~MultipleLightMaterial() {}

void MultipleLightMaterial::_lazyInitializeShader() {
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "light.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "light.fs");
        _shader->finalize();

        // Get uniform locations
        _uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
        _uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");
        _uAmbientLightColor = _shader->getUniformLocation("ambientLightColor");
        _uAmbientIntensity = _shader->getUniformLocation("ambientIntensity");
        _uLightPosition = _shader->getUniformLocation("lightPositions");
        _uLightColor = _shader->getUniformLocation("lightColors");

        // Get attribute locations
        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV = _shader->getAttribLocation("uv");
    }
}

void MultipleLightMaterial::setDiffuseTexture(Texture* pDiffuseTexture) {
    _diffuseTexture = pDiffuseTexture;
}

void MultipleLightMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
    if (!_diffuseTexture) return;

    _shader->use();

    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
    glUniform1i(_uDiffuseTexture, 0);

    // Set ambient light
    glm::vec3 ambientLightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    float ambientIntensity = 0.5f;
    glUniform3fv(_uAmbientLightColor, 1, glm::value_ptr(ambientLightColor));
    glUniform1f(_uAmbientIntensity, ambientIntensity);

    // Prepare light data arrays
    const int maxLights = 10;
    glm::vec3 lightPositions[maxLights];
    glm::vec3 lightColors[maxLights];
    //int lightCount = std::min(pWorld->getLightCount(), maxLights);

    int lightCount = std::min(10, pWorld->getLightCount()); // Assuming a max of 10 lights
    glUniform1i(glGetUniformLocation(_shader->getProgramId(), "lightCount"), lightCount);
    for (int i = 0; i < lightCount; i++) {
        Light* light = dynamic_cast<Light*>(pWorld->getLightAt(i));
        glUniform3fv(glGetUniformLocation(_shader->getProgramId(), ("lightPositions[" + std::to_string(i) + "]").c_str()), 1, glm::value_ptr(light->getWorldPosition()));
        glUniform3fv(glGetUniformLocation(_shader->getProgramId(), ("lightColors[" + std::to_string(i) + "]").c_str()), 1, glm::value_ptr(light->getLightColor()));
    }

    // Send light data to the shader
    glUniform3fv(_uLightPosition, lightCount, glm::value_ptr(lightPositions[0]));
    glUniform3fv(_uLightColor, lightCount, glm::value_ptr(lightColors[0]));

    // Compute and send MVP matrix
    glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
    glUniformMatrix4fv(_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

    // Stream mesh data to OpenGL
    pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}

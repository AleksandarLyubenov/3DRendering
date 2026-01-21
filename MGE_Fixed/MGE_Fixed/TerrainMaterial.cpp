#include "TerrainMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/Mesh.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

TerrainMaterial::TerrainMaterial(Texture* heightMap, Texture* splatMap, Texture* diffuse1, Texture* diffuse2, Texture* diffuse3, Texture* diffuse4)
    : _heightMap(heightMap), _splatMap(splatMap), _diffuse1(diffuse1), _diffuse2(diffuse2), _diffuse3(diffuse3), _diffuse4(diffuse4) {
    _shader = new ShaderProgram();
    _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "terrainDeform.vs");
    _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "terrainDeform.fs");
    _shader->finalize();
}

TerrainMaterial::~TerrainMaterial() {
    delete _shader;
}

void TerrainMaterial::render(World* world, Mesh* mesh, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    _shader->use();
    glUniform3f(_shader->getUniformLocation("lightDirection"),
        _lightDirection.x, _lightDirection.y, _lightDirection.z);

    /*std::cout << "Light Direction: "
        << _lightDirection.x << ", "
        << _lightDirection.y << ", "
        << _lightDirection.z << std::endl;*/

    // Pass transformation matrices
    glUniformMatrix4fv(_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glUniform3f(_shader->getUniformLocation("lightDirection"), 1.0f, 0.0f, 1.0f);

    /*GLint loc = _shader->getUniformLocation("lightDirection");
    std::cout << "lightDirection Uniform Location: " << loc << std::endl;*/

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << err << std::endl;
    }

    glUniform3f(_shader->getUniformLocation("lightColor"), 1.0f, 1.0f, 1.0f);    // White light
    glUniform3f(_shader->getUniformLocation("ambientColor"), 0.2f, 0.2f, 0.2f); // Ambient light

    // Bind textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _heightMap->getId());
    glUniform1i(_shader->getUniformLocation("heightMap"), 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _splatMap->getId());
    glUniform1i(_shader->getUniformLocation("splatMap"), 1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, _diffuse1->getId());
    glUniform1i(_shader->getUniformLocation("diffuse1"), 2);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, _diffuse2->getId());
    glUniform1i(_shader->getUniformLocation("diffuse2"), 3);

    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, _diffuse3->getId());
    glUniform1i(_shader->getUniformLocation("diffuse3"), 4);

    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, _diffuse4->getId());
    glUniform1i(_shader->getUniformLocation("diffuse4"), 5);

    // Render the mesh
    mesh->streamToOpenGL(
        _shader->getAttribLocation("vertex"),
        _shader->getAttribLocation("normal"),
        _shader->getAttribLocation("uv")
    );
}

// HOLY MOTHER OF DEBUGGING UNIFORMS

//void TerrainMaterial::render(World* world, Mesh* mesh, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
//    _shader->use(); // Ensure the shader program is active
//
//    GLint lightDirLoc = _shader->getUniformLocation("lightDirection");
//    if (lightDirLoc != -1) {
//        std::cout << "Setting lightDirection: " << _lightDirection.x << ", "
//            << _lightDirection.y << ", " << _lightDirection.z << std::endl;
//        glUniform3f(lightDirLoc, _lightDirection.x, _lightDirection.y, _lightDirection.z);
//    }
//    else {
//        std::cerr << "Error: lightDirection uniform not found in shader!" << std::endl;
//    }
//
//    // Pass transformation matrices
//    glUniformMatrix4fv(_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
//    glUniformMatrix4fv(_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
//    glUniformMatrix4fv(_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
//
//    // Bind textures to respective texture units
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, _heightMap->getId());
//    glUniform1i(_shader->getUniformLocation("heightMap"), 0);
//
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, _splatMap->getId());
//    glUniform1i(_shader->getUniformLocation("splatMap"), 1);
//
//    glActiveTexture(GL_TEXTURE2);
//    glBindTexture(GL_TEXTURE_2D, _diffuse1->getId());
//    glUniform1i(_shader->getUniformLocation("diffuse1"), 2);
//
//    glActiveTexture(GL_TEXTURE3);
//    glBindTexture(GL_TEXTURE_2D, _diffuse2->getId());
//    glUniform1i(_shader->getUniformLocation("diffuse2"), 3);
//
//    glActiveTexture(GL_TEXTURE4);
//    glBindTexture(GL_TEXTURE_2D, _diffuse3->getId());
//    glUniform1i(_shader->getUniformLocation("diffuse3"), 4);
//
//    glActiveTexture(GL_TEXTURE5);
//    glBindTexture(GL_TEXTURE_2D, _diffuse4->getId());
//    glUniform1i(_shader->getUniformLocation("diffuse4"), 5);
//
//    // Pass lighting uniforms
//    glUniform3f(_shader->getUniformLocation("lightDirection"), _lightDirection.x, _lightDirection.y, _lightDirection.z);
//
//    GLenum err = glGetError();
//    if (err != GL_NO_ERROR) {
//        std::cerr << "OpenGL Error after setting lightDirection: " << err << std::endl;
//    }
//
//    glUniform3f(_shader->getUniformLocation("lightColor"), 1.0f, 1.0f, 1.0f);    // White light
//    glUniform3f(_shader->getUniformLocation("ambientColor"), 0.1f, 0.1f, 0.1f); // Ambient light
//
//    std::cout << "Light Direction: " << _lightDirection.x << ", " << _lightDirection.y << ", " << _lightDirection.z << std::endl;
//
//    // Render the mesh
//    mesh->streamToOpenGL(
//        _shader->getAttribLocation("vertex"),
//        _shader->getAttribLocation("normal"),
//        _shader->getAttribLocation("uv")
//    );
//}

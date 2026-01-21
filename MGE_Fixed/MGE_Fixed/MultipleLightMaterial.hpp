#ifndef MULTIPLELIGHTMATERIAL_HPP
#define MULTIPLELIGHTMATERIAL_HPP

#include <GL/glew.h>
#include "mge/materials/AbstractMaterial.hpp"

class ShaderProgram;
class Texture;

class MultipleLightMaterial : public AbstractMaterial
{
public:
    MultipleLightMaterial(Texture* pDiffuseTexture);
    virtual ~MultipleLightMaterial();

    virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

    void setDiffuseTexture(Texture* pDiffuseTexture);

private:
    static ShaderProgram* _shader;
    static void _lazyInitializeShader();

    // Uniform locations
    static GLint _uMVPMatrix;
    static GLint _uDiffuseTexture;
    static GLint _uAmbientLightColor;
    static GLint _uAmbientIntensity;
    static GLint _uLightPosition;
    static GLint _uDiffuseColor;
    static GLint _uLightColor;

    // Attribute locations
    static GLint _aVertex;
    static GLint _aNormal;
    static GLint _aUV;

    Texture* _diffuseTexture;

    MultipleLightMaterial(const MultipleLightMaterial&);
    MultipleLightMaterial& operator=(const MultipleLightMaterial&);
};

#endif // MULTIPLELIGHTMATERIAL_HPP

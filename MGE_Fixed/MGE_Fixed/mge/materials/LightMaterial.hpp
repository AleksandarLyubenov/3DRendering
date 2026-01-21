#ifndef LIGHTMATERIAL_HPP
#define LIGHTMATERIAL_HPP

#include <GL/glew.h>
#include "AbstractMaterial.hpp"

class ShaderProgram;
class Texture;

class LightMaterial : public AbstractMaterial
{
public:
    LightMaterial(Texture* pDiffuseTexture);
    virtual ~LightMaterial();

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

    LightMaterial(const LightMaterial&);
    LightMaterial& operator=(const LightMaterial&);
};

#endif // LIGHTMATERIAL_HPP

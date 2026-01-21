#ifndef TERRAINMATERIAL_HPP
#define TERRAINMATERIAL_HPP

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/ShaderProgram.hpp"

class TerrainMaterial : public AbstractMaterial {
public:
    TerrainMaterial(Texture* heightMap, Texture* splatMap, Texture* diffuse1, Texture* diffuse2, Texture* diffuse3, Texture* diffuse4);
    virtual ~TerrainMaterial();

    virtual void render(World* world, Mesh* mesh, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

    glm::vec3 _lightDirection;

private:
    ShaderProgram* _shader;
    Texture* _heightMap;
    Texture* _splatMap;
    Texture* _diffuse1;
    Texture* _diffuse2;
    Texture* _diffuse3;
    Texture* _diffuse4;
};

#endif // TERRAINMATERIAL_HPP

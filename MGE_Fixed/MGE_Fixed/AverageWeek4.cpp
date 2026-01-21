#include "AverageWeek4.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Camera.hpp"
#include "mge/materials/LightMaterial.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/config.hpp"
#include "TerrainMaterial.hpp"
#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Mesh.hpp"

AverageWeek4::AverageWeek4() : AbstractGame(), _cube(nullptr), _camera(nullptr) {}

AverageWeek4::~AverageWeek4() {}

void AverageWeek4::initialize() {
    AbstractGame::initialize();
    std::cout << "Initializing Average Week 4 Demo..." << std::endl;
}

void AverageWeek4::_initializeScene() {
    // Load the necessary textures
    Texture* heightMap = Texture::load(config::MGE_TERRAIN_PATH + "heightmap.png");
    Texture* heightMapTest = Texture::load(config::MGE_TERRAIN_PATH + "heightmap_test.png");

    Texture* splatMap = Texture::load(config::MGE_TERRAIN_PATH + "splatmap.png");
    Texture* diffuse1 = Texture::load(config::MGE_TERRAIN_PATH + "diffuse1.jpg");
    Texture* diffuse2 = Texture::load(config::MGE_TERRAIN_PATH + "diffuse2.jpg");
    Texture* diffuse3 = Texture::load(config::MGE_TERRAIN_PATH + "diffuse3.jpg");
    Texture* diffuse4 = Texture::load(config::MGE_TERRAIN_PATH + "diffuse4.jpg");

    TerrainMaterial* terrainMaterial = new TerrainMaterial(heightMap, splatMap, diffuse1, diffuse2, diffuse3, diffuse4);

    Mesh* terrainMesh = Mesh::load(config::MGE_MODEL_PATH + "plane20x20_million_tris.obj");

    GameObject* terrain = new GameObject("Terrain", glm::vec3(0, 0, 0));
    terrain->setMesh(terrainMesh);
    terrain->scale(glm::vec3(1, 1, 1));
    terrain->setMaterial(terrainMaterial);
    _world->add(terrain);

    _camera = new Camera("MainCamera", glm::vec3(0, 10, 20));
    _camera->rotate(glm::radians(-35.0f), glm::vec3(1, 0, 0));
    _world->add(_camera);
    _world->setMainCamera(_camera);

    _lightRotationAngle = 0.0f;
    _lightDirection = glm::vec3(1.0f, 1.0f, 1.0f);
    _lightRotationAngle = 0.0f;

    _terrain = terrain;

    terrain->setBehaviour(new RotatingBehaviour());
}


void AverageWeek4::_render() {
    //_lightRotationAngle += 0.01f; // Attempt at making the directional light rotate (way harder)

    //// Update light direction
    //_lightDirection = glm::normalize(glm::vec3(
    //    cos(_lightRotationAngle),
    //    -1.0f, // Light points downward
    //    sin(_lightRotationAngle)
    //));

    //std::cout << "Calculated Light Direction: "
    //    << _lightDirection.x << ", "
    //    << _lightDirection.y << ", "
    //    << _lightDirection.z << std::endl;

    AbstractGame::_render();
}




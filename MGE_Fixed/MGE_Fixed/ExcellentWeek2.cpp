#include "ExcellentWeek2.hpp"
#include "CameraOrbitBehaviour.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Camera.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/config.hpp"

ExcellentWeek2::ExcellentWeek2() : AbstractGame(), _cube(nullptr), _camera(nullptr) {}

ExcellentWeek2::~ExcellentWeek2() {}

void ExcellentWeek2::initialize() {
    AbstractGame::initialize();
    std::cout << "Initializing Excellent Week 2 Demo..." << std::endl;
}

void ExcellentWeek2::_initializeScene() {
    // Load meshes
    Mesh* planeMesh = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
    Mesh* cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
    Mesh* sphereMesh = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");
    Mesh* hastingsMesh = Mesh::load(config::MGE_MODEL_PATH + "hastings.obj");

    // Load textures
    Texture* planeTexture = Texture::load(config::MGE_TEXTURE_PATH + "land.jpg");
    Texture* cubeTexture = Texture::load(config::MGE_TEXTURE_PATH + "bricks.jpg");
    Texture* hastingsTexture = Texture::load(config::MGE_TEXTURE_PATH + "HastingsColorMap2.png");

    AbstractMaterial* planeMaterial = new TextureMaterial(planeTexture);
    AbstractMaterial* cubeMaterial = new TextureMaterial(cubeTexture);
    AbstractMaterial* lightMaterial = new ColorMaterial(glm::vec3(1, 1, 0)); // Yellow light
    AbstractMaterial* redMaterial = new ColorMaterial(glm::vec3(1, 0, 0));   // Red material

    AbstractMaterial* hastingsMaterial = new TextureMaterial(hastingsTexture);

    GameObject* floor = new GameObject("Floor", glm::vec3(0, 0, 0));
    floor->setMesh(planeMesh);
    floor->setMaterial(planeMaterial);
    floor->scale(glm::vec3(10, 1, 10));
    _world->add(floor);

    GameObject* immobileCube = new GameObject("Cube", glm::vec3(3, 1, 0));
    immobileCube->setMesh(cubeMesh);
    immobileCube->setMaterial(cubeMaterial);
    immobileCube->scale(glm::vec3(2, 2, 2));
    _world->add(immobileCube);

    _cube = new GameObject("Hastings", glm::vec3(0, 1, 0));
    _cube->setMesh(hastingsMesh);
    _cube->setMaterial(hastingsMaterial);
    _cube->scale(glm::vec3(1, 1, 1));
    _cube->setBehaviour(new KeysBehaviour(15));
    _world->add(_cube);

    _camera = new Camera("MainCamera", glm::vec3(0, 6, 10));
    CameraOrbitBehaviour* orbitBehaviour = new CameraOrbitBehaviour(_cube, 0.2f, 0.2f, 10.0f);
    orbitBehaviour->enableZoom(true); // Toggle zoom functionality
    _camera->setBehaviour(orbitBehaviour);
    _world->add(_camera);
    _world->setMainCamera(_camera);

    GameObject* light = new GameObject("Light", glm::vec3(0, 2.5, 0));
    light->setMesh(sphereMesh);
    light->setMaterial(lightMaterial);
    light->scale(glm::vec3(0.5, 0.5, 0.5));
    _cube->add(light); // Attach light to cube
}

void ExcellentWeek2::_render() {
    AbstractGame::_render();
}
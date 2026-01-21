#include "MediocreWeek2.hpp"
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

MediocreWeek2::MediocreWeek2() : AbstractGame(), _cube(nullptr), _camera(nullptr) {}

MediocreWeek2::~MediocreWeek2() {}

void MediocreWeek2::initialize() {
    AbstractGame::initialize();
    std::cout << "Initializing Mediocre Week 2 Demo..." << std::endl;
}

void MediocreWeek2::_initializeScene() {
    // Load meshes
    Mesh* planeMesh = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
    Mesh* cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
    Mesh* sphereMesh = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");

    // Load textures
    Texture* planeTexture = Texture::load(config::MGE_TEXTURE_PATH + "land.jpg");
    Texture* cubeTexture = Texture::load(config::MGE_TEXTURE_PATH + "bricks.jpg");

    AbstractMaterial* planeMaterial = new TextureMaterial(planeTexture);
    AbstractMaterial* cubeMaterial = new TextureMaterial(cubeTexture);
    AbstractMaterial* lightMaterial = new ColorMaterial(glm::vec3(1, 1, 0)); // Yellow light
    AbstractMaterial* redMaterial = new ColorMaterial(glm::vec3(1, 0, 0));   // Red material

    GameObject* floor = new GameObject("Floor", glm::vec3(0, 0, 0));
    floor->setMesh(planeMesh);
    floor->setMaterial(planeMaterial); // Grass Material
    floor->scale(glm::vec3(10, 1, 10));
    _world->add(floor);

    GameObject* immobileCube = new GameObject("Cube", glm::vec3(3, 1, 0));
    immobileCube->setMesh(cubeMesh);
    immobileCube->setMaterial(cubeMaterial); // Brick Material
    immobileCube->scale(glm::vec3(2, 2, 2));
    _world->add(immobileCube);

    _cube = new GameObject("MovableCube", glm::vec3(0, 1, 0));
    _cube->setMesh(cubeMesh);
    _cube->setMaterial(redMaterial); // Red colour material
    _cube->scale(glm::vec3(2, 2, 2));
    _cube->setBehaviour(new KeysBehaviour(15));
    _world->add(_cube);

    _camera = new Camera("MainCamera", glm::vec3(0, 6, 10));
    _camera->rotate(glm::radians(-30.0f), glm::vec3(1, 0, 0));
    _world->add(_camera);
    _world->setMainCamera(_camera);

    GameObject* light = new GameObject("Light", glm::vec3(0, 2.5, 0));
    light->setMesh(sphereMesh);
    light->setMaterial(lightMaterial); // Yellow colour material
    light->scale(glm::vec3(0.5, 0.5, 0.5));
    _cube->add(light); // Attach light to cube
}

void MediocreWeek2::_render() {
    AbstractGame::_render();

    // Update camera position to follow the cube
    if (_cube && _camera) {
        glm::vec3 cubePosition = _cube->getLocalPosition();
        glm::vec3 cameraOffset(0, 6, 10);
        glm::vec3 newCameraPosition = cubePosition + cameraOffset;

        _camera->setLocalPosition(newCameraPosition);
    }
}

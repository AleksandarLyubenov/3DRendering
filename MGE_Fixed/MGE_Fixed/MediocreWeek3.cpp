#include "MediocreWeek3.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Camera.hpp"
#include "mge/materials/LightMaterial.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/config.hpp"

MediocreWeek3::MediocreWeek3() : AbstractGame(), _cube(nullptr), _camera(nullptr) {}

MediocreWeek3::~MediocreWeek3() {}

void MediocreWeek3::initialize() {
    AbstractGame::initialize();
    std::cout << "Initializing Mediocre Week 3 Demo..." << std::endl;
}

void MediocreWeek3::_initializeScene() {
    // Load meshes
    Mesh* planeMesh = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
    Mesh* cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
    Mesh* sphereMesh = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");

    // Load textures
    Texture* planeTexture = Texture::load(config::MGE_TEXTURE_PATH + "land.jpg");
    Texture* cubeTexture = Texture::load(config::MGE_TEXTURE_PATH + "bricks.jpg");

    AbstractMaterial* planeMaterial = new LightMaterial(planeTexture);
    AbstractMaterial* cubeMaterial = new LightMaterial(cubeTexture);
    AbstractMaterial* lightMaterial = new LightMaterial(nullptr);

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

    _cube = new GameObject("MovableCube", glm::vec3(0, 1, 0));
    _cube->setMesh(cubeMesh);
    _cube->setMaterial(cubeMaterial);
    _cube->scale(glm::vec3(2, 2, 2));
    _cube->setBehaviour(new KeysBehaviour(15));
    _world->add(_cube);

    _camera = new Camera("MainCamera", glm::vec3(0, 6, 10));
    _camera->rotate(glm::radians(-45.0f), glm::vec3(1, 0, 0));
    //_world->add(_camera);
    _cube->add(_camera);
    _world->setMainCamera(_camera);
    

    /*GameObject* light = new GameObject("Light", glm::vec3(0, 2.5, 5));
    light->setMesh(sphereMesh);
    light->setMaterial(cubeMaterial);
    light->scale(glm::vec3(0.5, 0.5, 0.5));
    _world->add(light);*/

    // Register the light in the world
    Light* pointLight = new Light("PointLight", glm::vec3(0, 4.5, 5));
    pointLight->setConstantAttenuation(1.0f);
    pointLight->setLinearAttenuation(0.07f);
    pointLight->setQuadraticAttenuation(0.017f);
    //pointLight->setLightColor(glm::vec3(1.0f, 0.0f, 0.0f));
    _world->add(pointLight);

    //// Register the light in the world
    //Light* pointLightRed = new Light("PointLight", glm::vec3(-5, 2.5, 0));
    //_world->add(pointLight);
}

void MediocreWeek3::_render() {
    Light* pointLight = dynamic_cast<Light*>(_world->getLightAt(0));
    if (pointLight) {
        glm::vec3 updatedLightPosition = pointLight->getWorldPosition();
        // Update lighting dynamically
    }

    AbstractGame::_render();
}

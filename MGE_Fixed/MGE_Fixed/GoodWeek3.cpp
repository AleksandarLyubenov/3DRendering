#include "GoodWeek3.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Camera.hpp"
#include "MultipleLightMaterial.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/config.hpp"

GoodWeek3::GoodWeek3() : AbstractGame(), _cube(nullptr), _camera(nullptr) {}

GoodWeek3::~GoodWeek3() {}

void GoodWeek3::initialize() {
    AbstractGame::initialize();
    std::cout << "Initializing Mediocre Week 3 Demo..." << std::endl;
}

void GoodWeek3::_initializeScene() {
    // Load meshes
    Mesh* planeMesh = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
    Mesh* cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
    Mesh* sphereMesh = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");

    // Load textures
    Texture* planeTexture = Texture::load(config::MGE_TEXTURE_PATH + "land.jpg");
    Texture* cubeTexture = Texture::load(config::MGE_TEXTURE_PATH + "bricks.jpg");

    AbstractMaterial* planeMaterial = new MultipleLightMaterial(planeTexture);
    AbstractMaterial* cubeMaterial = new MultipleLightMaterial(cubeTexture);
    AbstractMaterial* lightMaterial = new MultipleLightMaterial(nullptr);

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
    _camera->rotate(glm::radians(-30.0f), glm::vec3(1, 0, 0));
    _world->add(_camera);
    _world->setMainCamera(_camera);

    /*GameObject* light = new GameObject("Light", glm::vec3(0, 2.5, 5));
    light->setMesh(sphereMesh);
    light->setMaterial(cubeMaterial);
    light->scale(glm::vec3(0.5, 0.5, 0.5));
    _world->add(light);*/

    // Lights
    Light* light1 = new Light("Light1", glm::vec3(0, 5, 5));
    light1->setConstantAttenuation(1.0f);
    light1->setLinearAttenuation(0.07f);
    light1->setQuadraticAttenuation(0.017f);
    _world->add(light1);

    Light* light2 = new Light("Light2", glm::vec3(-5, 3, 0));
    light2->setConstantAttenuation(1.0f);
    light2->setLinearAttenuation(0.07f);
    light2->setQuadraticAttenuation(0.017f);
    _world->add(light2);
}

void GoodWeek3::_render() {
    Light* pointLight = dynamic_cast<Light*>(_world->getLightAt(0));
    if (pointLight) {
        glm::vec3 updatedLightPosition = pointLight->getWorldPosition();
        // Update lighting dynamically
    }

    AbstractGame::_render();
}

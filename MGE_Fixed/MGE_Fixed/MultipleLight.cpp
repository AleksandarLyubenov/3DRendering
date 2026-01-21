#include "MultipleLight.hpp"
#include "mge/core/World.hpp"

MultipleLight::MultipleLight(const std::string& pName, const glm::vec3& pPosition) : GameObject(pName, pPosition)
{}

MultipleLight::~MultipleLight() {
}



//Override setWorldRecursively to make sure we are registered
void MultipleLight::_setWorldRecursively(World* pWorld) {

    //store the previous and new world before and after storing the given world
    World* previousWorld = _world;
    GameObject::_setWorldRecursively(pWorld);
    World* newWorld = _world;

    //check whether we need to register or unregister
    /*if (previousWorld != nullptr) previousWorld->unregisterLight(this);
    if (newWorld != nullptr) newWorld->registerLight(this);*/

}

float MultipleLight::getConstantAttenuation() const {
    return _constantAttenuation;
}

void MultipleLight::setConstantAttenuation(float value) {
    _constantAttenuation = value;
}

float MultipleLight::getLinearAttenuation() const {
    return _linearAttenuation;
}

void MultipleLight::setLinearAttenuation(float value) {
    _linearAttenuation = value;
}

float MultipleLight::getQuadraticAttenuation() const {
    return _quadraticAttenuation;
}

void MultipleLight::setQuadraticAttenuation(float value) {
    _quadraticAttenuation = value;
}


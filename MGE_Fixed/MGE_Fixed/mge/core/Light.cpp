#include "Light.hpp"
#include "World.hpp"

Light::Light(const std::string& pName, const glm::vec3& pPosition) : GameObject(pName, pPosition)
{}

Light::~Light() {
}



//Override setWorldRecursively to make sure we are registered
void Light::_setWorldRecursively (World* pWorld) {

    //store the previous and new world before and after storing the given world
    World* previousWorld = _world;
    GameObject::_setWorldRecursively(pWorld);
    World* newWorld = _world;

    //check whether we need to register or unregister
    if (previousWorld != nullptr) previousWorld->unregisterLight(this);
	if (newWorld != nullptr) newWorld->registerLight(this);

}

void Light::setLightColor(const glm::vec3& color) {
    _lightColor = color;
}

glm::vec3 Light::getLightColor() const {
    return _lightColor;
}

float Light::getConstantAttenuation() const {
    return _constantAttenuation;
}

void Light::setConstantAttenuation(float value) {
    _constantAttenuation = value;
}

float Light::getLinearAttenuation() const {
    return _linearAttenuation;
}

void Light::setLinearAttenuation(float value) {
    _linearAttenuation = value;
}

float Light::getQuadraticAttenuation() const {
    return _quadraticAttenuation;
}

void Light::setQuadraticAttenuation(float value) {
    _quadraticAttenuation = value;
}


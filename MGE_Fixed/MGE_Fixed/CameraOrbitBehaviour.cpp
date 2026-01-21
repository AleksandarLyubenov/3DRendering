#include "CameraOrbitBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

CameraOrbitBehaviour::CameraOrbitBehaviour(GameObject* target, float rotationSpeedX, float rotationSpeedY, float distance)
    : _target(target), _rotationSpeedX(rotationSpeedX), _rotationSpeedY(rotationSpeedY), _distance(distance), _currentAngleX(0.0f), _currentAngleY(0.0f), _isRotating(false), _enableZoom(true), _zoomVelocity(0.0f), _rotationVelocityX(0.0f), _rotationVelocityY(0.0f) {}

CameraOrbitBehaviour::~CameraOrbitBehaviour() {}

void CameraOrbitBehaviour::update(float pStep) {
    // Orbit functionality
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        _isRotating = true;

        static sf::Vector2i lastMousePosition = sf::Mouse::getPosition();
        sf::Vector2i currentMousePosition = sf::Mouse::getPosition();

        int deltaX = currentMousePosition.x - lastMousePosition.x;
        int deltaY = currentMousePosition.y - lastMousePosition.y;

        // Eased rotation (gradual acceleration and deceleration)
        _rotationVelocityX = glm::mix(_rotationVelocityX, deltaX * _rotationSpeedX, 0.1f); // Smooth horizontal rotation
        _rotationVelocityY = glm::mix(_rotationVelocityY, deltaY * _rotationSpeedY, 0.1f); // Smooth vertical rotation

        _currentAngleX += _rotationVelocityX * pStep;
        _currentAngleY += _rotationVelocityY * pStep;

        // Clamp vertical angle
        _currentAngleY = glm::clamp(_currentAngleY, -glm::radians(45.0f), glm::radians(45.0f));

        lastMousePosition = currentMousePosition; // Needed, otherwise it spins into oblivion
    }
    else {
        _isRotating = false;

        // Decelerate rotation velocities smoothly
        _rotationVelocityX = glm::mix(_rotationVelocityX, 0.0f, 0.1f);
        _rotationVelocityY = glm::mix(_rotationVelocityY, 0.0f, 0.1f);
    }

    if (_enableZoom) {
        float zoomChange = 0.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            zoomChange = 15.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            zoomChange = -15.0f;
        }

        _zoomVelocity = glm::mix(_zoomVelocity, zoomChange, 0.1f);

        Camera* camera = dynamic_cast<Camera*>(_owner);
        if (camera) {
            float newFOV = camera->getFOV() + _zoomVelocity * pStep;
            camera->setFOV(newFOV);
        }
    }
    else {
        _zoomVelocity = glm::mix(_zoomVelocity, 0.0f, 0.1f);
    }

    // Update camera position
    if (_target) {
        glm::vec3 targetPosition = _target->getWorldPosition();
        float x = targetPosition.x + _distance * cos(_currentAngleY) * sin(_currentAngleX);
        float y = targetPosition.y + _distance * sin(_currentAngleY);
        float z = targetPosition.z + _distance * cos(_currentAngleY) * cos(_currentAngleX);

        _owner->setLocalPosition(glm::vec3(x, y, z));
        _owner->lookAt(targetPosition);
    }
}


void CameraOrbitBehaviour::setRotationSpeedX(float speedX) {
    _rotationSpeedX = speedX;
}

void CameraOrbitBehaviour::setRotationSpeedY(float speedY) {
    _rotationSpeedY = speedY;
}

void CameraOrbitBehaviour::enableZoom(bool enable) {
    _enableZoom = enable;
}

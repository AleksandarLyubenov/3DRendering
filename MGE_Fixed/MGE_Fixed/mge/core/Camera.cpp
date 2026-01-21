#include "glm/glm.hpp"
#include "Camera.hpp"

Camera::Camera(
    std::string pName,
    glm::vec3 pPosition,
    glm::mat4 pProjectionMatrix
)
    : GameObject(pName, pPosition), _projection(pProjectionMatrix) {
    //_fov = glm::degrees(glm::atan(1.0f / _projection[1][1])); // Calculate FOV from projection matrix (tl;dr get current FOV)
}

Camera::~Camera() {}

void Camera::setFOV(float fov) {
    _fov = glm::clamp(fov, 5.0f, 120.0f); // so we don't go to 180+ FOV
    _projection = glm::perspective(glm::radians(_fov), 4.0f / 3.0f, 0.1f, 1000.0f);
}

float Camera::getFOV() const {
    return _fov;
}


glm::mat4& Camera::getProjection() {
    return _projection;
}



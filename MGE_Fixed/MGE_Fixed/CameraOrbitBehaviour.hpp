#ifndef CAMERA_ORBIT_BEHAVIOUR_HPP
#define CAMERA_ORBIT_BEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "glm.hpp"
#include "mge/core/Camera.hpp"

class Camera;

class CameraOrbitBehaviour : public AbstractBehaviour
{
public:
    CameraOrbitBehaviour(GameObject* target, float rotationSpeedX, float rotationSpeedY, float distance);
    virtual ~CameraOrbitBehaviour();

    virtual void update(float pStep) override;

    void setRotationSpeedX(float speedX);
    void setRotationSpeedY(float speedY);

    void enableZoom(bool enable);  // Enable/disable zoom

private:
    //GLuint _rotationSpeedXLocation; // Uniform location for rotationSpeedX
    //GLuint _rotationSpeedYLocation; // Uniform location for rotationSpeedY

    GameObject* _target;      // The object to orbit around
    float _rotationSpeedX;
    float _rotationSpeedY;
    float _distance;          // Distance from the target

    float _currentAngleX;
    float _currentAngleY;

    bool _isRotating;
    bool _enableZoom;         // Toggle for zoom functionality

    // Easing velocities
    float _rotationVelocityX;
    float _rotationVelocityY;
    float _zoomVelocity;
};

#endif // CAMERA_ORBIT_BEHAVIOUR_HPP

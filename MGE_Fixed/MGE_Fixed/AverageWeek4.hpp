#ifndef AVERAGEWEEK4_HPP
#define AVERAGEWEEK4_HPP

#include "mge/core/AbstractGame.hpp"
#include <glm/glm.hpp>

class GameObject;
class Camera;

class AverageWeek4 : public AbstractGame
{
public:
    AverageWeek4();
    virtual ~AverageWeek4();

    virtual void initialize();

protected:
    virtual void _initializeScene();
    virtual void _render();

private:
    glm::vec3 _lightDirection;
    float _lightRotationAngle;

    GameObject* _terrain;
    GameObject* _cube;
    Camera* _camera;
};

#endif // AVERAGEWEEK4_HPP

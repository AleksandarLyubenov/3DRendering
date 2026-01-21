#ifndef AVERAGEWEEK2_HPP
#define AVERAGEWEEK2_HPP

#include "mge/core/AbstractGame.hpp"

class GameObject;
class Camera;

class AverageWeek2 : public AbstractGame
{
public:
    AverageWeek2();
    virtual ~AverageWeek2();

    virtual void initialize();

protected:
    virtual void _initializeScene();
    virtual void _render();

private:
    GameObject* _cube;
    Camera* _camera;
};

#endif // AVERAGEWEEK2_HPP

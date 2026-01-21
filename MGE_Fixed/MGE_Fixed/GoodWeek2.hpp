#ifndef GOODWEEK2_HPP
#define GOODWEEK2_HPP

#include "mge/core/AbstractGame.hpp"

class GameObject;
class Camera;

class GoodWeek2 : public AbstractGame
{
public:
    GoodWeek2();
    virtual ~GoodWeek2();

    virtual void initialize();

protected:
    virtual void _initializeScene();
    virtual void _render();

private:
    GameObject* _cube;
    Camera* _camera;
};

#endif // GOODWEEK2_HPP

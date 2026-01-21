#ifndef GOODWEEK3_HPP
#define GOODWEEK3_HPP

#include "mge/core/AbstractGame.hpp"

class GameObject;
class Camera;

class GoodWeek3 : public AbstractGame
{
public:
    GoodWeek3();
    virtual ~GoodWeek3();

    virtual void initialize();

protected:
    virtual void _initializeScene();
    virtual void _render();

private:
    GameObject* _cube;
    Camera* _camera;
};

#endif // GOODWEEK3_HPP

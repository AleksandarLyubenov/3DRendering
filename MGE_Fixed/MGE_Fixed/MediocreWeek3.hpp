#ifndef MEDIOCREWEEK3_HPP
#define MEDIOCREWEEK3_HPP

#include "mge/core/AbstractGame.hpp"

class GameObject;
class Camera;

class MediocreWeek3 : public AbstractGame
{
public:
    MediocreWeek3();
    virtual ~MediocreWeek3();

    virtual void initialize();

protected:
    virtual void _initializeScene();
    virtual void _render();

private:
    GameObject* _cube;
    Camera* _camera;
};

#endif // MEDIOCREWEEK3_HPP

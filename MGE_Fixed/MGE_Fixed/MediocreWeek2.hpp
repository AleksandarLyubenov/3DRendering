#ifndef MEDIOCREWEEK2_HPP
#define MEDIOCREWEEK2_HPP

#include "mge/core/AbstractGame.hpp"

class GameObject;
class Camera;

class MediocreWeek2 : public AbstractGame
{
public:
    MediocreWeek2();
    virtual ~MediocreWeek2();

    virtual void initialize();

protected:
    virtual void _initializeScene();
    virtual void _render();

private:
    GameObject* _cube;
    Camera* _camera;
};

#endif // MEDIOCREWEEK2_HPP

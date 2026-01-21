#ifndef MEDIOCREWEEK4_HPP
#define MEDIOCREWEEK4_HPP

#include "mge/core/AbstractGame.hpp"

class GameObject;
class Camera;

class MediocreWeek4 : public AbstractGame
{
public:
    MediocreWeek4();
    virtual ~MediocreWeek4();

    virtual void initialize();

protected:
    virtual void _initializeScene();
    virtual void _render();

private:
    GameObject* _cube;
    Camera* _camera;
};

#endif // MEDIOCREWEEK4_HPP

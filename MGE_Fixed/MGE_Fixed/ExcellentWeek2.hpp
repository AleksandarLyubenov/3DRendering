#ifndef EXCELLENTWEEK2_HPP
#define EXCELLENTWEEK2_HPP

#include "mge/core/AbstractGame.hpp"

class GameObject;
class Camera;

class ExcellentWeek2 : public AbstractGame
{
public:
    ExcellentWeek2();
    virtual ~ExcellentWeek2();

    virtual void initialize();

protected:
    virtual void _initializeScene();
    virtual void _render();

private:
    GameObject* _cube;
    Camera* _camera;
};

#endif // EXCELLENTWEEK2_HPP

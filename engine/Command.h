#ifndef COMMAND_H
#define COMMAND_H

#include "Camera.h"

class Command
{
public:
    virtual ~Command() {}
    virtual void execute(Camera &camera) = 0;
};

class MoveForwardCommand : public Command
{
    public:
    virtual void execute(Camera& camera)
    {
        camera.position += camera.speed * camera.orientation;
    }
};

class StraffLeftCommand : public Command
{
    public:
    virtual void execute(Camera& camera)
    {
        camera.position += camera.speed * -glm::normalize(glm::cross(camera.orientation, camera.up));
    }
};

class StraffRightCommand : public Command
{
    public:
    virtual void execute(Camera& camera)
    {
        camera.position += camera.speed * glm::normalize(glm::cross(camera.orientation, camera.up));
    }
};

class MoveBackwardCommand : public Command
{
    public:
    virtual void execute(Camera& camera)
    {
        camera.position += camera.speed * -camera.orientation;
    }
};

class MoveUpCommand : public Command
{
    public:
    virtual void execute(Camera& camera)
    {
        camera.position += camera.speed * camera.up;
    }
};

class MoveDownCommand : public Command
{
    public:
    virtual void execute(Camera& camera)
    {
        camera.position += camera.speed * -camera.up;
    }
};

class TurboOnCommand : public Command
{
    public:
    virtual void execute(Camera& camera)
    {
        camera.speed = camera.high_speed;
    }
};

class TurboOffCommand : public Command
{
    public:
    virtual void execute(Camera& camera)
    {
        camera.speed = camera.slow_speed;
    }
};

#endif

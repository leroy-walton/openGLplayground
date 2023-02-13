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
        camera.Position += camera.speed * camera.Orientation;
    }
};

class StraffLeftCommand : public Command
{
    public:
    virtual void execute(Camera& camera)
    {
        camera.Position += camera.speed * -glm::normalize(glm::cross(camera.Orientation, camera.Up));
    }
};

class StraffRightCommand : public Command
{
    public:
    virtual void execute(Camera& camera)
    {
        camera.Position += camera.speed * glm::normalize(glm::cross(camera.Orientation, camera.Up));
    }
};

class MoveBackwardCommand : public Command
{
    public:
    virtual void execute(Camera& camera)
    {
        camera.Position += camera.speed * -camera.Orientation;
    }
};

class MoveUpCommand : public Command
{
    public:
    virtual void execute(Camera& camera)
    {
        camera.Position += camera.speed * camera.Up;
    }
};

class MoveDownCommand : public Command
{
    public:
    virtual void execute(Camera& camera)
    {
        camera.Position += camera.speed * -camera.Up;
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

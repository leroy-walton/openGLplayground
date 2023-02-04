#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <vector>

#include "Camera.h"
#include "Command.h"

class InputHandler
{
public:
    InputHandler();
    void handleInput(Camera &camera, GLFWwindow &window);

private:
    Command *key_w = new MoveForwardCommand();
    Command *key_s = new MoveBackwardCommand();
    Command *key_a = new StraffLeftCommand();
    Command *key_d = new StraffRightCommand();
    Command *key_leftctrl = new MoveDownCommand();
    Command *key_space = new MoveUpCommand();
    Command *key_leftshift_press = new TurboOnCommand();
    Command *key_leftshift_release = new TurboOffCommand();
};

#endif
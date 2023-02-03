#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Camera.h"

class InputHandler
{
    // Command*
    public:
    void handleInput(Camera &camera, GLFWwindow &window);
};

#endif
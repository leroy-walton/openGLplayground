#include "InputHandler.h"

InputHandler::InputHandler()
{
    key_w = new MoveForwardCommand();
    key_s = new MoveBackwardCommand();
    key_a = new StraffLeftCommand();
    key_d = new StraffRightCommand();
    key_leftctrl = new MoveDownCommand();
    key_space = new MoveUpCommand();
    key_leftshift_press = new TurboOnCommand();
    key_leftshift_release = new TurboOffCommand();
}

void InputHandler::handleInput(Camera &camera, GLFWwindow &window)
{
    {
        std::vector<Command*> command_queue;
        
        // Handles key inputs
        if (glfwGetKey(&window, GLFW_KEY_W) == GLFW_PRESS)
            key_w->execute(camera);
        if (glfwGetKey(&window, GLFW_KEY_A) == GLFW_PRESS) key_a->execute(camera);
        if (glfwGetKey(&window, GLFW_KEY_S) == GLFW_PRESS) key_s->execute(camera);
        if (glfwGetKey(&window, GLFW_KEY_D) == GLFW_PRESS) key_d->execute(camera);
        if (glfwGetKey(&window, GLFW_KEY_SPACE) == GLFW_PRESS) key_space->execute(camera);
        if (glfwGetKey(&window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) key_leftctrl->execute(camera);
        if (glfwGetKey(&window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) key_leftshift_press->execute(camera);
        else if (glfwGetKey(&window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) key_leftshift_release->execute(camera);

        // Handles mouse inputs
        if (glfwGetMouseButton(&window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            // Hides mouse cursor
            glfwSetInputMode(&window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

            // Prevents camera from jumping on the first click
            if (camera.firstClick)
            {
                glfwSetCursorPos(&window, (camera.width / 2), (camera.height / 2));
                camera.firstClick = false;
            }

            // Stores the coordinates of the cursor
            double mouseX;
            double mouseY;
            // Fetches the coordinates of the cursor
            glfwGetCursorPos(&window, &mouseX, &mouseY);

            // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
            // and then "transforms" them into degrees
            float rotX = camera.sensitivity * (float)(mouseY - (camera.height / 2)) / camera.height;
            float rotY = camera.sensitivity * (float)(mouseX - (camera.width / 2)) / camera.width;

            // Calculates upcoming vertical change in the Orientation
            glm::vec3 newOrientation = glm::rotate(camera.orientation, glm::radians(-rotX), glm::normalize(glm::cross(camera.orientation, camera.up)));

            // Decides whether or not the next vertical Orientation is legal or not
            if (abs(glm::angle(newOrientation, camera.up) - glm::radians(90.0f)) <= glm::radians(85.0f))
            {
                camera.orientation = newOrientation;
            }

            // Rotates the Orientation left and right
            camera.orientation = glm::rotate(camera.orientation, glm::radians(-rotY), camera.up);

            // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
            glfwSetCursorPos(&window, (camera.width / 2), (camera.height / 2));
        }
        else if (glfwGetMouseButton(&window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        {
            // Unhides cursor since camera is not looking around anymore
            glfwSetInputMode(&window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            // Makes sure the next time the camera looks around it doesn't jump
            camera.firstClick = true;
        }
    }
}

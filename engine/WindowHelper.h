#ifndef WINDOW_HELPER_H
#define WINDOW_HELPER_H

#include <iostream>
#include <GLFW/glfw3.h>

class WindowHelper {
public:
    GLFWwindow* m_window;

    WindowHelper(int width, int height) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        GLFWwindow *window = glfwCreateWindow(width, height, "engine_demo", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            // return nullptr;
            //  TODO: raise exception
        }
        glfwMakeContextCurrent(window);
        // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
        glewExperimental = GL_TRUE;
        if (GLEW_OK != glewInit())
        {
            std::cout << "Failed to initialize GLEW" << std::endl;
            // return nullptr;
            //  TODO: raise exception
        }

       glfwSetFramebufferSizeCallback(window, fb_size_callback);
       
        // return window;
        m_window = window;

        	glViewport(0, 0, width, height);
	        glEnable(GL_DEPTH_TEST);
	        glEnable(GL_CULL_FACE);
	        glFrontFace(GL_CCW);
	        // glCullFace(GL_FRONT);
	        glCullFace(GL_BACK);
	        glDepthFunc(GL_LESS);
    }

    void static fb_size_callback(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

};

#endif
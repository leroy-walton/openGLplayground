#include <ctime>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "VAO.h"
#include "EBO.h"
#include "Shader.h"

const unsigned int window_width = 2000;
const unsigned int window_height = 1000;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow *initGlfwWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow *window = glfwCreateWindow(window_width, window_height, "bored textured quad", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return nullptr;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    return window;
}

void initOpenGl()
{
    glViewport(0, 0, window_width, window_height);
    // glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_FRONT);
    // glCullFace(GL_BACK);
    glDepthFunc(GL_LESS);
}

float quad_vertices[] = {
    //  Position      Color             Texcoords
    -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // Top-right
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
    -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f // Bottom-left
};

GLuint quad_elements[] = {
    0, 1, 2,
    2, 3, 0};

int main()
{
    GLFWwindow *window = initGlfwWindow();
    initOpenGl();

    // --------------------------- compile shader -------------------------//
    // Create and compile the shader

    Shader stupidShader("stupid.vert", "stupid.frag");
    stupidShader.Activate();

    // ----------------------------- mesh data----------------------------- //
    // upload mesh data to gpu & link data to shader

    VAO VAO1;
    VAO1.Bind();
    VBO VBO1(quad_vertices, sizeof(quad_vertices)); // glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);
    EBO EBO1(quad_elements, sizeof(quad_elements)); // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quad_elements), quad_elements, GL_STATIC_DRAW);
    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(stupidShader.ID, "aPos");
    GLint colAttrib = glGetAttribLocation(stupidShader.ID, "aColor");
    GLint texAttrib = glGetAttribLocation(stupidShader.ID, "aTex");
    VAO1.LinkAttrib(VBO1, posAttrib, 2, GL_FLOAT, 7 * sizeof(float), (void *)0);                   // position ?
    VAO1.LinkAttrib(VBO1, colAttrib, 3, GL_FLOAT, 7 * sizeof(float), (void *)(2 * sizeof(float))); // colors ?
    VAO1.LinkAttrib(VBO1, texAttrib, 2, GL_FLOAT, 7 * sizeof(float), (void *)(5 * sizeof(float))); // texCoord ?

    // --------------------------- texture -------------------------------//
    // Create texture and load images

    GLuint texture;
    glGenTextures(1, &texture);
    int width, height, comp = 0;
    unsigned char *img = 0;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    img = stbi_load("resources/textures/sample.png", &width, &height, &comp, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    stbi_image_free(img);
    glUniform1i(glGetUniformLocation(stupidShader.ID, "tex0"), 0);

    // time test

    float crntTime;
    // ---------------------------- Main Loop ------------------------------ //

    while (!glfwWindowShouldClose(window))
    {
        // time test
        crntTime = glfwGetTime();
        // Use the current time to update the "time" uniform in your shader
        glUniform1f(glGetUniformLocation(stupidShader.ID, "time"), crntTime);
        // Clear the screen to black
        glClearColor(0.02f, 0.0f, 0.01f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw a quad from the 2 triangles using 6 elements
        glDrawElements(GL_TRIANGLES, sizeof(quad_elements), GL_UNSIGNED_INT, 0);

        // Swap buffers and poll window events
        glfwSwapBuffers(window);
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        glfwPollEvents();
    }

    // ---------------------------- CLEARING ------------------------------ //
    // Delete allocated resources

    stupidShader.Delete();
    glDeleteTextures(1, &texture);
    EBO1.Delete(); // glDeleteBuffers(1, &ebo);
    VBO1.Delete(); // glDeleteBuffers(1, &vbo);
    VAO1.Delete(); // glDeleteVertexArrays(1, &vao);

    // ---------------------------- TERMINATE ----------------------------- //

    glfwTerminate();
    return 0;
}

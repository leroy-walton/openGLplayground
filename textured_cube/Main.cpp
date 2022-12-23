#include<filesystem>
// namespace fs = std::filesystem;

#include<iostream>
#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include<math.h>
#include"CubeMap.h"
#include"FpsCounter.h"
#include<map>
#include"GUI.h"
#include"ModelLoader.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include"VAO.h"
#include"EBO.h"

const unsigned int width = 2000;
const unsigned int height = 1000;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
     glViewport(0, 0, width, height);
}

GLFWwindow* initGlfwWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(width, height, "bored v0.0.1  - basic opengl rendering engine demistified", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);
	 // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
	if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return nullptr;
    }

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	return window;
}

void initOpenGl() 
{
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	//glCullFace(GL_FRONT);
	glCullFace(GL_BACK);
	glDepthFunc(GL_LESS);

}

GLfloat cube_vertices[] = { // position / color / texCoord
    // front
    -1.0, -1.0,  1.0,	0.9f, 0.0f, 0.0f,  	0.0f, 0.0f,
     1.0, -1.0,  1.0,	0.0f, 0.9f, 0.0f,   1.0f, 0.0f,
     1.0,  1.0,  1.0,	0.0f, 0.0f, 0.9f,	1.0f, 1.0f,
    -1.0,  1.0,  1.0,	0.9f, 0.9f, 0.9f,	0.0f, 1.0f,
    // back
    -1.0, -1.0, -1.0,	0.9f, 0.0f, 0.0f,	1.0f, 0.0f,
     1.0, -1.0, -1.0,	0.0f, 0.9f, 0.0f,	0.0f, 1.0f,
     1.0,  1.0, -1.0,	0.0f, 0.0f, 0.9f,	0.0f, 0.0f,
    -1.0,  1.0, -1.0,	0.9f, 0.9f, 0.9f,	1.0f, 1.0f
};

GLuint cube_elements[] = {  // face indices
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
};

int main()
{
	GLFWwindow* window = initGlfwWindow();
	initOpenGl();

	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(cube_vertices, sizeof(cube_vertices));
	EBO EBO1(cube_elements, sizeof(cube_elements));
	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0); // position ?
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float))); // colors ?
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float))); // texCoord ?
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f)); // init camera
	Shader stupidShader("stupid.vert", "stupid.frag");			// compile shader
	
	// texture mapping
	Texture tex(".","resources/textures/3dfx-chip.png", aiTextureType_NONE);
	tex.load(1);		
	GLint textureUniformLocation = glGetUniformLocation(stupidShader.ID, "tex0");
    glUniform1i(textureUniformLocation, 0); // 0 corresponds to GL_TEXTURE0 ?
    glBindTexture(GL_TEXTURE_2D, tex.id); 	// Bind the texture before drawing

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		stupidShader.Activate();
		camera.Inputs(window);
		camera.Matrix(stupidShader, "camMatrix");

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(cube_elements) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        	glfwSetWindowShouldClose(window, true);
		glfwPollEvents();
	}

	// seek & destroy
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

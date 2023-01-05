#include <filesystem>
// namespace fs = std::filesystem;

#include <iostream>
#include <GL/glew.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <math.h>
#include "FpsCounter.h"
#include <map>
#include "GUI.h"

#include <assimp/Importer.hpp>	// C++ importer interface
#include <assimp/scene.h>		// Output data structure
#include <assimp/postprocess.h> // Post processing flags

#include "VAO.h"
#include "EBO.h"
#include <glm/gtx/string_cast.hpp>

const unsigned int width = 2000;
const unsigned int height = 1000;

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
	GLFWwindow *window = glfwCreateWindow(width, height, "superbible 6", NULL, NULL);
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
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glCullFace(GL_FRONT);
	// glCullFace(GL_BACK);

	glDepthFunc(GL_LESS);
}

int main()
{
	GLFWwindow *window = initGlfwWindow();
	initOpenGl();
	double prevTime = glfwGetTime();
	FpsCounter fpsCounter;
	GUI gui(window);
	/************************* startup ************************************/

	Shader stupidShader("stupid.vert", "stupid.frag");
	VAO *ourVAO = new VAO();
	ourVAO->Bind();

	/*********************************************************************/
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.25f, 0.13f, 0.14f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			prevTime = crntTime;
		}
		/************************* render ************************************/

		const GLfloat color[] = {0.3f, 0.8f, 1.0f, 1.0f};
		glClearBufferfv(GL_COLOR, 0, color);
		stupidShader.Activate();
		GLfloat attrib[] = {(float)sin(crntTime) * 0.5f,
							(float)cos(crntTime) * 0.6f,
							0.0f, 0.0f};
		// Update the value of input attribute 0
		glVertexAttrib4fv(0, attrib);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/*********************************************************************/
		gui.drawGUI(fpsCounter.getFps());
		glfwSwapBuffers(window);
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
		glfwPollEvents();
	}
	/*************************** shutdown ***********************************/

	ourVAO->Delete();
	stupidShader.Delete();

	/*********************************************************************/
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

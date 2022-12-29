#include <filesystem>
// namespace fs = std::filesystem;

#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <math.h>
#include "CubeMap.h"
#include "FpsCounter.h"
#include <map>
#include "GUI.h"
#include "ModelLoader.h"

#include <assimp/Importer.hpp>	// C++ importer interface
#include <assimp/scene.h>		// Output data structure
#include <assimp/postprocess.h> // Post processing flags

#include "VAO.h"
#include "EBO.h"
#include "TexturedCube.h"
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
	GLFWwindow *window = glfwCreateWindow(width, height, "textured cube", NULL, NULL);
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
	// glCullFace(GL_FRONT);
	glCullFace(GL_BACK);
	glDepthFunc(GL_LESS);
}

int main()
{
	GLFWwindow *window = initGlfwWindow();
	initOpenGl();

	TexturedCube texturedCube;

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f)); // init camera

	// CubeMap cubeMap;
	// Shader skyboxShader("skybox.vert", "skybox.frag");
	// skyboxShader.Activate();
	// glUniform1i(glGetUniformLocation(skyboxShader.ID, "skybox"), 0);

	Shader stupidShader("stupid.vert", "stupid.frag"); // compile shader

	// cube texture mapping
	Texture tex(".", "resources/textures/3dfx-chip.png", aiTextureType_NONE);
	tex.load(1);
	GLint textureUniformLocation = glGetUniformLocation(stupidShader.ID, "tex0");
	glUniform1i(textureUniformLocation, 0); // 0 corresponds to GL_TEXTURE0 ?
	glBindTexture(GL_TEXTURE_2D, tex.id);	// Bind the texture before drawing

	FpsCounter fpsCounter;
	GUI gui(window);

	float rotation = 0.0f;
	double prevTime = glfwGetTime();
	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.05f, 0.03f, 0.04f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// cubeMap.draw(skyboxShader, camera);
		stupidShader.Activate();
		camera.Inputs(window);
		camera.Matrix(stupidShader, "proj");
		glActiveTexture(GL_TEXTURE0);

		float crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.5f;
			prevTime = crntTime;
		}

		// rotation
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation * 2.3f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation * 0.6f), glm::vec3(0.0f, 0.0f, 1.0f));
		int modelLoc = glGetUniformLocation(stupidShader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		int timeLoc = glGetUniformLocation(stupidShader.ID, "time");
		glUniform1f(timeLoc, crntTime);

		texturedCube.draw(stupidShader, camera);

		gui.draw(fpsCounter.getFps());

		glfwSwapBuffers(window);
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
		glfwPollEvents();
	}

	// seek & destroy
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

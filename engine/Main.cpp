#include <filesystem>
#include <iostream>
#include <math.h>
#include <map>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <assimp/Importer.hpp>	// C++ importer interface
#include <assimp/scene.h>		// Output data structure
#include <assimp/postprocess.h> // Post processing flags
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CubeMap.h"
#include "FpsCounter.h"
#include "GUI.h"
#include "ModelLoader.h"
#include "World.h"
#include "VAO.h"
#include "EBO.h"
#include "TexturedCube.h"

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
	GLFWwindow *window = glfwCreateWindow(width, height, "engine_demo", NULL, NULL);
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

	Shader stupidShader("stupid.vert", "stupid.frag"); // compile shader
	Shader normalColorShader("normalColor.vert", "normalColor.frag");
	Shader lightShader("light.vert", "light.frag");

	World world;
	Model barrelModel("resources/models/wine_barrel/wine_barrel_01_4k.gltf");
	Model sponzaModel("resources/models/sponza/Sponza.gltf");
	Model suzanneModel("resources/models/suzanne/Suzanne2.gltf");
	Model skullRatCubeModel("resources/models/cubeskullrat/cube_skull_rat.gltf");
	Model sphereModel("resources/models/sphere.gltf");
	Model terrainModel("resources/models/terrain/terrain_test_01.gltf");

	WorldEntity lamp("lamp", &sphereModel, &lightShader );
	world.addEntity("lamp", &lamp);
	//WorldEntity sponza("sponza", &sponzaModel, &normalColorShader);
	WorldEntity sponza("sponza", &sponzaModel, &stupidShader);
	world.addEntity("sponza", &sponza);
	WorldEntity skullRatCube("skullRatCube", &skullRatCubeModel, &stupidShader);
	world.addEntity("skullRatCube", &skullRatCube);
	WorldEntity test("test", &skullRatCubeModel, &stupidShader); // multiple entities can be linked to the same model.
	world.addEntity("test", &test);
	WorldEntity suzanne("suzanne", &suzanneModel, &normalColorShader);
	world.addEntity("suzanne", &suzanne);
	WorldEntity barrel("barrel", &barrelModel, &stupidShader);
	world.addEntity("barrel", &barrel);
	WorldEntity terrain("terrain", &terrainModel, &stupidShader);
	world.addEntity("terrain", &terrain);

	barrel.position = glm::vec3(50.0, -1.0f, 0.0f);
	barrel.scaleUp(glm::vec3(50.0f));
	skullRatCube.scaleUp(glm::vec3(20.0f));
	skullRatCube.translate(glm::vec3(400.0f, 20.0f, 150.0f));
	suzanne.scaleUp(glm::vec3(30.0f));
	suzanne.translate(glm::vec3(-440.0f, 140.0f, -250.0f));
	test.scaleUp(glm::vec3(20.0f));
	lamp.scaleUp(glm::vec3(20.0f));
	terrain.scaleUp(glm::vec3(10000.0f));
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 4.0f)); // init camera

	// CubeMap cubeMap;
	// Shader skyboxShader("skybox.vert", "skybox.frag");
	// skyboxShader.Activate();
	// glUniform1i(glGetUniformLocation(skyboxShader.ID, "skybox"), 0);

	FpsCounter fpsCounter;
	GUI gui(window);
	float rotation = 0.0f;
	double prevTime = glfwGetTime();
	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		camera.Inputs(window);
		float crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.5f;
			prevTime = crntTime;
		}

		// 3d space positioning
		skullRatCube.rotate(0.04f, glm::vec3(0.0f, 1.0f, 0.0f));
		//suzanne.position = glm::vec3(sin(crntTime), 0.0f, cos(crntTime)) * 5.0f;
		test.position = glm::vec3(0.0f, 150.0f, 0.0f);

		glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec3 lightPos = glm::vec3(10.5f, 10.5f, 10.5f);
		glm::mat4 lightModel = glm::mat4(1.0f);

		lightPos = glm::vec3(1200.5f * sin(crntTime/3.0), abs(sin(crntTime*2.4)*300.5f), cos(crntTime/3.0) * 40.5f);
		lightModel = glm::translate(lightModel, lightPos);
		lamp.position = lightPos;
		stupidShader.Activate();
		glUniform4f(glGetUniformLocation(stupidShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(stupidShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform1f(glGetUniformLocation(stupidShader.ID, "time"), crntTime);
		glUniform3f(glGetUniformLocation(stupidShader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(stupidShader, "proj");

		normalColorShader.Activate();
		glUniform4f(glGetUniformLocation(normalColorShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(normalColorShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform1f(glGetUniformLocation(normalColorShader.ID, "time"), crntTime);
		glUniform3f(glGetUniformLocation(normalColorShader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(normalColorShader, "proj");

		lightShader.Activate();
		glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		camera.Matrix(lightShader, "camMatrix");

		glClearColor(0.12f, 0.16f, 0.21f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		world.draw();

		// cubeMap.draw(skyboxShader, camera);
		gui.drawGUI(fpsCounter.getFps(), &world);
		// gui.draw(fpsCounter.getFps(), world.getItems());
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

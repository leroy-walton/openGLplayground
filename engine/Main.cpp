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
#include "World.h"

#include <assimp/Importer.hpp>	// C++ importer interface
#include <assimp/scene.h>		// Output data structure
#include <assimp/postprocess.h> // Post processing flags
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	GLFWwindow *window = glfwCreateWindow(width, height, "Sponza with rotating cube", NULL, NULL);
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

	Shader normalColorShader("normalColor.vert", "normalColor.frag");
	Shader stupidShader("stupid.vert", "stupid.frag"); // compile shader
	

	std::cout << "stupidShader.ID = " << stupidShader.ID << "\n";
	std::cout << "normalColorShader.ID = " << normalColorShader.ID << "\n";

	World world;
	Model barrelModel("resources/models/wine_barrel/wine_barrel_01_4k.gltf");
	Model sponzaModel("resources/models/sponza/Sponza.gltf");
	Model suzanneModel("resources/models/suzanne/Suzanne2.gltf");
	Model skullRatCubeModel("resources/models/cubeskullrat/cube_skull_rat.gltf");
	
	//WorldEntity sponza("sponza", &sponzaModel, &normalColorShader);
	WorldEntity sponza("sponza", &sponzaModel, &stupidShader);
	world.addEntity("sponza", &sponza);
	WorldEntity skullRatCube("skullRatCube", &skullRatCubeModel, &stupidShader);
	world.addEntity("skullRatCube", &skullRatCube);
	WorldEntity suzanne("suzanne", &suzanneModel, &stupidShader);
	world.addEntity("suzanne", &suzanne);
	WorldEntity barrel("barrel", &barrelModel, &stupidShader);
	world.addEntity("barrel", &barrel);

	WorldEntity test("test", &skullRatCubeModel, &stupidShader); // multiple entities can be linked to the same model.
	world.addEntity("test", &test);

	barrel.position = glm::vec3(50.0, -1.0f, 0.0f);
	barrel.scaleUp(glm::vec3(50.0f ));
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
		glClearColor(0.12f, 0.16f, 0.21f, 1.0f );
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// cubeMap.draw(skyboxShader, camera);
		//stupidShader.Activate();
		camera.Inputs(window);
		camera.Matrix(normalColorShader, "proj");
		camera.Matrix(stupidShader, "proj");

		float crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.5f;
			prevTime = crntTime;
		}

		glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec3 lightPos = glm::vec3(10.5f, 10.5f, 10.5f);
		glm::mat4 lightModel = glm::mat4(1.0f);


		lightPos = glm::vec3(300.5f * sin(crntTime), 10.5f, cos(crntTime)*40.5f);

		lightModel = glm::translate(lightModel, lightPos);
		glUniform4f(glGetUniformLocation(stupidShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(stupidShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform1f(glGetUniformLocation(stupidShader.ID, "time"), crntTime);

		glUniform4f(glGetUniformLocation(normalColorShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(normalColorShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform1f(glGetUniformLocation(normalColorShader.ID, "time"), crntTime);

		skullRatCube.rotate(0.04f,  glm::vec3(0.0f, 1.0f, 0.0f));
		suzanne.position=glm::vec3(sin(crntTime), 0.0f, cos(crntTime) )* 5.0f;
		test.position=glm::vec3(-4.0f, 0.0f, 0.0f);
		
		world.draw();

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

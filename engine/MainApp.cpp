
#include "MainApp.h"

MainApp::MainApp()
{
	initGlfwWindow();
	initOpenGl();
}

MainApp::~MainApp()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void MainApp::initGlfwWindow()
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

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// return window;
	m_window = window;
}

void MainApp::initOpenGl()
{
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	// glCullFace(GL_FRONT);
	glCullFace(GL_BACK);
	glDepthFunc(GL_LESS);
}

void MainApp::run()
{
	World world;

	Model barrelModel("resources/models/wine_barrel/wine_barrel_01_4k.gltf");
	Model sphereModel("resources/models/sphere.gltf");
	Model terrainModel("resources/models/terrain/ground_textured_100x100.gltf");
	Model skullRatCubeModel("resources/models/cubeskullrat/cube_skull_rat.gltf");

	Shader basicShader = *world.basicShader;
	Shader normalColorShader = *world.normalColorShader;
	Shader uniColorShader = *world.uniColorShader;


	entt::registry registry;
	auto e = registry.create();
    const int numEntities = 2;
    for (int i = 0; i < numEntities; i++)
    {
        auto e = registry.create();
		registry.emplace<DynamicCube>(e);
        Transform &transform = registry.emplace<Transform>(e);
		transform.position.x = 2*i;
		transform.position.y = 1;
		transform.position.z = 2*i;
        auto &vel = registry.emplace<Velocity>(e);
        vel.velocity.x = 5;
        vel.velocity.y = 5;
		vel.velocity.z = 4;
		VisualShape &visuals = registry.emplace<VisualShape>(e);
		visuals.model = &skullRatCubeModel;
		visuals.shader = &basicShader;
    }



	WorldEntity lamp("lamp", &sphereModel, &uniColorShader);
	world.addEntity("lamp", &lamp);
	WorldEntity barrel("barrel", &barrelModel, &basicShader);
	world.addEntity("barrel", &barrel);
	WorldEntity terrain("terrain", &terrainModel, &basicShader);
	world.addEntity("terrain", &terrain);

	WorldEntity skullRatCube("skullRatCube", &skullRatCubeModel, &basicShader);
	world.addEntity("skullRatCube", &skullRatCube);

	barrel.position = glm::vec3(50.0, -1.0f, 0.0f);
	barrel.scaleUp(glm::vec3(20.0f));
	lamp.scaleUp(glm::vec3(30.0f));
	terrain.scaleUp(glm::vec3(10000.0f));

	skullRatCube.scaleUp(glm::vec3(20.0f));
	skullRatCube.translate(glm::vec3(0.0f, 20.0f, 150.0f));

	Camera camera(width, height, glm::vec3(0.0f, 4.0f, -40.0f)); // init camera

	// ************************************************* phys ************************************** //
	// ************************************************************************************** //

	FpsCounter fpsCounter;
	GUI gui(m_window);
	float rotation = 0.0f;
	double prevTime = glfwGetTime();
	WorldRenderer worldRenderer;
	InputHandler inputHandler;

	// Main loop
	while (!glfwWindowShouldClose(m_window))
	{
		inputHandler.handleInput(camera, *m_window);
		if (camera.Position.y < 0.2f)
			camera.Position.y = 0.20f;
		float crntTime = glfwGetTime();
		float timeStep = crntTime - prevTime;
		if (timeStep >= 1 / 60)
		{
			rotation += 0.5f;
			prevTime = crntTime;
		}

		// *******************   bullet phys **************
		// ************************************************

		// 3d space positioning
		skullRatCube.rotate(0.04f, glm::vec3(0.0f, 1.0f, 0.0f));
		// suzanne.position = glm::vec3(sin(crntTime), 0.0f, cos(crntTime)) * 5.0f;

		glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec3 lightPos = glm::vec3(10.5f, 10.5f, 10.5f);
		glm::mat4 lightModel = glm::mat4(1.0f);

		// lightPos = glm::vec3(1200.5f * sin(crntTime/3.0), abs(sin(crntTime*2.4)*300.5f), cos(crntTime/3.0) * 40.5f);
		lightPos = glm::vec3(-1000.0, 1000.0, 450.0);

		lightModel = glm::translate(lightModel, lightPos);
		lamp.position = lightPos;
		basicShader.Activate();
		glUniform4f(glGetUniformLocation(basicShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(basicShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform1f(glGetUniformLocation(basicShader.ID, "time"), crntTime);
		glUniform3f(glGetUniformLocation(basicShader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(basicShader, "proj");

		normalColorShader.Activate();
		glUniform4f(glGetUniformLocation(normalColorShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(normalColorShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform1f(glGetUniformLocation(normalColorShader.ID, "time"), crntTime);
		glUniform3f(glGetUniformLocation(normalColorShader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(normalColorShader, "proj");

		uniColorShader.Activate();
		glUniform4f(glGetUniformLocation(uniColorShader.ID, "color"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		camera.Matrix(uniColorShader, "camMatrix");

		glClearColor(0.12f, 0.16f, 0.21f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//world.draw();
		//renderWorld(world);
		worldRenderer.render(&world);
		worldRenderer.renderRegistry(registry);
		// cubeMap.draw(skyboxShader, camera);
		gui.drawGUI(fpsCounter.getFps(), &world);
		// gui.draw(fpsCounter.getFps(), world.getItems());
		glfwSwapBuffers(m_window);
		if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(m_window, true);
		glfwPollEvents();
	}
}

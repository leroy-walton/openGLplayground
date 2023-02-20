
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
	entt::registry registry;
    
	Factory::makePlanets(registry);
	Factory::makeStaticObjects(registry);
	Factory::makeRotatingCube(registry);
	entt::entity lampEntity = Factory::makeLight(registry);
	Transform& lampTransform = registry.get<Transform>(lampEntity); // needed for shaders
	lampTransform.position = glm::vec3(-1000.0, 1000.0, 450.0);
	Camera camera(width, height, glm::vec3(40.0f, 40.0f, 250.0f)); // init camera

	FpsCounter fpsCounter;
	GUI gui(m_window);
	float rotation = 0.0f;
	double prevTime = glfwGetTime();
	InputHandler inputHandler;
	RenderSystem renderSystem;
	RotationSystem rotationSystem;
	MoveSystem moveSystem;
	GravitySystem gravitySystem;
	
	// Main loop
	while (!glfwWindowShouldClose(m_window))
	{
		float crntTime = glfwGetTime();
		inputHandler.handleInput(camera, *m_window);
		if (camera.position.y < 0.2f)
			camera.position.y = 0.20f;

		moveSystem.update(registry);
		gravitySystem.update(registry);
		rotationSystem.update(registry);
		ResourceManager::updateShaders(camera, lampTransform.position, crntTime);
		glClearColor(0.12f, 0.16f, 0.21f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		renderSystem.render(registry);
		// cubeMap.draw(skyboxShader, camera);
		gui.drawGUI(fpsCounter.getFps(), camera);

		glfwSwapBuffers(m_window);
		if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(m_window, true);
		glfwPollEvents();
	}
}

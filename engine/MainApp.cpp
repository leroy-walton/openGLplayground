
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
	
	// // lamp
	auto lampEntity = registry.create();
	Transform &lampTransform = registry.emplace<Transform>(lampEntity);
	VisualShape &lampVs = registry.emplace<VisualShape>(lampEntity);
	lampVs.model = ResourceManager::getSphereModel();
	lampVs.shader = ResourceManager::getUniColorShader();
	lampTransform.scale = glm::vec3(30.f);

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
		if (camera.Position.y < 0.2f)
			camera.Position.y = 0.20f;

		glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec3 lightPos = glm::vec3(10.5f, 10.5f, 10.5f);
		glm::mat4 lightModel = glm::mat4(1.0f);

		//lightPos = glm::vec3(1200.5f * sin(crntTime/3.0), abs(sin(crntTime*2.4)*300.5f), cos(crntTime/3.0) * 40.5f);
		lightPos = glm::vec3(-1000.0, 1000.0, 450.0);

		lightModel = glm::translate(lightModel, lightPos);
		lampTransform.position = lightPos;
		
		ResourceManager::getBasicShader()->Activate();
		glUniform4f(glGetUniformLocation(ResourceManager::getBasicShader()->ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(ResourceManager::getBasicShader()->ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform1f(glGetUniformLocation(ResourceManager::getBasicShader()->ID, "time"), crntTime);
		glUniform3f(glGetUniformLocation(ResourceManager::getBasicShader()->ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(*ResourceManager::getBasicShader(), "proj");

		ResourceManager::getNormalColorShader()->Activate();
		glUniform4f(glGetUniformLocation(ResourceManager::getNormalColorShader()->ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(ResourceManager::getNormalColorShader()->ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform1f(glGetUniformLocation(ResourceManager::getNormalColorShader()->ID, "time"), crntTime);
		glUniform3f(glGetUniformLocation(ResourceManager::getNormalColorShader()->ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(*ResourceManager::getNormalColorShader(), "proj");

		ResourceManager::getUniColorShader()->Activate();
		glUniform4f(glGetUniformLocation(ResourceManager::getUniColorShader()->ID, "color"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		camera.Matrix(*ResourceManager::getUniColorShader(), "camMatrix");

		glClearColor(0.12f, 0.16f, 0.21f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		moveSystem.update(registry);
		gravitySystem.update(registry);
		rotationSystem.update(registry);
		renderSystem.render(registry);
		// cubeMap.draw(skyboxShader, camera);
		gui.drawGUI(fpsCounter.getFps(), camera);

		glfwSwapBuffers(m_window);
		if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(m_window, true);
		glfwPollEvents();
	}
}

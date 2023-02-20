
#include "MainApp.h"

MainApp::MainApp()
{
	m_window = WindowHelper(width, height).m_window;
}

MainApp::~MainApp()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void MainApp::run()
{
	FpsCounter fpsCounter;
	GUI gui(m_window);
	InputHandler inputHandler;
	RenderSystem renderSystem;
	RotationSystem rotationSystem;
	MoveSystem moveSystem;
	GravitySystem gravitySystem;

	entt::registry registry;
	Factory::makePlanets(registry);
	Factory::makeStaticObjects(registry);
	Factory::makeRotatingCube(registry);
	entt::entity lampEntity = Factory::makeLight(registry);
	Transform& lampTransform = registry.get<Transform>(lampEntity); 
	lampTransform.position = glm::vec3(-1000.0, 1000.0, 450.0); // needed by shaders
	Camera camera(width, height, glm::vec3(40.0f, 40.0f, 250.0f)); // init camera
	
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

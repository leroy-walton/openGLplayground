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

#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/btBulletCollisionCommon.h>

#include "CubeMap.h"
#include "FpsCounter.h"
#include "GUI.h"
#include "ModelLoader.h"
#include "World.h"
#include "VAO.h"
#include "EBO.h"
#include "TexturedCube.h"
#include "WorldFactory.h"

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


	//WorldFactory wf;
//    World testWorld = wf.generate();

	World world;
	
	Model barrelModel("resources/models/wine_barrel/wine_barrel_01_4k.gltf");
	//Model sponzaModel("resources/models/sponza/Sponza.gltf");
	Model suzanneModel("resources/models/suzanne/Suzanne2.gltf");
	Model sphereModel("resources/models/sphere.gltf");
	Model terrainModel("resources/models/terrain/ground_textured_100x100.gltf");

	Model skullRatCubeModel("resources/models/cubeskullrat/cube_skull_rat.gltf");

	Shader basicShader = *world.basicShader;
	Shader normalColorShader = *world.normalColorShader;
	Shader uniColorShader = *world.uniColorShader;

	
	WorldEntity lamp("lamp", &sphereModel, &uniColorShader );
	world.addEntity("lamp", &lamp);
	//WorldEntity sponza("sponza", &sponzaModel, &normalColorShader);
	//WorldEntity sponza("sponza", &sponzaModel, &basicShader);
	//world.addEntity("sponza", &sponza);
	WorldEntity suzanne("suzanne", &suzanneModel, &normalColorShader);
	world.addEntity("suzanne", &suzanne);
	WorldEntity barrel("barrel", &barrelModel, &basicShader);
	world.addEntity("barrel", &barrel);
	WorldEntity terrain("terrain", &terrainModel, &basicShader);
	world.addEntity("terrain", &terrain);

	WorldEntity skullRatCube("skullRatCube", &skullRatCubeModel, &basicShader);
	world.addEntity("skullRatCube", &skullRatCube);
	WorldEntity test("test", &skullRatCubeModel, &basicShader); // multiple entities can be linked to the same model.
	world.addEntity("test", &test);
	WorldEntity test2("test2", &skullRatCubeModel, &basicShader); // multiple entities can be linked to the same model.
	world.addEntity("test2", &test2);



	barrel.position = glm::vec3(50.0, -1.0f, 0.0f);
	barrel.scaleUp(glm::vec3(20.0f));
	suzanne.scaleUp(glm::vec3(30.0f));
	suzanne.translate(glm::vec3(-440.0f, 140.0f, -250.0f));
	lamp.scaleUp(glm::vec3(30.0f));
	terrain.scaleUp(glm::vec3(10000.0f));

	skullRatCube.scaleUp(glm::vec3(20.0f));
	skullRatCube.translate(glm::vec3(400.0f, 20.0f, 150.0f));

	Camera camera(width, height, glm::vec3(0.0f, 4.0f, 40.0f)); // init camera

	// CubeMap cubeMap;
	// Shader skyboxShader("skybox.vert", "skybox.frag");
	// skyboxShader.Activate();
	// glUniform1i(glGetUniformLocation(skyboxShader.ID, "skybox"), 0);

// ************************************************* phys ************************************** //
	// create world
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
	btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	btVector3 boxHalfExtents(1.0, 1.0, 1.0);
	// btBoxShape* boxShape = new btBoxShape(boxHalfExtents);
	btCollisionShape* boxShape = new btBoxShape(boxHalfExtents);
	
	// Create a rigid body: You will need to create a btRigidBody object to represent 
	// the box in the physics simulation. You will need to specify the mass, the initial
	// position, and the rotation of the box, as well as the shape, and motion state of the box.

	btTransform boxTransform;
	boxTransform.setIdentity();
	boxTransform.setOrigin(btVector3(0, 50, 0));

	btTransform boxTransform2;
	boxTransform2.setIdentity();
	boxTransform2.setOrigin(btVector3(0, 52.5, 0));

	btScalar boxMass = 1;
	btVector3 boxInertia(0, 0, 0);
	boxShape->calculateLocalInertia(boxMass, boxInertia);

	btDefaultMotionState* boxMotionState = new btDefaultMotionState(boxTransform);
	btRigidBody::btRigidBodyConstructionInfo boxRigidBodyCI(boxMass, boxMotionState, boxShape, boxInertia);
	btRigidBody* boxRigidBody = new btRigidBody(boxRigidBodyCI);

	dynamicsWorld->addRigidBody(boxRigidBody);

	btDefaultMotionState* boxMotionState2 = new btDefaultMotionState(boxTransform2);
	btRigidBody::btRigidBodyConstructionInfo boxRigidBodyCI2(boxMass, boxMotionState2, boxShape, boxInertia);
	btRigidBody* boxRigidBody2 = new btRigidBody(boxRigidBodyCI2);

	dynamicsWorld->addRigidBody(boxRigidBody2);

	// ground
	btVector3 planeNormal(0,1,0);
	btScalar planeConstant = 0;
	btCollisionShape* groundShape = new btStaticPlaneShape(planeNormal,planeConstant);

	btDefaultMotionState* groundMotionState = new btDefaultMotionState();
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0,0,0));
	groundMotionState->setWorldTransform(groundTransform);

	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addCollisionObject(groundRigidBody);

	groundRigidBody->setCollisionFlags(groundRigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	groundRigidBody->setActivationState(DISABLE_DEACTIVATION);

//	dynamicsWorld->setGravity(btVector3(0, -9.8f, 0));

// ************************************************************************************** //

	FpsCounter fpsCounter;
	GUI gui(window);
	float rotation = 0.0f;
	double prevTime = glfwGetTime();
	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		camera.Inputs(window);
		if ( camera.Position.y < 0.2f ) camera.Position.y = 0.20f;
		float crntTime = glfwGetTime();
		float timeStep = crntTime - prevTime;
		if (timeStep >= 1 / 60)
		{
			rotation += 0.5f;
			prevTime = crntTime;
		}

		// *******************   bullet phys **************
		dynamicsWorld->stepSimulation(0.01666666666f, 10);

		// Retrieve the body's new position and rotation: To retrieve the box's new position and rotation, 
		// you can use the getWorldTransform function of the box's motion state.
		{
			btTransform boxTransform;
			boxMotionState->getWorldTransform(boxTransform);
			btVector3 newPosition = boxTransform.getOrigin();
			btQuaternion newRotation = boxTransform.getRotation();
			test.position=glm::make_vec3(newPosition.m_floats);
			glm::mat4 tmp_rotation_matrix = glm::mat4_cast(glm::quat(newRotation.x(), newRotation.y(), newRotation.z(), newRotation.w()));
			test.setOrientation(tmp_rotation_matrix);
		}
		
		{
			btTransform boxTransform;
			boxMotionState2->getWorldTransform(boxTransform);
			btVector3 newPosition = boxTransform.getOrigin();
			btQuaternion newRotation = boxTransform.getRotation();
			test2.position=glm::make_vec3(newPosition.m_floats);
			glm::mat4 tmp_rotation_matrix = glm::mat4_cast(glm::quat(newRotation.x(), newRotation.y(), newRotation.z(), newRotation.w()));
			test2.setOrientation(tmp_rotation_matrix);
		}

		// Apply forces or torques: You can apply forces or torques to the box to make it move 
		// around or rotate, by calling applyCentralForce or applyTorque on the rigid body.
		//btVector3 force(1.0, 0.0, 0.0);
		//boxRigidBody->applyCentralForce(force);

		// ************************************************

		// 3d space positioning
		skullRatCube.rotate(0.04f, glm::vec3(0.0f, 1.0f, 0.0f));
		//suzanne.position = glm::vec3(sin(crntTime), 0.0f, cos(crntTime)) * 5.0f;
		
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

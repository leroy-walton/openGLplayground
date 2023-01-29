#ifndef MAINAPP_H
#define MAINAPP_H

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


class MainApp
{
public:
    static constexpr unsigned int width = 2000;
    static constexpr unsigned int height = 1000;
    void run();
    MainApp();
    ~MainApp();
    MainApp(const MainApp &) = delete;
    MainApp &operator=(const MainApp &) = delete;

private:
    void initGlfwWindow();
    void initOpenGl();
    GLFWwindow* m_window;
};

#endif
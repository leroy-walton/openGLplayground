#ifndef GUI_CLASS_H
#define GUI_CLASS_H

#include "GL/glew.h"
#include <map>
#include <string>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "World.h"

class GUI
{
public:
	GUI(GLFWwindow *window);
	void drawGUI(double fps, World *world);

private:
};

#endif

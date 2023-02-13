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

class GUI
{
public:
	GUI(GLFWwindow *window);
	void drawGUI(double fps);

private:
};

#endif

#ifndef GUI_CLASS_H
#define GUI_CLASS_H

#include <GLFW/glfw3.h>
#include <map>
#include <string>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>

class GUI
{
public:
	GUI(GLFWwindow *window);
	void draw(double fps);
	// void draw(double fps, std::map<std::string, SceneItem*> *pItems);
private:
};

#endif

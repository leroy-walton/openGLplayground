#include "GUI.h"

GUI::GUI(GLFWwindow *window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	const char *glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void GUI::drawGUI(double fps, World *world)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	{
		ImGui::NewFrame();
		ImGui::Begin("engine_demo v0.0.1");
		ImGui::Text("fps %f", fps);
		ImGui::Text("show/hide objects");
		for ( std::map<std::string, WorldEntity*>::iterator itr  = world->_entities.begin(); itr != world->_entities.end(); ++itr) {
			Model* model = itr->second->getModel();
			WorldEntity *entity = itr->second;
			ImGui::Checkbox(itr->first.c_str(), &(entity->isEnabled));
		}

		ImGui::End();
		ImGui::Render();
	}
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

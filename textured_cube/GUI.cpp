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
};

void GUI::draw(double fps, std::map<std::string, bool> &switches)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	{
		ImGui::NewFrame();
		ImGui::Begin("Bored v0.0.1-03");
		ImGui::Text("fps %f", fps);
		ImGui::Text("show/hide objects");
		for (std::map<std::string, bool>::iterator itr = switches.begin(); itr != switches.end(); ++itr)
		{
			ImGui::Checkbox(itr->first.c_str(), &itr->second);
		}
		ImGui::End();
		ImGui::Render();
	}
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
};
/*
void GUI::draw(double fps, std::map<std::string, SceneItem*> *pItems)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	{
		ImGui::NewFrame();
		ImGui::Begin("Bored v0.0.1-03");
		ImGui::Text("fps %f", fps);
		ImGui::Text("show/hide objects");
		 // std::cout << "GUI::draw start\n";
		for (std::map<std::string,SceneItem*>::iterator itr = pItems->begin(); itr != pItems->end(); ++itr) {
			SceneItem* item = itr->second;
			// std::cout << item->getName() << " " << &(item->isEnabled) << "\n";
			ImGui::Checkbox(itr->first.c_str(), &(item->isEnabled));
		}
		ImGui::End();
		ImGui::Render();
		// std::cout << "GUI::draw end\n";
	}
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
*/

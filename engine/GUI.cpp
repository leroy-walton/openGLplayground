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

void GUI::drawGUI(double fps)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	{
		ImGui::NewFrame();
		ImGui::Begin("engine_demo v0.0.2");
		ImGui::Text("fps %f", fps);
		ImGui::End();
		ImGui::Render();
	}
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::drawGUI(double fps, Camera camera)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	{
		ImGui::NewFrame();
		ImGui::Begin("engine_demo v0.0.2");
		ImGui::Text("fps %f", fps);
		ImGui::Text("CamPos %.2f, %.2f, %.2f", camera.position.x, camera.position.y, camera.position.z);
		ImGui::End();
		ImGui::Render();
	}
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
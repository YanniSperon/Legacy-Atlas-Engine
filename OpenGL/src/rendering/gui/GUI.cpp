#include "GUI.h"
#include "Global.h"
#include "IO.h"
#include "Window.h"
#include "System.h"
#include "ShapeGenerator.h"
#include "Loader.h"

#include <algorithm>

#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "imgui/imgui_internal.h"

namespace Atlas {
	static ImFont* font = nullptr;

	void GUI::Initialize(GLFWwindow* window)
	{
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;

		io.IniFilename = NULL;

		font = io.Fonts->AddFontFromFileTTF(System::ConvertFilePathToAbsolute("res/fonts/arial/arial.ttf").c_str(), 16);

		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();
	}

	void GUI::LoadLevelEditorGUI(GLFWwindow* window, bool& EnableWireframe)
	{
		ImGui_ImplGlfwGL3_NewFrame();
		ImGui::PushFont(font);
		Window::DrawUI(window, EnableWireframe);
		ImGui::PopFont();
	}

	void GUI::LoadPhysicsSimulatorGUI()
	{
		ImGui_ImplGlfwGL3_NewFrame();
		ImGui::PushFont(font);
		Window::DrawFPSCounter();
		System::DrawConsole(0.0f);
		ImGui::PopFont();
	}

	void GUI::Draw()
	{
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
	}
	void GUI::Terminate()
	{
		ImGui_ImplGlfwGL3_Shutdown();
		ImGui::DestroyContext();
	}
}

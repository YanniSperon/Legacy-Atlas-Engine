#include "GUI.h"
#include "Global.h"
#include "IO.h"
#include "Window.h"
#include "System.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

namespace Atlas {

	void GUI::Initialize(GLFWwindow* window)
	{
		ImGui::CreateContext();

		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();
	}

	void GUI::LoadLevelEditorGUI(GLFWwindow* window, LevelEditor::EditorType currentEditorType, LevelEditor::Mode currentMode, unsigned int& selectedObject)
	{
		ImGui_ImplGlfwGL3_NewFrame();
		static bool EnableDebug = true;
		static bool EnableSpawnMenu = true;
		static bool EnableConsole = true;
		static bool EnableInfoPage = true;
		static bool EnableFileManager = true;
		static bool ShouldToggleVSync = false;
		static bool GUIEnabled = true;
		static bool EnableObjectInfoPage = true;
		static bool EnableWireframe = false;
		if (Global::Variables.keyIn.leftAltPressed) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			Global::Variables.enableMouseMove = false;
		}
		if (Global::Variables.keyIn.leftAltReleased) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			Global::Variables.enableMouseMove = true;
			glfwSetCursorPos(window, Global::Variables.mouseX, Global::Variables.mouseY);
		}
		if (Global::Variables.keyIn.tildePressed) {
			EnableConsole = !EnableConsole;
		}

		{
			ImGui::Begin("File", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
			ImGui::Checkbox("Enable Info Page##infoControl", &EnableInfoPage);
			ImGui::Checkbox("Enable Spawn Menu##spawnControl", &EnableSpawnMenu);
			ImGui::Checkbox("Enable Debug Options##debugControl", &EnableDebug);
			ImGui::Checkbox("Enable Object Settings##objectSettingsControl", &EnableObjectInfoPage);
			ImGui::Separator();
			if (ImGui::Button("Save##saveButton")) {
				Global::Variables.currentScene.Save("res/other/", "level.lvl");
			}
			if (ImGui::Button("Close##closeButton")) {
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
			ImGui::End();
		}

		if (EnableDebug) {
			Window::DrawDebug(EnableConsole, EnableWireframe);
		}

		if (EnableSpawnMenu) {
			Window::DrawSpawnWindow(Global::Variables.currentScene.objectsOnScene, selectedObject);
		}

		if (EnableInfoPage) {
			Window::DrawInfoWindow(currentEditorType, currentMode);
		}

		if (EnableObjectInfoPage) {
			if (Global::Variables.currentScene.objectsOnScene.size() > 0 && selectedObject < Global::Variables.currentScene.objectsOnScene.size() && selectedObject >= 0) {
				Window::DrawObjectSettingsWindow(Global::Variables.currentScene.objectsOnScene[selectedObject]);
			}
		}

		if (EnableConsole) {
			System::DrawConsole();
		}

		if (EnableFileManager) {
			Window::DrawFileManager(window);
		}
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

#include "GUI.h"
#include "Global.h"
#include "IO.h"
#include "Window.h"
#include "System.h"

#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "imgui/imgui_internal.h"

namespace Atlas {

	void GUI::Initialize(GLFWwindow* window)
	{
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;

		io.IniFilename = NULL;

		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();
	}

	void GUI::LoadLevelEditorGUI(GLFWwindow* window, LevelEditor::EditorType currentEditorType, LevelEditor::Mode currentMode, unsigned int& selectedObject, bool& EnableWireframe)
	{
		ImGui_ImplGlfwGL3_NewFrame();
		static bool EnableDebug = true;
		static bool EnableSpawnMenu = true;
		static bool EnableConsole = true;
		static bool EnableInfoPage = true;
		static bool EnableFileManager = true;
		static bool EnablePhysicsManager = true;
		static bool ShouldToggleVSync = false;
		static bool GUIEnabled = true;
		static bool EnableObjectInfoPage = true;
		static bool EnablePostProcessingManager = true;
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
			ImGui::SetNextWindowPos(ImVec2((20.0f / 1920.0f) * ((float)Global::Variables.currentWidth), (20.0f / 1080.0f) * ((float)Global::Variables.currentHeight)));
			ImGui::SetNextWindowSize(ImVec2((190.0f / 1920.0f) * ((float)Global::Variables.currentWidth), (245.0f / 1080.0f) * ((float)Global::Variables.currentHeight)));
			ImGui::Begin("File", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
			ImGui::Checkbox("Enable Debug Options##debugControl", &EnableDebug);
			ImGui::Checkbox("Enable File Manager##filemanager", &EnableFileManager);
			ImGui::Checkbox("Enable Spawn Menu##spawnControl", &EnableSpawnMenu);
			ImGui::Checkbox("Enable Info Page##infoControl", &EnableInfoPage);
			ImGui::Checkbox("Enable Object Settings##objectSettingsControl", &EnableObjectInfoPage);
			ImGui::Checkbox("Enable PSFX Manager##psfxmanager", &EnablePostProcessingManager);
			ImGui::Checkbox("Enable Physics Manager##physicstoggle", &EnablePhysicsManager);
			ImGui::Separator();
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
			if (ImGui::Button("Save##saveButton", ImVec2(ImGui::GetWindowSize().x * 0.5f, 0.0f))) {
				Global::Variables.currentScene.Save("res/other/", "level.lvl");
			}
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
			if (ImGui::Button("Close##closeButton", ImVec2(ImGui::GetWindowSize().x * 0.5f, 0.0f))) {
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

		if (EnablePostProcessingManager) {
			Window::DrawPostProcessingManager(window);
		}

		if (EnablePhysicsManager) {
			Window::DrawPhysicsManager();
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

#include "Window.h"
#include "System.h"
#include "Global.h"
#include "Loader.h"
#include "ShapeGenerator.h"
#include "PostProcessor.h"
#include "Convert.h"
#include "PhysicsSimulator.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "imgui/imgui_internal.h"

#include <algorithm>

namespace Atlas {
	static int AddValueFile(std::string directory, std::string file, int value) {
		if (value == 0) {
			if (System::DoesFileExist(directory + file)) {
				return AddValueFile(directory, file, value + 1);
			}
			else {
				return value;
			}
		}
		else {
			if (System::DoesFileExist(directory + std::to_string(value) + file)) {
				return AddValueFile(directory, file, value + 1);
			}
			else {
				return value;
			}
		}
	}

	static int AddValueMesh(std::string meshName, int value) {
		if (value == 0) {
			if (Global::Variables.loadedMeshCache.find(meshName) != Global::Variables.loadedMeshCache.end()) {
				return AddValueMesh(meshName, value + 1);
			}
			else {
				return value;
			}
		}
		else {
			if (Global::Variables.loadedMeshCache.find(meshName + std::to_string(value)) != Global::Variables.loadedMeshCache.end()) {
				return AddValueMesh(meshName, value + 1);
			}
			else {
				return value;
			}
		}
	}

	static int AddValueTexture(std::string meshName, int value) {
		if (value == 0) {
			if (Global::Variables.loadedTextureCache.find(meshName) != Global::Variables.loadedTextureCache.end()) {
				return AddValueTexture(meshName, value + 1);
			}
			else {
				return value;
			}
		}
		else {
			if (Global::Variables.loadedTextureCache.find(meshName + std::to_string(value)) != Global::Variables.loadedTextureCache.end()) {
				return AddValueTexture(meshName, value + 1);
			}
			else {
				return value;
			}
		}
	}

	static int AddValueShader(std::string meshName, int value) {
		if (value == 0) {
			if (Global::Variables.loadedShaderCache.find(meshName) != Global::Variables.loadedShaderCache.end()) {
				return AddValueShader(meshName, value + 1);
			}
			else {
				return value;
			}
		}
		else {
			if (Global::Variables.loadedShaderCache.find(meshName + std::to_string(value)) != Global::Variables.loadedShaderCache.end()) {
				return AddValueShader(meshName, value + 1);
			}
			else {
				return value;
			}
		}
	}

	void DrawLoadButtons(GLFWwindow* window) {
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.125f).x);
		if (ImGui::Button("Load new mesh##loadmeshbutton1", ImVec2(ImGui::GetWindowSize().x * 0.75f, 0.0f))) {
			std::string file = System::FileOpenDialog("Select a mesh to load", "OBJECT File\0*.obj\0", window);
			std::replace(file.begin(), file.end(), '\\', '/');
			if (file != "INVALID") {
				System::Warn("Loading mesh \"" + file + "\"");
				std::string physicalLocation = "";
				std::size_t lastSlashPos = file.find_last_of("/");
				std::string meshDir = "";
				std::string meshName = "";
				if (lastSlashPos != std::string::npos) {
					meshDir = file.substr(0, lastSlashPos + 1);
					meshName = file.substr(lastSlashPos + 1);
				}
				else {
					meshName = file;
				}
				physicalLocation = meshDir + meshName;
				if (System::IsFilePathInWorkingDirectory(file)) {
					file = System::ConvertFilePathToLocal(file);
					lastSlashPos = file.find_last_of("/");
					meshDir = "";
					meshName = "";
					if (lastSlashPos != std::string::npos) {
						meshDir = file.substr(0, lastSlashPos + 1);
						meshName = file.substr(lastSlashPos + 1);
					}
					else {
						meshName = file;
					}
					physicalLocation = meshDir + meshName;
				}
				else {
					std::string val = std::to_string(AddValueFile("res/models/", meshName, 0));
					if (val == "0") {
						physicalLocation = System::ConvertFilePathToAbsolute("res/models/" + meshName);
					}
					else {
						physicalLocation = System::ConvertFilePathToAbsolute("res/models/" + val + meshName);
					}
					System::CopyFileAtlas(file, physicalLocation);
					physicalLocation = System::ConvertFilePathToLocal(physicalLocation);
					lastSlashPos = physicalLocation.find_last_of("/");
					meshDir = "";
					meshName = "";
					if (lastSlashPos != std::string::npos) {
						meshDir = physicalLocation.substr(0, lastSlashPos + 1);
						meshName = physicalLocation.substr(lastSlashPos + 1);
					}
					else {
						meshName = physicalLocation;
					}
				}
				std::string val = std::to_string(AddValueMesh(meshName, 0));
				if (val == "0") {
					Global::Variables.loadedMeshCache[meshName] = (physicalLocation);
				}
				else {
					Global::Variables.loadedMeshCache[val + meshName] = (physicalLocation);
				}
				try {
					if (Global::Variables.meshCache.find(meshDir + meshName) == Global::Variables.meshCache.end()) {
						Global::Variables.meshCache[meshDir + meshName] = ShapeGenerator::loadTexturedShape(meshDir, meshName);
					}
				}
				catch (const std::exception& e) {
					try {
						if (Global::Variables.meshCache.find(meshDir + meshName) == Global::Variables.meshCache.end()) {
							Global::Variables.meshCache[meshDir + meshName] = ShapeGenerator::loadShape(physicalLocation);
						}
					}
					catch (const std::exception& e) {
						System::Err("Unrecognized file type, must be wavefront .obj file following the specified format");
					}
				}
				System::Warn("Mesh \"" + file + "\" loaded");
			}
		}
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.125f).x);
		if (ImGui::Button("Load new texture##loadtexturebutton1", ImVec2(ImGui::GetWindowSize().x * 0.75f, 0.0f))) {
			std::string file = System::FileOpenDialog("Select a texture to load", "Portable Network Graphics\0*.png\0", window);
			std::replace(file.begin(), file.end(), '\\', '/');
			if (file != "INVALID") {
				System::Warn("Loading texture \"" + file + "\"");
				std::string physicalLocation = "";
				std::size_t lastSlashPos = file.find_last_of("/");
				std::string textureDir = "";
				std::string textureName = "";
				if (lastSlashPos != std::string::npos) {
					textureDir = file.substr(0, lastSlashPos + 1);
					textureName = file.substr(lastSlashPos + 1);
				}
				else {
					textureName = file;
				}
				physicalLocation = textureDir + textureName;
				if (System::IsFilePathInWorkingDirectory(file)) {
					file = System::ConvertFilePathToLocal(file);
					lastSlashPos = file.find_last_of("/");
					textureDir = "";
					textureName = "";
					if (lastSlashPos != std::string::npos) {
						textureDir = file.substr(0, lastSlashPos + 1);
						textureName = file.substr(lastSlashPos + 1);
					}
					else {
						textureName = file;
					}
					physicalLocation = textureDir + textureName;
				}
				else {
					std::string val = std::to_string(AddValueFile("res/images/textures/", textureName, 0));
					if (val == "0") {
						physicalLocation = System::ConvertFilePathToAbsolute("res/images/textures/" + textureName);
					}
					else {
						physicalLocation = System::ConvertFilePathToAbsolute("res/images/textures/" + val + textureName);
					}
					System::CopyFileAtlas(file, physicalLocation);
					physicalLocation = System::ConvertFilePathToLocal(physicalLocation);
					lastSlashPos = physicalLocation.find_last_of("/");
					textureDir = "";
					textureName = "";
					if (lastSlashPos != std::string::npos) {
						textureDir = physicalLocation.substr(0, lastSlashPos + 1);
						textureName = physicalLocation.substr(lastSlashPos + 1);
					}
					else {
						textureName = physicalLocation;
					}
				}
				std::string val = std::to_string(AddValueTexture(textureName, 0));
				if (val == "0") {
					Global::Variables.loadedTextureCache[textureName] = physicalLocation;
				}
				else {
					Global::Variables.loadedTextureCache[val + textureName] = physicalLocation;
				}
				if (Global::Variables.textureCache.find(textureDir + textureName) == Global::Variables.textureCache.end()) {
					Global::Variables.textureCache[textureDir + textureName] = Loader::LoadTexture(physicalLocation, GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
				}
				System::Warn("Texture \"" + file + "\" loaded");
			}
		}
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.125f).x);
		if (ImGui::Button("Load new shader##loadshaderbutton1", ImVec2(ImGui::GetWindowSize().x * 0.75f, 0.0f))) {
			std::string file = System::FileOpenDialog("Select a shader to load", "SHADER File\0*.shader\0", window);
			std::replace(file.begin(), file.end(), '\\', '/');
			if (file != "INVALID") {
				System::Warn("Loading shader \"" + file + "\"");
				std::string physicalLocation = "";
				std::size_t lastSlashPos = file.find_last_of("/");
				std::string shaderDir = "";
				std::string shaderName = "";
				if (lastSlashPos != std::string::npos) {
					shaderDir = file.substr(0, lastSlashPos + 1);
					shaderName = file.substr(lastSlashPos + 1);
				}
				else {
					shaderName = file;
				}
				physicalLocation = shaderDir + shaderName;
				if (System::IsFilePathInWorkingDirectory(file)) {
					file = System::ConvertFilePathToLocal(file);
					lastSlashPos = file.find_last_of("/");
					shaderDir = "";
					shaderName = "";
					if (lastSlashPos != std::string::npos) {
						shaderDir = file.substr(0, lastSlashPos + 1);
						shaderName = file.substr(lastSlashPos + 1);
					}
					else {
						shaderName = file;
					}
					physicalLocation = shaderDir + shaderName;
				}
				else {
					std::string val = std::to_string(AddValueFile("res/shaders/", shaderName, 0));
					if (val == "0") {
						physicalLocation = System::ConvertFilePathToAbsolute("res/shaders/" + shaderName);
					}
					else {
						physicalLocation = System::ConvertFilePathToAbsolute("res/shaders/" + val + shaderName);
					}
					System::CopyFileAtlas(file, physicalLocation);
					physicalLocation = System::ConvertFilePathToLocal(physicalLocation);
					lastSlashPos = physicalLocation.find_last_of("/");
					shaderDir = "";
					shaderName = "";
					if (lastSlashPos != std::string::npos) {
						shaderDir = physicalLocation.substr(0, lastSlashPos + 1);
						shaderName = physicalLocation.substr(lastSlashPos + 1);
					}
					else {
						shaderName = physicalLocation;
					}
				}
				std::string val = std::to_string(AddValueShader(shaderName, 0));
				if (val == "0") {
					Global::Variables.loadedShaderCache[shaderName] = physicalLocation;
				}
				else {
					Global::Variables.loadedShaderCache[val + shaderName] = physicalLocation;
				}

				if (Global::Variables.shaderCache.find(shaderDir + shaderName) == Global::Variables.shaderCache.end()) {
					Global::Variables.shaderCache[shaderDir + shaderName] = new Shader(physicalLocation);
				}
				System::Warn("Shader \"" + file + "\" loaded");
			}
		}
	}

	void Window::DrawUI(GLFWwindow* window, bool& EnableWireframe)
	{
		static bool EnableControl = true;
		static bool EnableConsole = true;
		static bool EnableSceneViewer = true;
		static bool ShouldToggleVSync = false;
		static bool GUIEnabled = true;
		static bool EnableObjectInfoPage = true;
		static bool EnablePostProcessingManager = true;
		static bool IsMovingCamera = true;
		if (Global::Variables.keyIn.leftAltPressed) {
			IsMovingCamera = !IsMovingCamera;
			glfwSetInputMode(window, GLFW_CURSOR, IsMovingCamera ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
			Global::Variables.enableMouseMove = IsMovingCamera;
			if (!IsMovingCamera) {
				glfwSetCursorPos(window, Global::Variables.currentWidth * 0.5, Global::Variables.currentHeight * 0.5);
			}
			else {
				glfwSetCursorPos(window, Global::Variables.mouseX, Global::Variables.mouseY);
			}
		}
		if (Global::Variables.keyIn.tildePressed) {
			EnableConsole = !EnableConsole;
		}

		{
			ImGui::SetNextWindowPos(ImVec2((335.0f / 1920.0f) * ((float)Global::Variables.currentWidth), (20.0f / 1080.0f) * ((float)Global::Variables.currentHeight)));
			ImGui::SetNextWindowSize(ImVec2((190.0f / 1920.0f) * ((float)Global::Variables.currentWidth), (330.0f / 1080.0f) * ((float)Global::Variables.currentHeight)));
			ImGui::Begin("File", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
			ImGui::Checkbox("Enable Scene Control##sceneControl", &EnableControl);
			ImGui::Checkbox("Enable Object Settings##objectSettingsControl", &EnableObjectInfoPage);
			ImGui::Checkbox("Enable PSFX Manager##psfxmanager", &EnablePostProcessingManager);
			ImGui::Checkbox("Enable Scene Viewer##scenetoggle", &EnableSceneViewer);
			ImGui::Checkbox("Enable Console##consoleControl", &EnableConsole);
			if (ImGui::Button("Toggle display mode##wireframetoggler", ImVec2(ImGui::GetWindowSize().x * 0.75f, 0.0f))) {
				if (EnableWireframe) {
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					EnableWireframe = false;
				}
				else {
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					EnableWireframe = true;
				}
			}
			ImGui::Separator();
			DrawLoadButtons(window);
			ImGui::Separator();
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
			if (ImGui::Button("Save##saveButton", ImVec2(ImGui::GetWindowSize().x * 0.5f, 0.0f))) {
				Global::Variables.currentScene.Save("res/other/", "level.lvl");
			}
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
			if (ImGui::Button("Quit##quitButton", ImVec2(ImGui::GetWindowSize().x * 0.5f, 0.0f))) {
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
			ImGui::End();
		}

		if (EnableControl) {
			Window::DrawControl(window, IsMovingCamera);
		}

		if (EnableObjectInfoPage) {
			Window::DrawObjectSettingsWindow();
		}

		if (EnableConsole) {
			System::DrawConsole(315.0f);
		}

		if (EnablePostProcessingManager) {
			Window::DrawPostProcessingManager(window);
		}

		if (EnableSceneViewer) {
			Window::DrawSceneViewer();
		}
	}

	void Window::DrawControl(GLFWwindow* window, bool& isMovingCamera)
	{
		ImGui::SetNextWindowPos(ImVec2((550.0f / 1920.0f) * ((float)Global::Variables.currentWidth), (20.0f / 1080.0f) * ((float)Global::Variables.currentHeight)));
		ImGui::SetNextWindowSize(ImVec2((240.0f / 1920.0f) * ((float)Global::Variables.currentWidth), (120.0f / 1080.0f) * ((float)Global::Variables.currentHeight)));
		ImGui::Begin("Control", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.12f).x);
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Separator();
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.1f).x);
		ImGui::InputFloat3("Gravity##gravityfloatin", &(Global::Variables.currentScene.sceneSettings.gravity[0]), 3);
		ImGui::Separator();
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
		if (ImGui::Button("Start##startbutton", ImVec2(ImGui::GetWindowSize().x * 0.50f, 0.0f))) {
			System::AddPriorityEventToGlobalQueue([&]() {
				System::Log("Loading physics: " + std::string(window != nullptr ? "Good" : "Not good"));
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				glfwSetCursorPos(window, Global::Variables.mouseX, Global::Variables.mouseY);
				Global::Variables.enableMouseMove = true;
				isMovingCamera = false; // Set to false so when this is next checked (when simulation is over) it is in sync
				PhysicsSimulator::LaunchSimulation(&Global::Variables.currentScene);
			});
		}
		ImGui::Separator();
		ImGui::End();
	}

	void Window::DrawFPSCounter()
	{
		ImGui::SetNextWindowPos(ImVec2((20.0f / 1920.0f) * ((float)Global::Variables.currentWidth), (20.0f / 1080.0f) * ((float)Global::Variables.currentHeight)));
		ImGui::SetNextWindowSize(ImVec2((240.0f / 1920.0f) * ((float)Global::Variables.currentWidth), (55.0f / 1080.0f) * ((float)Global::Variables.currentHeight)));
		ImGui::Begin("Debug", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.12f).x);
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	void Window::DrawPostProcessingManager(GLFWwindow* window)
	{
		static std::string currentSelectedPSFX = "";
		ImGui::SetNextWindowPos(ImVec2((1605.0f / 1920.0f) * ((float)Global::Variables.currentWidth), (910.0f / 1080.0f) * ((float)Global::Variables.currentHeight)));
		ImGui::SetNextWindowSize(ImVec2((295.0f / 1920.0f) * ((float)Global::Variables.currentWidth), (150.0f / 1080.0f) * ((float)Global::Variables.currentHeight)));
		ImGui::Begin("Post-Processing Manager", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.125f).x);
		if (ImGui::Button("Load new PSFX shader##loadpsfxshader", ImVec2(ImGui::GetWindowSize().x * 0.75f, 0.0f))) {
			std::string file = System::FileOpenDialog("Select a mesh to load", "SHADER File\0*.shader\0", window);
			std::replace(file.begin(), file.end(), '\\', '/');
			if (file != "INVALID") {
				System::Warn("Loading shader \"" + file + "\"");
				std::string physicalLocation = "";
				std::size_t lastSlashPos = file.find_last_of("/");
				std::string shaderDir = "";
				std::string shaderName = "";
				if (lastSlashPos != std::string::npos) {
					shaderDir = file.substr(0, lastSlashPos + 1);
					shaderName = file.substr(lastSlashPos + 1);
				}
				else {
					shaderName = file;
				}
				physicalLocation = shaderDir + shaderName;
				if (System::IsFilePathInWorkingDirectory(file)) {
					file = System::ConvertFilePathToLocal(file);
					lastSlashPos = file.find_last_of("/");
					shaderDir = "";
					shaderName = "";
					if (lastSlashPos != std::string::npos) {
						shaderDir = file.substr(0, lastSlashPos + 1);
						shaderName = file.substr(lastSlashPos + 1);
					}
					else {
						shaderName = file;
					}
					physicalLocation = shaderDir + shaderName;
				}
				else {
					std::string val = std::to_string(AddValueFile("res/shaders/", shaderName, 0));
					if (val == "0") {
						physicalLocation = System::ConvertFilePathToAbsolute("res/shaders/" + shaderName);
					}
					else {
						physicalLocation = System::ConvertFilePathToAbsolute("res/shaders/" + val + shaderName);
					}
					System::CopyFileAtlas(file, physicalLocation);
					physicalLocation = System::ConvertFilePathToLocal(physicalLocation);
					lastSlashPos = physicalLocation.find_last_of("/");
					shaderDir = "";
					shaderName = "";
					if (lastSlashPos != std::string::npos) {
						shaderDir = physicalLocation.substr(0, lastSlashPos + 1);
						shaderName = physicalLocation.substr(lastSlashPos + 1);
					}
					else {
						shaderName = physicalLocation;
					}
				}
				std::string val = std::to_string(AddValueShader(shaderName, 0));
				if (val == "0") {
					Global::Variables.loadedPostProcessingShaderCache[shaderName] = physicalLocation;
				}
				else {
					Global::Variables.loadedPostProcessingShaderCache[val + shaderName] = physicalLocation;
				}

				if (Global::Variables.shaderCache.find(shaderDir + shaderName) == Global::Variables.shaderCache.end()) {
					Global::Variables.shaderCache[shaderDir + shaderName] = new Shader(physicalLocation);
				}
				System::Warn("Shader \"" + file + "\" loaded");
			}
		}
		ImGui::Separator();
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.15f).x);
		ImGui::Text("Current post-processing shader");
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.175f).x);
		if (ImGui::BeginCombo("##psfxcombo", currentSelectedPSFX.c_str()))
		{
			for (auto it : Global::Variables.loadedPostProcessingShaderCache) {
				bool is_selected = (currentSelectedPSFX == it.first);
				if (ImGui::Selectable(it.first.c_str(), is_selected)) {
					currentSelectedPSFX = it.first;
					if (is_selected) {
						ImGui::SetItemDefaultFocus();
					}
				}
			}
			ImGui::EndCombo();
		}
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
		if (ImGui::Button("Apply##t1", ImVec2(ImGui::GetWindowSize().x * 0.50f, 0.0f))) {
			PostProcessor::ChangeEffect(Global::Variables.loadedPostProcessingShaderCache[currentSelectedPSFX]);
		}
		ImGui::End();
	}

	std::size_t GetIndexInSelectedObjectsVector(Object* obj) {
		for (std::size_t i = 0; i < Global::Variables.selectedObjects.size(); ++i) {
			if (Global::Variables.selectedObjects[i] == obj) {
				return i;
			}
		}
		return std::string::npos;
	}

	std::size_t GetIndexInSceneObjectsVector(Object* obj) {
		for (std::size_t i = 0; i < Global::Variables.currentScene.objectsOnScene.size(); ++i) {
			if (Global::Variables.currentScene.objectsOnScene[i] == obj) {
				return i;
			}
		}
		return std::string::npos;
	}

	std::size_t GetIndexInSceneLightsVector(Object* obj) {
		for (std::size_t i = 0; i < Global::Variables.currentScene.lightsOnScene.size(); ++i) {
			if (Global::Variables.currentScene.lightsOnScene[i] == obj) {
				return i;
			}
		}
		return std::string::npos;
	}
	
	void Window::DrawObjectSettingsWindow()
	{
		static char* items[] = { "Rendering", "Lighting", "Position" };
		static char* current_item = items[0];
		static std::string currentSelectedMesh = "";
		static std::string currentSelectedTexture = "";
		static std::string currentSelectedShader = "";
		static char name[1024];
		Object* object = Global::Variables.selectedObjects.size() > 0 ? Global::Variables.selectedObjects[0] : nullptr;
		static Object* lastObject = object;

		auto loadObjectData = [&](Object* o) {
			current_item = items[0];
			switch (o->GetTypeEnum()) {
			case cubeInvertedLighting:
				currentSelectedMesh = "cubeInvertedLighting";
				break;
			case cubeModel:
				currentSelectedMesh = "cubeModel";
				break;
			case skyBox:
				currentSelectedMesh = "skyBox";
				break;
			case normalModel:
				currentSelectedMesh = o->GetModelFileName();
				break;
			}
			currentSelectedTexture = o->GetTextureName();
			currentSelectedShader = o->GetShaderName();
			strcpy(name, o->GetDisplayName().c_str());
		};

		if (lastObject != object) {
			lastObject = object;
			if (object) {
				loadObjectData(object);
			}
		}

		ImGui::SetNextWindowPos(ImVec2((1605.0f / 1920.0f) * ((float)Global::Variables.currentWidth), (20.0f / 1080.0f) * ((float)Global::Variables.currentHeight)));
		ImGui::SetNextWindowSize(ImVec2((295.0f / 1920.0f) * ((float)Global::Variables.currentWidth), (870.0f / 1080.0f) * ((float)Global::Variables.currentHeight)));
		ImGui::Begin("Object Settings", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		if (object) {
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
			if (ImGui::BeginCombo("##combo", current_item))
			{
				for (int n = 0; n < IM_ARRAYSIZE(items); n++)
				{
					bool is_selected = (current_item == items[n]);
					if (ImGui::Selectable(items[n], is_selected)) {
						current_item = items[n];
						if (is_selected) {
							ImGui::SetItemDefaultFocus();
						}
					}
				}
				ImGui::EndCombo();
			}

			ImGui::Text("");
			ImGui::Separator();

			if (current_item == "Rendering") {
				ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.4f).x);
				ImGui::Text("Model");
				ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.1f).x);
				if (ImGui::BeginCombo("Model##modelcombo", currentSelectedMesh.c_str()))
				{
					for (auto it : Global::Variables.loadedMeshCache) {
						bool is_selected = (currentSelectedMesh == it.first);
						if (ImGui::Selectable(it.first.c_str(), is_selected)) {
							currentSelectedMesh = it.first;
							if (is_selected) {
								ImGui::SetItemDefaultFocus();
							}
						}
					}
					{
						bool is_selected = (currentSelectedMesh == "cubeModel");
						if (ImGui::Selectable("cubeModel", is_selected)) {
							currentSelectedMesh = "cubeModel";
							if (is_selected) {
								ImGui::SetItemDefaultFocus();
							}
						}
					}
					{
						bool is_selected = (currentSelectedMesh == "skyBox");
						if (ImGui::Selectable("skyBox", is_selected)) {
							currentSelectedMesh = "skyBox";
							if (is_selected) {
								ImGui::SetItemDefaultFocus();
							}
						}
					}
					{
						bool is_selected = (currentSelectedMesh == "cubeInvertedLighting");
						if (ImGui::Selectable("cubeInvertedLighting", is_selected)) {
							currentSelectedMesh = "cubeInvertedLighting";
							if (is_selected) {
								ImGui::SetItemDefaultFocus();
							}
						}
					}
					ImGui::EndCombo();
				}
				ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
				if (ImGui::Button("Apply##m1", ImVec2(ImGui::GetWindowSize().x * 0.50f, 0.0f))) {
					Filepath meshpath = System::SeperateFilepath(Global::Variables.loadedMeshCache[currentSelectedMesh]);
					type t = normalModel;
					if (currentSelectedMesh == "skyBox") {
						t = skyBox;
					}
					else if (currentSelectedMesh == "cubeModel") {
						t = cubeModel;
					}
					else if (currentSelectedMesh == "cubeInvertedLighting") {
						t = cubeInvertedLighting;
					}
					if (object->GetType() == "Light") {
						Light* newObject = new Light(t, std::string(meshpath.directory), std::string(meshpath.filename), (*(static_cast<Light*>(object))));

						std::size_t indexInSelectedObjects = GetIndexInSelectedObjectsVector(object);
						if (indexInSelectedObjects != std::string::npos) {
							Global::Variables.selectedObjects[indexInSelectedObjects] = newObject;
						}

						std::size_t indexInSceneLights = GetIndexInSceneLightsVector(object);
						if (indexInSceneLights != std::string::npos) {
							Global::Variables.currentScene.lightsOnScene[indexInSceneLights] = newObject;
						}
						delete object;
						object = static_cast<Object*>(newObject);
					}
					else {
						Object* newObject = new Object(t, std::string(meshpath.directory), std::string(meshpath.filename), (*object));

						std::size_t indexInSelectedObjects = GetIndexInSelectedObjectsVector(object);
						if (indexInSelectedObjects != std::string::npos) {
							Global::Variables.selectedObjects[indexInSelectedObjects] = newObject;
						}

						std::size_t indexInSceneObjects = GetIndexInSceneObjectsVector(object);
						if (indexInSceneObjects != std::string::npos) {
							Global::Variables.currentScene.objectsOnScene[indexInSceneObjects] = newObject;
						}
						delete object;
						object = newObject;
					}
				}
				ImGui::Separator();
				ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.4f).x);
				ImGui::Text("Texture");
				ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
				if (ImGui::BeginCombo("##texturecombo", currentSelectedTexture.c_str()))
				{
					for (auto it : Global::Variables.loadedTextureCache) {
						bool is_selected = (currentSelectedTexture == it.first);
						if (ImGui::Selectable(it.first.c_str(), is_selected)) {
							currentSelectedTexture = it.first;
							if (is_selected) {
								ImGui::SetItemDefaultFocus();
							}
						}
					}
					ImGui::EndCombo();
				}
				ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
				if (ImGui::Button("Apply##t1", ImVec2(ImGui::GetWindowSize().x * 0.50f, 0.0f))) {
					Filepath texpath = System::SeperateFilepath(Global::Variables.loadedTextureCache[currentSelectedTexture]);
					object->SetTexture(std::string(texpath.directory), std::string(texpath.filename));
				}
				ImGui::Separator();
				ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.4f).x);
				ImGui::Text("Shader");
				ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
				if (ImGui::BeginCombo("##shadercombo", currentSelectedShader.c_str()))
				{
					for (auto it : Global::Variables.loadedShaderCache) {
						bool is_selected = (currentSelectedTexture == it.first);
						if (ImGui::Selectable(it.first.c_str(), is_selected)) {
							currentSelectedShader = it.first;
							if (is_selected) {
								ImGui::SetItemDefaultFocus();
							}
						}
					}
					ImGui::EndCombo();
				}
				ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
				if (ImGui::Button("Apply##s1", ImVec2(ImGui::GetWindowSize().x * 0.50f, 0.0f))) {
					Filepath shaderpath = System::SeperateFilepath(Global::Variables.loadedShaderCache[currentSelectedShader]);
					object->SetShader(std::string(shaderpath.directory), std::string(shaderpath.filename));
				}
				ImGui::Separator();
				ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.4f).x);
				ImGui::Text("Display Name");
				ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
				ImGui::InputText("##entryeditor", name, IM_ARRAYSIZE(name));
				ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
				if (ImGui::Button("Apply##name1", ImVec2(ImGui::GetWindowSize().x * 0.50f, 0.0f))) {
					object->SetDisplayName(std::string(name));
				}

				ImGui::Separator();
			}
			else if (current_item == "Position") {

				ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.38f).x);
				ImGui::Text("Rotation");
				ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
				ImGui::InputFloat3("##in1", &((object->GetRotation())[0]));

				ImGui::Separator();

				ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.36f).x);
				ImGui::Text("Translation");
				ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
				ImGui::InputFloat3("##in2", &((object->GetTranslation())[0]));

				ImGui::Separator();

				ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.41f).x);
				ImGui::Text("Scale");
				ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
				ImGui::InputFloat3("##in3", &((object->GetScale())[0]));

				ImGui::Separator();
			}
			else if (current_item == "Lighting") {
				if (object->GetType() == "Light") {
					Light* lt = static_cast<Light*>(object);
					ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.27f).x);
					ImGui::Text("Ambient Color");
					ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
					ImGui::InputFloat3("##ambcolor", &((lt->GetLightIntensity().ambient)[0]));

					ImGui::Separator();

					ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.27f).x);
					ImGui::Text("Diffuse Color");
					ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
					ImGui::InputFloat3("##diffcolor", &((lt->GetLightIntensity().diffuse)[0]));

					ImGui::Separator();

					ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.27f).x);
					ImGui::Text("Specular Color");
					ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
					ImGui::InputFloat3("##speccolor", &((lt->GetLightIntensity().specular)[0]));

					ImGui::Separator();

				}
				else {
					ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.27f).x);
					ImGui::Text("Ambient Reflection");
					ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
					ImGui::InputFloat3("##lin2", &((object->GetMaterial().ambient)[0]));

					ImGui::Separator();

					ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.27f).x);
					ImGui::Text("Diffuse Reflection");
					ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
					ImGui::InputFloat3("##lin3", &((object->GetMaterial().diffuse)[0]));

					ImGui::Separator();

					ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.27f).x);
					ImGui::Text("Specular Reflection");
					ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
					ImGui::InputFloat3("##lin4", &((object->GetMaterial().specular)[0]));

					ImGui::Separator();

					ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.27f).x);
					ImGui::Text("Reflection Shininess");
					ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
					ImGui::SliderInt("##lin5", &((object->GetMaterial().shininess)), 0, 512);

					ImGui::Separator();
				}
			}
		}

		ImGui::End();
	}

	bool IsPrimarySelected(Object* o) {
		return (Global::Variables.selectedObjects.size() > 0) && (Global::Variables.selectedObjects[0] == o);
	}

	bool IsSelected(Object* o) {
		for (std::size_t i = 0; i < Global::Variables.selectedObjects.size(); ++i) {
			if (o == Global::Variables.selectedObjects[i]) {
				return true;
			}
		}
		return false;
	}

	void AddItemsBetweenToSelectedObjects(std::size_t front, std::size_t back) {
		if (front > back) {
			std::size_t temp = front;
			front = back;
			back = temp;
		}

		for (std::size_t i = front; i <= back; ++i) {
			if (i >= Global::Variables.currentScene.objectsOnScene.size()) {
				Global::Variables.selectedObjects.push_back(Global::Variables.currentScene.lightsOnScene[(i - Global::Variables.currentScene.objectsOnScene.size())]);
			}
			else {
				Global::Variables.selectedObjects.push_back(Global::Variables.currentScene.objectsOnScene[i]);
			}
		}
	}

	bool IsAlreadyInSelectedItems(Object* o) {
		for (std::size_t i = 0; i < Global::Variables.selectedObjects.size(); ++i) {
			if (o == Global::Variables.selectedObjects[i]) {
				return true;
			}
		}
		return false;
	}

	void RemoveFromSelectedItems(Object* o) {
		std::size_t i = 0;
		for (i = 0; i < Global::Variables.selectedObjects.size(); ++i) {
			if (o == Global::Variables.selectedObjects[i]) {
				break;
			}
		}
		if (i < Global::Variables.selectedObjects.size()) {
			Global::Variables.selectedObjects.erase(Global::Variables.selectedObjects.begin() + i);
		}
	}

	void Window::DrawSceneViewer()
	{
		static std::size_t indexOfLastSelection = 0;

		ImGui::SetNextWindowPos(ImVec2((20.0f / 1920.0f) * ((float)Global::Variables.currentWidth), (20.0f / 1080.0f) * ((float)Global::Variables.currentHeight)));
		ImGui::SetNextWindowSize(ImVec2((295.0f / 1920.0f) * ((float)Global::Variables.currentWidth), (1040.0f / 1080.0f) * ((float)Global::Variables.currentHeight)));
		ImGui::Begin("Scene Viewer", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.05f).x);
		if (ImGui::Button("Deselect All", ImVec2(ImGui::GetWindowSize().x * 0.90f, 0.0f))) {
			Global::Variables.selectedObjects.clear();
		}
		Scene& scene = Global::Variables.currentScene;
		std::size_t totalIndex = 0;
		for (std::size_t i = 0; i < scene.objectsOnScene.size(); ++i) {
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.125f).x);
			std::string buttonName = scene.objectsOnScene[i]->GetDisplayName() + "##" + std::to_string(scene.objectsOnScene[i]->GetUID());
			bool isPrimarySelected = IsPrimarySelected(scene.objectsOnScene[i]);
			bool isSelected = isPrimarySelected || IsSelected(scene.objectsOnScene[i]);
			if (isPrimarySelected) {
				//ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
				ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
			} else if (isSelected) {
				//ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
				ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
			}
			if (ImGui::Button(buttonName.c_str(), ImVec2(ImGui::GetWindowSize().x * 0.75f, 0.0f))) {
				if (Global::Variables.keyIn.leftShiftHeld || Global::Variables.keyIn.leftShiftPressed || Global::Variables.keyIn.rightShiftHeld || Global::Variables.keyIn.rightShiftPressed) {
					Global::Variables.selectedObjects.clear();
					AddItemsBetweenToSelectedObjects(indexOfLastSelection, i);
				} else if (Global::Variables.keyIn.leftControlHeld || Global::Variables.keyIn.leftControlPressed || Global::Variables.keyIn.rightControlHeld || Global::Variables.keyIn.rightControlPressed) {
					if (IsAlreadyInSelectedItems(scene.objectsOnScene[i])) {
						RemoveFromSelectedItems(scene.objectsOnScene[i]);
					}
					else {
						Global::Variables.selectedObjects.push_back(scene.objectsOnScene[i]);
					}
					indexOfLastSelection = totalIndex;
				}
				else {
					Global::Variables.selectedObjects.clear();
					Global::Variables.selectedObjects.push_back(scene.objectsOnScene[i]);
					indexOfLastSelection = totalIndex;
				}
			}
			if (isPrimarySelected || isSelected) {
				//ImGui::PopItemFlag();
				ImGui::PopStyleVar();
			}
			totalIndex++;
		}

		for (std::size_t i = 0; i < scene.lightsOnScene.size(); ++i) {
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.125f).x);
			std::string buttonName = scene.lightsOnScene[i]->GetDisplayName() + "##" + std::to_string(scene.lightsOnScene[i]->GetUID());
			bool isPrimarySelected = IsPrimarySelected(scene.lightsOnScene[i]);
			bool isSelected = isPrimarySelected || IsSelected(scene.lightsOnScene[i]);
			if (isPrimarySelected) {
				//ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
				ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
			}
			else if (isSelected) {
				//ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
				ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
			}
			if (ImGui::Button(buttonName.c_str(), ImVec2(ImGui::GetWindowSize().x * 0.75f, 0.0f))) {
				if (Global::Variables.keyIn.leftShiftHeld || Global::Variables.keyIn.leftShiftPressed || Global::Variables.keyIn.rightShiftHeld || Global::Variables.keyIn.rightShiftPressed) {
					Global::Variables.selectedObjects.clear();
					AddItemsBetweenToSelectedObjects(indexOfLastSelection, i);
				}
				else if (Global::Variables.keyIn.leftControlHeld || Global::Variables.keyIn.leftControlPressed || Global::Variables.keyIn.rightControlHeld || Global::Variables.keyIn.rightControlPressed) {
					if (IsAlreadyInSelectedItems(scene.lightsOnScene[i])) {
						RemoveFromSelectedItems(scene.lightsOnScene[i]);
					}
					else {
						Global::Variables.selectedObjects.push_back(scene.lightsOnScene[i]);
					}
					indexOfLastSelection = totalIndex;
				}
				else {
					if (!IsAlreadyInSelectedItems(scene.lightsOnScene[i])) {
						Global::Variables.selectedObjects.clear();
						Global::Variables.selectedObjects.push_back(scene.lightsOnScene[i]);
					}
					else {
						Global::Variables.selectedObjects.clear();
					}
					indexOfLastSelection = totalIndex;
				}
			}
			if (isPrimarySelected || isSelected) {
				//ImGui::PopItemFlag();
				ImGui::PopStyleVar();
			}
			totalIndex++;
		}

		ImGui::End();
	}
}
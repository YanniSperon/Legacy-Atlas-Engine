#include "Window.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "System.h"
#include "Global.h"
#include "Loader.h"
#include "ShapeGenerator.h"
#include <algorithm>

namespace Atlas {

	static int AddValueFile(std::string directory, std::string file, int value) {
		if (value == 0) {
			if (System::DoesFileExist(directory + file)) {
				AddValueFile(directory, file, value + 1);
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

	void Window::DrawInfoWindow(LevelEditor::EditorType& currentEditorType, LevelEditor::Mode& currentMode)
	{
		ImGui::Begin("Info", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::Text("Current Editor Type: ");
		ImGui::SameLine();
		if (currentEditorType == LevelEditor::EditorType::light) {
			ImGui::Text("Light");
		}
		else if (currentEditorType == LevelEditor::EditorType::scene) {
			ImGui::Text("Scene");
		}
		ImGui::Separator();
		ImGui::Text("Current Editing Mode: ");
		ImGui::SameLine();
		if (currentMode == LevelEditor::Mode::cam) {
			ImGui::Text("Camera");
		}
		else if (currentMode == LevelEditor::Mode::rotate) {
			ImGui::Text("Rotate");
		}
		else if (currentMode == LevelEditor::Mode::scale) {
			ImGui::Text("Scale");
		}
		else if (currentMode == LevelEditor::Mode::texture) {
			ImGui::Text("Texture");
		}
		else if (currentMode == LevelEditor::Mode::translate) {
			ImGui::Text("Translate");
		}
		ImGui::End();
	}
	
	void Window::DrawDebug(bool& EnableConsole, bool& Wireframe)
	{
		ImGui::Begin("Debug", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Separator();
		ImGui::Checkbox("Enable Console##consoleControl", &EnableConsole);
		if (ImGui::Button("Toggle display mode##wireframetoggler")) {
			if (Wireframe) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				Wireframe = false;
			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				Wireframe = true;
			}
		}
		ImGui::End();
	}

	void Window::DrawFileManager(GLFWwindow* window)
	{
		ImGui::Begin("File Manager", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		if (ImGui::Button("Load new mesh##loadmeshbutton1")) {
			std::string file = System::FileOpenDialog("Select a mesh to load", "OBJECT File\0*.obj\0", window);
			std::replace(file.begin(), file.end(), '\\', '/');
			if (file != "INVALID") {
				System::Log("");
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
						Global::Variables.meshCache[meshDir + meshName] = ShapeGenerator::loadShape(physicalLocation, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
					}
				}
				catch (const std::exception & e) {
					try {
						if (Global::Variables.meshCache.find(meshDir + meshName) == Global::Variables.meshCache.end()) {
							Global::Variables.meshCache[meshDir + meshName] = ShapeGenerator::loadTexturedShape(meshDir, meshName, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
						}
					}
					catch (const std::exception & e) {
						System::Err("Unrecognized file type, must be wavefront .obj file following the specified format");
					}
				}
				System::Warn("Mesh \"" + file + "\" loaded");
			}
		}
		if (ImGui::Button("Load new texture##loadtexturebutton1")) {
			std::string file = System::FileOpenDialog("Select a texture to load", "Portable Network Graphics\0*.png\0", window);
			std::replace(file.begin(), file.end(), '\\', '/');
			if (file != "INVALID") {
				System::Log("");
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
		if (ImGui::Button("Load new shader##loadshaderbutton1")) {
			std::string file = System::FileOpenDialog("Select a shader to load", "SHADER File\0*.shader\0", window);
			std::replace(file.begin(), file.end(), '\\', '/');
			if (file != "INVALID") {
				System::Log("");
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
		ImGui::End();
	}

	void Window::DrawPostProcessingManager(GLFWwindow* window)
	{
		ImGui::Begin("Post-Processing Manager", NULL/*, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove*/);
		if (ImGui::Button("Load new mesh##loadmeshbutton1")) {
			std::string file = System::FileOpenDialog("Select a mesh to load", "OBJECT File\0*.obj\0", window);
			std::replace(file.begin(), file.end(), '\\', '/');
			if (file != "INVALID") {
				System::Log("");
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
						Global::Variables.meshCache[meshDir + meshName] = ShapeGenerator::loadShape(physicalLocation, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
					}
				}
				catch (const std::exception & e) {
					try {
						if (Global::Variables.meshCache.find(meshDir + meshName) == Global::Variables.meshCache.end()) {
							Global::Variables.meshCache[meshDir + meshName] = ShapeGenerator::loadTexturedShape(meshDir, meshName, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
						}
					}
					catch (const std::exception & e) {
						System::Err("Unrecognized file type, must be wavefront .obj file following the specified format");
					}
				}
				System::Warn("Mesh \"" + file + "\" loaded");
			}
		}
		if (ImGui::Button("Load new texture##loadtexturebutton1")) {
			std::string file = System::FileOpenDialog("Select a texture to load", "Portable Network Graphics\0*.png\0", window);
			std::replace(file.begin(), file.end(), '\\', '/');
			if (file != "INVALID") {
				System::Log("");
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
		if (ImGui::Button("Load new shader##loadshaderbutton1")) {
			std::string file = System::FileOpenDialog("Select a shader to load", "SHADER File\0*.shader\0", window);
			std::replace(file.begin(), file.end(), '\\', '/');
			if (file != "INVALID") {
				System::Log("");
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
		ImGui::End();
	}

	void Window::DrawSpawnWindow(std::vector<Object*>& objectsOnScene, unsigned int& selectedObject)
	{
		static glm::vec3 InputRotation = glm::vec3(0.0f, 0.0f, 0.0f);
		static glm::vec3 InputTranslation = glm::vec3(0.0f, 0.0f, 0.0f);
		static glm::vec3 InputScale = glm::vec3(1.0f, 1.0f, 1.0f);
		static glm::vec3 InputAmbient = glm::vec3(0.5f, 0.5f, 0.5f);
		static glm::vec3 InputDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		static glm::vec3 InputSpecular = glm::vec3(0.5f, 0.5f, 0.5f);
		static int InputShininess = 32;
		static std::string currentSelectedMesh = "";
		static std::string currentSelectedTexture = "";
		static std::string currentSelectedShader = "";

		ImGui::Begin("Spawn Menu", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		if (ImGui::BeginCombo("Mesh##meshcombo", currentSelectedMesh.c_str()))
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
			ImGui::EndCombo();
		}
		ImGui::Separator();
		if (ImGui::BeginCombo("Texture##texturecombo", currentSelectedTexture.c_str()))
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
		ImGui::Separator();
		if (ImGui::BeginCombo("Shader##shadercombo", currentSelectedShader.c_str()))
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
		ImGui::Separator();
		ImGui::Text("Position");
		ImGui::InputFloat3("Rotation##rotfloatin", &InputRotation[0]);
		ImGui::InputFloat3("Translation##transfloatin", &InputTranslation[0]);
		ImGui::InputFloat3("Scale##scalefloatin", &InputScale[0]);
		ImGui::Separator();
		ImGui::Text("Lighting");
		ImGui::InputFloat3("Ambient##ambientfloatin", &InputAmbient[0]);
		ImGui::InputFloat3("Diffuse##diffusefloatin", &InputDiffuse[0]);
		ImGui::InputFloat3("Specular##specularfloatin", &InputSpecular[0]);
		ImGui::SliderInt("Shininess##shininessintslider", &InputShininess, 0, 512);
		ImGui::Separator();
		if (ImGui::Button("Spawn##spawn")) {
			if (Global::Variables.loadedMeshCache.find(currentSelectedMesh) != Global::Variables.loadedMeshCache.end() && Global::Variables.loadedTextureCache.find(currentSelectedTexture) != Global::Variables.loadedTextureCache.end() && Global::Variables.loadedShaderCache.find(currentSelectedShader) != Global::Variables.loadedShaderCache.end()) {
				Filepath meshpath = System::SeperateFilepath(Global::Variables.loadedMeshCache[currentSelectedMesh]);
				Filepath texpath = System::SeperateFilepath(Global::Variables.loadedTextureCache[currentSelectedTexture]);
				Filepath shaderpath = System::SeperateFilepath(Global::Variables.loadedShaderCache[currentSelectedShader]);

				System::Log("Spawned object with model \"" + meshpath.directory + meshpath.filename + "\" at (" + std::to_string(InputTranslation.x) + ", " + std::to_string(InputTranslation.y) + ", " + std::to_string(InputTranslation.z) + ")");
				objectsOnScene.push_back(new Object(glm::vec3(-5.0f, -5.0f, -5.0f), glm::vec3(5.0f, 5.0f, 5.0f), type::normalModel, meshpath.directory, meshpath.filename, texpath.directory, texpath.filename, shaderpath.directory, shaderpath.filename, true, true, InputRotation, InputTranslation, InputScale, Material(InputAmbient, InputDiffuse, InputSpecular, ((float)InputShininess))));
				selectedObject = objectsOnScene.size() - 1;
			}
			else {
				System::Err("Invalid or corrupted cache files!");
			}
		}
		ImGui::End();
	}
	
	void Window::DrawObjectSettingsWindow(Object* object)
	{
		static glm::vec3 InputModificationRotation = glm::vec3(0.0f, 0.0f, 0.0f);
		static glm::vec3 InputModificationTranslation = glm::vec3(0.0f, 0.0f, 0.0f);
		static glm::vec3 InputModificationScale = glm::vec3(1.0f, 1.0f, 1.0f);
		static glm::vec3 InputModificationAmbient = glm::vec3(0.5f, 0.5f, 0.5f);
		static glm::vec3 InputModificationDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		static glm::vec3 InputModificationSpecular = glm::vec3(0.5f, 0.5f, 0.5f);
		static int InputModificationShininess = 32;
		static char* items[] = { "Rendering", "Lighting", "Position" };
		static char* current_item = items[0];
		static std::string currentSelectedTexture = "";
		static std::string currentSelectedShader = "";

		ImGui::Begin("Object Settings", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

		if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < IM_ARRAYSIZE(items); n++)
			{
				bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your objects
				if (ImGui::Selectable(items[n], is_selected)) {
					current_item = items[n];
					if (is_selected) {
						ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
					}
				}
			}
			ImGui::EndCombo();
		}
		ImGui::Text("");

		if (current_item == "Rendering") {
			ImGui::Text("Texture");
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
			if (ImGui::Button("Apply##t1")) {
				Filepath texpath = System::SeperateFilepath(Global::Variables.loadedTextureCache[currentSelectedTexture]);
				object->SetTexture(std::string(texpath.directory), std::string(texpath.filename));
			}
			ImGui::Separator();
			ImGui::Text("Shader");
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
			if (ImGui::Button("Apply##s1")) {
				Filepath shaderpath = System::SeperateFilepath(Global::Variables.loadedShaderCache[currentSelectedShader]);
				object->SetShader(std::string(shaderpath.directory), std::string(shaderpath.filename));
			}
		}
		else if (current_item == "Position") {

			ImGui::Text("Rotation");
			ImGui::InputFloat3("##in1", &InputModificationRotation[0]);
			if (ImGui::Button("Apply##in1")) {
				object->RotateVec3(InputModificationRotation);
			}

			ImGui::Separator();

			ImGui::Text("Translation");
			ImGui::InputFloat3("##in2", &InputModificationTranslation[0]);
			if (ImGui::Button("Apply##in2")) {
				object->TranslateVec3(InputModificationTranslation);
			}

			ImGui::Separator();

			ImGui::Text("Scale");
			ImGui::InputFloat3("##in3", &InputModificationScale[0]);
			if (ImGui::Button("Apply##in3")) {
				object->ScaleVec3(InputModificationScale);
			}
		}
		else if (current_item == "Lighting") {

			ImGui::Text("Ambient Reflection");
			ImGui::InputFloat3("##lin2", &InputModificationAmbient[0]);
			if (ImGui::Button("Apply##lin2")) {
				auto temp = object->GetMaterial();
				temp.ambient = InputModificationAmbient;
				object->SetMaterial(temp);
			}

			ImGui::Separator();

			ImGui::Text("Diffuse Reflection");
			ImGui::InputFloat3("##lin3", &InputModificationDiffuse[0]);
			if (ImGui::Button("Apply##lin3")) {
				auto temp = object->GetMaterial();
				temp.diffuse = InputModificationDiffuse;
				object->SetMaterial(temp);
			}

			ImGui::Separator();

			ImGui::Text("Specular Reflection");
			ImGui::InputFloat3("##lin4", &InputModificationSpecular[0]);
			if (ImGui::Button("Apply##lin4")) {
				auto temp = object->GetMaterial();
				temp.ambient = InputModificationSpecular;
				object->SetMaterial(temp);
			}

			ImGui::Separator();

			ImGui::Text("Reflection Shininess");
			ImGui::SliderInt("##lin5", &InputModificationShininess, 0, 512);
			if (ImGui::Button("Apply##lin5")) {
				auto temp = object->GetMaterial();
				temp.shininess = InputModificationShininess;
				object->SetMaterial(temp);
			}
		}

		ImGui::End();
	}
}
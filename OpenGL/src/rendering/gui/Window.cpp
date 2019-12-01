#include "Window.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "System.h"
#include "Global.h"
#include "Loader.h"
#include "ShapeGenerator.h"

namespace Atlas {

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

	void Window::DrawObjectSettingsWindow(Object* object)
	{
		static char InputModificationStringTextureDirectory[128] = "res/images/textures/3d/";
		static char InputModificationStringTextureName[128] = "";
		static char InputModificationStringShaderDirectory[128] = "res/shaders/";
		static char InputModificationStringShaderName[128] = "Lighting.shader";
		static glm::vec3 InputModificationRotation = glm::vec3(0.0f, 0.0f, 0.0f);
		static glm::vec3 InputModificationTranslation = glm::vec3(0.0f, 0.0f, 0.0f);
		static glm::vec3 InputModificationScale = glm::vec3(1.0f, 1.0f, 1.0f);
		static glm::vec3 InputModificationAmbient = glm::vec3(0.5f, 0.5f, 0.5f);
		static glm::vec3 InputModificationDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		static glm::vec3 InputModificationSpecular = glm::vec3(0.5f, 0.5f, 0.5f);
		static int InputModificationShininess = 32;
		static char* items[] = { "Position", "Lighting", "Rendering" };
		static char* current_item = items[0];

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
			ImGui::Text("Texture Directory");
			ImGui::InputText("##tin1", InputModificationStringTextureDirectory, IM_ARRAYSIZE(InputModificationStringTextureDirectory));
			ImGui::Text("Texture Name");
			ImGui::InputText("##tin2", InputModificationStringTextureName, IM_ARRAYSIZE(InputModificationStringTextureName));
			if (ImGui::Button("Apply##t1")) {
				object->SetTexture(std::string(InputModificationStringTextureDirectory), std::string(InputModificationStringTextureName));
			}
			ImGui::Text("");
			ImGui::Separator();
			ImGui::Text("");
			ImGui::Text("Shader Directory");
			ImGui::InputText("##sin1", InputModificationStringShaderDirectory, IM_ARRAYSIZE(InputModificationStringShaderDirectory));
			ImGui::Text("Shader Name");
			ImGui::InputText("##sin2", InputModificationStringShaderName, IM_ARRAYSIZE(InputModificationStringShaderName));
			if (ImGui::Button("Apply##s1")) {
				object->SetShader(std::string(InputModificationStringShaderDirectory), std::string(InputModificationStringShaderName));
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

			if (ImGui::Button("Toggle Lighting##l1")) {
				object->SetHasLighting(!object->GetHasLighting());
			}

			ImGui::Separator();

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

	void Window::DrawSpawnWindow(std::vector<Object*>& objectsOnScene, unsigned int& selectedObject)
	{
		static bool InputModelHasTexture = false;
		static bool InputShaderHasLighting = true;
		static char InputStringMeshDirectory[128] = "res/models/";
		static char InputStringMeshName[128] = "";
		static char InputStringTextureDirectory[128] = "res/images/textures/3d/";
		static char InputStringTextureName[128] = "";
		static char InputStringShaderDirectory[128] = "res/shaders/";
		static char InputStringShaderName[128] = "Lighting.shader";
		static glm::vec3 InputRotation = glm::vec3(0.0f, 0.0f, 0.0f);
		static glm::vec3 InputTranslation = glm::vec3(0.0f, 0.0f, 0.0f);
		static glm::vec3 InputScale = glm::vec3(1.0f, 1.0f, 1.0f);
		static glm::vec3 InputAmbient = glm::vec3(0.5f, 0.5f, 0.5f);
		static glm::vec3 InputDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		static glm::vec3 InputSpecular = glm::vec3(0.5f, 0.5f, 0.5f);
		static int InputShininess = 32;

		ImGui::Begin("Spawn Menu", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::InputText("Model Directory##shaderInDir", InputStringMeshDirectory, IM_ARRAYSIZE(InputStringMeshDirectory));
		ImGui::InputText("Model Name##modelInName", InputStringMeshName, IM_ARRAYSIZE(InputStringMeshName));
		ImGui::Separator();
		ImGui::InputText("Texture Directory##textureInDir", InputStringTextureDirectory, IM_ARRAYSIZE(InputStringTextureDirectory));
		ImGui::InputText("Texture Name##textureInName", InputStringTextureName, IM_ARRAYSIZE(InputStringTextureName));
		ImGui::Separator();
		ImGui::Checkbox("Shader Supports Lighting##shaderSupportsLighting", &InputShaderHasLighting);
		ImGui::InputText("Shader Directory##shaderInDir", InputStringShaderDirectory, IM_ARRAYSIZE(InputStringShaderDirectory));
		ImGui::InputText("Shader Name##shaderInName", InputStringShaderName, IM_ARRAYSIZE(InputStringShaderName));
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
			System::Log("Spawned object with model \"" + std::string(InputStringMeshDirectory) + std::string(InputStringMeshName) + "\" at (" + std::to_string(InputTranslation.x) + ", " + std::to_string(InputTranslation.y) + ", " + std::to_string(InputTranslation.z) + ")");
			objectsOnScene.push_back(new Object(glm::vec3(-5.0f, -5.0f, -5.0f), glm::vec3(5.0f, 5.0f, 5.0f), type::normalModel, std::string(InputStringMeshDirectory), std::string(InputStringMeshName), std::string(InputStringTextureDirectory), std::string(InputStringTextureName), std::string(InputStringShaderDirectory), std::string(InputStringShaderName), true, InputShaderHasLighting, InputRotation, InputTranslation, InputScale, Material(InputAmbient, InputDiffuse, InputSpecular, ((float)InputShininess))));
			selectedObject = objectsOnScene.size() - 1;
		}
		ImGui::End();
	}

	void Window::DrawDebug(bool& EnableConsole)
	{
		ImGui::Begin("Debug", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Separator();
		ImGui::Checkbox("Enable Console##consoleControl", &EnableConsole);
		ImGui::End();
	}

	void Window::DrawFileManager(GLFWwindow* window)
	{
		ImGui::Begin("File Manager", NULL);
		if (ImGui::Button("Load new mesh##loadmeshbutton1")) {
			std::string file = System::FileOpenDialog("Select a mesh to load", "OBJECT File\0*.obj\0", window);
			if (file != "INVALID") {
				std::size_t lastSlashPos = file.find_last_of("\\");
				std::string meshDir = "";
				std::string meshName = "";
				if (lastSlashPos != std::string::npos) {
					meshDir = file.substr(0, lastSlashPos + 1);
					meshName = file.substr(lastSlashPos + 1);
				}
				else {
					meshName = file;
				}
				std::string val = std::to_string(AddValueMesh(meshName, 0));
				if (val == "0") {
					Global::Variables.loadedMeshCache[meshName] = (meshDir + meshName);
				}
				else {
					Global::Variables.loadedMeshCache[meshName + val] = (meshDir + meshName);
				}
				try {
					if (Global::Variables.meshCache.find(meshDir + meshName) == Global::Variables.meshCache.end()) {
						Global::Variables.meshCache[meshDir + meshName] = ShapeGenerator::loadShape(meshDir + meshName, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
					}
				}
				catch (const std::exception & e) {
					if (Global::Variables.meshCache.find(meshDir + meshName) == Global::Variables.meshCache.end()) {
						Global::Variables.meshCache[meshDir + meshName] = ShapeGenerator::loadTexturedShape(meshDir, meshName, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
					}
				}
			}
		}
		if (ImGui::Button("Load new texture##loadtexturebutton1")) {
			std::string file = System::FileOpenDialog("Select a texture to load", "Portable Network Graphics\0*.png\0", window);
			if (file != "INVALID") {
				std::size_t lastSlashPos = file.find_last_of("\\");
				std::string texDir = "";
				std::string texName = "";
				if (lastSlashPos != std::string::npos) {
					texDir = file.substr(0, lastSlashPos + 1);
					texName = file.substr(lastSlashPos + 1);
				}
				else {
					texName = file;
				}
				std::string val = std::to_string(AddValueTexture(texName, 0));
				if (val == "0") {
					Global::Variables.loadedTextureCache[texName] = (texDir + texName);
				}
				else {
					Global::Variables.loadedTextureCache[texName + val] = (texDir + texName);
				}

				if (Global::Variables.textureCache.find(texDir + texName) == Global::Variables.textureCache.end()) {
					Global::Variables.textureCache[texDir + texName] = Loader::LoadTexture(texDir, texName, GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
				}
			}
		}
		if (ImGui::Button("Load new shader##loadshaderbutton1")) {
			std::string file = System::FileOpenDialog("Select a shader to load", "SHADER File\0*.shader\0", window);
			if (file != "INVALID") {
				std::size_t lastSlashPos = file.find_last_of("\\");
				std::string shaderDir = "";
				std::string shaderName = "";
				if (lastSlashPos != std::string::npos) {
					shaderDir = file.substr(0, lastSlashPos + 1);
					shaderName = file.substr(lastSlashPos + 1);
				}
				else {
					shaderName = file;
				}
				std::string val = std::to_string(AddValueTexture(shaderName, 0));
				if (val == "0") {
					Global::Variables.loadedShaderCache[shaderName] = (shaderDir + shaderName);
				}
				else {
					Global::Variables.loadedShaderCache[shaderName + val] = (shaderDir + shaderName);
				}

				if (Global::Variables.shaderCache.find(shaderDir + shaderName) == Global::Variables.shaderCache.end()) {
					Global::Variables.shaderCache[shaderDir + shaderName] = new Shader(shaderDir + shaderName);
				}
			}
		}
		ImGui::End();
	}
}
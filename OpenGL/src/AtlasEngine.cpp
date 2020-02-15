#include "AtlasEngine.h"
#include "System.h"
#include "WindowManager.h"
#include "Global.h"
#include "Mesh.h"
#include "RenderingEngine.h"
#include "IO.h"
#include "LevelEditor.h"
#include "LevelEditorControl.h"
#include "PostProcessor.h"
#include "GUI.h"
#include "InputHandler.h"
#include "PhysicsSimulator.h"
#include <chrono>

namespace Atlas {
	bool AtlasEngine::Start()
	{
		Atlas::System::SetWorkingDirectory();

		if (!WindowManager::Initialize()) {
			return false;
		}

		// SOUNDENGINE::INITIALIZIZEAWDIW;
		//irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
		//engine->setSoundVolume(1);

		//PhysicsEngine::Initialize();
		{
			RenderingEngine::Initialize();

			//Global::Variables.currentScene.camerasOnScene.push_back(new Player(true, Global::Variables.originalMovementSpeed, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 5.0f, Global::Variables.mouseSensitivity, type::normalModel, "res/models/", "person.obj", "res/images/textures/", "person4k.png", "res/shaders/", "Lighting.shader", true, true, true, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(3.0f, 5.0f, 3.0f), glm::vec3(1.0f, 1.0f, 1.0f), 100.0f, Material()));
			Global::Variables.activeCamera->SetSkybox(new Object(type::normalModel, "res/models/", "skybox.obj", "res/images/textures/", "skybox.png", "res/shaders/", "Basic.shader", true, false, System::GenerateUniqueID(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(50.0f, 50.0f, 50.0f)));
			Global::Variables.currentScene.lightsOnScene.push_back(new Light(LightIntensity(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f)), type::cubeInvertedLighting, "", "", "res/images/colors/", "yellow.png", "res/shaders/", "Lighting.shader", true, true, System::GenerateUniqueID(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), Material(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 512.0f)));
			Global::Variables.currentScene.preloadedObjectsOnScene.push_back(new Object(type::normalModel, "res/models/", "plane.obj", "res/images/colors/", "white.png", "res/shaders/", "Lighting.shader", true, true, System::GenerateUniqueID(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -3.0f, 0.0f), glm::vec3(3.0f, 3.0f, 3.0f), Material(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f)));
			
			IO::LoadFile(Global::Variables.currentScene.objectsOnScene, "res/other/", "level.lvl");

			LevelEditor::EditorType currentEditorType(LevelEditor::scene);
			LevelEditor::Mode currentMode(LevelEditor::cam);

			bool GUIEnabled = true;
			bool EnableWireframe = false;
			glm::vec3 camPos(0.0f, 0.0f, 0.0f);
			bool EditorEnabled = true;
			double timeConstant = 1.0;
			auto lastTime = std::chrono::high_resolution_clock::now();
			auto currentTime = lastTime;
			unsigned int selectedObject;
			bool shouldLaunchSimulation = false;

			if (Global::Variables.currentScene.objectsOnScene.size() > 0) {
				selectedObject = Global::Variables.currentScene.objectsOnScene.size() - 1;
			}
			else {
				selectedObject = 0;
			}
			Global::Variables.mouseX = 36000000.0;
			Global::Variables.mouseY = 0.0;
			glfwSetCursorPos(Global::Variables.window, 36000000.0, 0.0);

			while (!glfwWindowShouldClose(Global::Variables.window))
			{
				///////////////////////////////////////////////////////////////////////////
				currentTime = std::chrono::high_resolution_clock::now();
				auto deltaTimeNanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime);
				lastTime = currentTime;
				double deltaTime = deltaTimeNanoseconds.count()/1000000000.0 * timeConstant;
				///////////////////////////////////////////////////////////////////////////
				glfwPollEvents();
				InputHandler::ProcessEvents(&Global::Variables.keyIn, &Global::Variables.mouseIn);
				///////////////////////////////////////////////////////////////////////////
				RenderingEngine::Begin();
				///////////////////////////////////////////////////////////////////////////
				//PhysicsEngine::Update(deltaTime);
				///////////////////////////////////////////////////////////////////////////
				if ((Global::Variables.keyIn.leftControlHeld && Global::Variables.keyIn.fHeld) || (Global::Variables.keyIn.leftControlPressed && Global::Variables.keyIn.fPressed)) {
					glfwSetWindowMonitor(Global::Variables.window, glfwGetPrimaryMonitor(), 0, 0, Global::Variables.currentWidth, Global::Variables.currentHeight, GLFW_DONT_CARE);
					//glfwSetWindowMonitor(window, NULL, 0, 0, Global::Variables.currentWidth, Global::Variables.currentHeight, GLFW_DONT_CARE);
				}
				else if ((Global::Variables.keyIn.leftControlHeld && Global::Variables.keyIn.qHeld) || (Global::Variables.keyIn.leftControlPressed && Global::Variables.keyIn.qPressed)) {
					glfwSetWindowShouldClose(Global::Variables.window, GLFW_TRUE);
				}
				else if ((Global::Variables.keyIn.leftControlHeld && Global::Variables.keyIn.sHeld) || (Global::Variables.keyIn.leftControlPressed && Global::Variables.keyIn.sPressed) || (Global::Variables.keyIn.leftControlHeld && Global::Variables.keyIn.sPressed) || (Global::Variables.keyIn.leftControlPressed && Global::Variables.keyIn.sHeld)) {
					Global::Variables.currentScene.Save("res/other/", "level.lvl");
				}
				if (Global::Variables.keyIn.leftControlHeld && Global::Variables.keyIn.rightControlHeld) {
					shouldLaunchSimulation = true;
				}
				///////////////////////////////////////////////////////////////////////////
				if (EditorEnabled) {
					LevelEditor::LevelEditorControl::Control(currentEditorType, currentMode, selectedObject, deltaTime);
				}
				///////////////////////////////////////////////////////////////////////////
				Global::Variables.activeCamera->ChangeMovementSpeed(Global::Variables.movementSpeed);
				Global::Variables.currentScene.Submit(Global::Variables.currentRenderer, Global::Variables.activeCamera);
				///////////////////////////////////////////////////////////////////////////
				Global::Variables.currentRenderer->SimpleFlush(Global::Variables.activeCamera, Global::Variables.currentWidth, Global::Variables.currentHeight, Global::Variables.FOV, Global::Variables.currentScene.lightsOnScene.at(0));
				///////////////////////////////////////////////////////////////////////////
				RenderingEngine::Render(EnableWireframe, GUIEnabled, currentEditorType, currentMode, selectedObject);
				///////////////////////////////////////////////////////////////////////////
				InputHandler::Flush(&Global::Variables.keyIn, &Global::Variables.mouseIn);
				///////////////////////////////////////////////////////////////////////////
				RenderingEngine::End();
				///////////////////////////////////////////////////////////////////////////
				if (shouldLaunchSimulation) {
					PhysicsSimulator::LaunchSimulation(&Global::Variables.currentScene, timeConstant);
					shouldLaunchSimulation = false;
				}
			}
			RenderingEngine::Cleanup();
		}
		Global::Variables.currentScene.Save("res/other/", "level.lvl");
		Global::Variables.config.WriteConfig("res/other/", "config.cfg");
		return true;
	}

	void AtlasEngine::Cleanup()
	{
		GUI::Terminate();
		glfwTerminate();
	}
}
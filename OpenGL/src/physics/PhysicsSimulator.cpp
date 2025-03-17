#include "PhysicsSimulator.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "PhysicsScene.h"
#include "Global.h"
#include "InputHandler.h"
#include "RenderingEngine.h"
#include "System.h"
#include "PostProcessor.h"
#include "GUI.h"
#include "Timer.h"

namespace Atlas {
	
	void PhysicsSimulator::LaunchSimulation(Scene* sceneToSimulate)
	{
		double timeConstant = Global::Variables.physicsSettings.timeConstant;
		System::Warn("Physics Simulator entered");
		Camera* originalCamera = Global::Variables.activeCamera;
		PhysicsEngine::Initialize(sceneToSimulate->sceneSettings);
		bool shouldExit = false;
		PhysicsRenderer renderer = PhysicsRenderer();
		PhysicsScene physicsScene = PhysicsScene(sceneToSimulate);
		PhysicsEngine::SetPhysicsScene(&physicsScene);
		bool shouldReenableMovementControls = false;
		if (originalCamera->GetHasLookControls()) {
			shouldReenableMovementControls = true;
			originalCamera->SetHasLookControls(false);
		}
		auto lastTime = std::chrono::high_resolution_clock::now();
		auto currentTime = lastTime;
		Timer shootTimer(0.1f);
		while (!shouldExit && !glfwWindowShouldClose(Global::Variables.window)) {

			glfwPollEvents();
			InputHandler::ProcessEvents(&Global::Variables.keyIn, &Global::Variables.mouseIn);

			currentTime = std::chrono::high_resolution_clock::now();
			auto deltaTimeNanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime);
			lastTime = currentTime;
			double deltaTime = deltaTimeNanoseconds.count() / 1000000000.0 * timeConstant;

			if (Global::Variables.keyIn.escapePressed) {
				shouldExit = true;
				System::Warn("Physics Simulator exited");
			}
			if (Atlas::Global::Variables.keyIn.wHeld) {
				physicsScene.playersOnScene.at(0)->MoveForward(deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.sHeld) {
				physicsScene.playersOnScene.at(0)->MoveBackward(deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.aHeld) {
				physicsScene.playersOnScene.at(0)->StrafeLeft(deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.dHeld) {
				physicsScene.playersOnScene.at(0)->StrafeRight(deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.spaceHeld) {
				physicsScene.playersOnScene.at(0)->MoveUp(deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.leftControlHeld) {
				physicsScene.playersOnScene.at(0)->MoveDown(deltaTime);
			}
			if (Global::Variables.mouseIn.leftClicked) {
				physicsScene.physicsObjectsOnScene.push_back(new PhysicsObject(new Object(type::normalModel, "res/models/", "sphere.obj", "res/images/textures/", "newcow.png", "res/shaders/", "Lighting.shader", true, true, Atlas::UUID(), glm::vec3(0.0f, 0.0f, 0.0f), physicsScene.playersOnScene.at(0)->GetTranslation(), glm::vec3(0.25f, 0.25f, 0.5f)), 50.0f, PhysicsObject::typeShape::sphere));
				physicsScene.physicsObjectsOnScene.at(physicsScene.physicsObjectsOnScene.size() - 1)->SetDisplayName("Bullet");
				physicsScene.physicsObjectsOnScene.at(physicsScene.physicsObjectsOnScene.size() - 1)->Launch(physicsScene.playersOnScene.at(0)->GetViewDirection());
				shootTimer.Reset(0.1f);
				shootTimer.Start();
			}
			if (Global::Variables.mouseIn.leftHeld) {
				shootTimer.ElapseTime(deltaTime);
				if (shootTimer.HasFinished()) {
					physicsScene.physicsObjectsOnScene.push_back(new PhysicsObject(new Object(type::normalModel, "res/models/", "sphere.obj", "res/images/textures/", "newcow.png", "res/shaders/", "Lighting.shader", true, true, Atlas::UUID(), glm::vec3(0.0f, 0.0f, 0.0f), physicsScene.playersOnScene.at(0)->GetTranslation(), glm::vec3(0.25f, 0.25f, 0.5f)), 50.0f, PhysicsObject::typeShape::sphere));
					physicsScene.physicsObjectsOnScene.at(physicsScene.physicsObjectsOnScene.size() - 1)->SetDisplayName("Bullet");
					physicsScene.physicsObjectsOnScene.at(physicsScene.physicsObjectsOnScene.size() - 1)->Launch(physicsScene.playersOnScene.at(0)->GetViewDirection());
					shootTimer.Reset(0.1f);
					shootTimer.Start();
				}
			}
			physicsScene.playersOnScene.at(0)->BringWith(physicsScene.playersOnScene.at(0)->GetPlayerModel());
			PhysicsEngine::Update(deltaTime);

			RenderingEngine::BeginPhysicsSimulator();

			physicsScene.playersOnScene.at(0)->LookAt(Global::Variables.mouseX, Global::Variables.mouseY);
			physicsScene.Submit(&renderer, physicsScene.playersOnScene.at(0));
			physicsScene.playersOnScene.at(0)->ChangeMovementSpeed(Global::Variables.movementSpeed);
			renderer.SimpleFlush(physicsScene.playersOnScene.at(0), Global::Variables.currentWidth, Global::Variables.currentHeight, Global::Variables.FOV, physicsScene.physicsLightsOnScene.at(0));
			
			PhysicsEngine::DrawDebug();

			PostProcessor::RenderPhysicsRenderer(&renderer, &physicsScene);
			GUI::LoadPhysicsSimulatorGUI();
			GUI::Draw();

			RenderingEngine::End();

			InputHandler::Flush(&Global::Variables.keyIn, &Global::Variables.mouseIn);

			System::ProcessGlobalEvents();
		}
		if (shouldReenableMovementControls) {
			originalCamera->SetHasLookControls(true);
		}
		originalCamera->BringWith(originalCamera->GetSkybox());
		Camera::SetFocus(originalCamera);
		PhysicsEngine::Cleanup();
		
		glfwSetInputMode(Global::Variables.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		glfwSetCursorPos(Global::Variables.window, Global::Variables.currentWidth * 0.5, Global::Variables.currentHeight * 0.5);
		Global::Variables.enableMouseMove = false;
	}
}

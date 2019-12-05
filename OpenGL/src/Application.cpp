//#define DGPU

#ifdef DGPU
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <irrKlang.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>

#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Config.h"
#include "Object.h"
#include "PhysicsBody.h"
#include "Loader.h"
#include "Timer.h"
#include "SimpleRenderer.h"
#include "LevelEditor.h"
#include "IO.h"
#include "Object2D.h"
#include "Font.h"
#include "Search.h"
#include "Light.h"
#include "System.h"
#include "InputHandler.h"
#include "Input.h"
#include "Global.h"
#include "Callbacks.h"
#include "GUI.h"
#include "Scene.h"
#include "SceneEditorControl.h"
#include "VRHandler.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/quaternion.hpp"
#include "primitives/Vertex.h"
#include "primitives/ShapeGenerator.h"



using namespace Atlas;



int main(void)
{
	System::SetWorkingDirectory();
	GLFWwindow* window;

	if (!glfwInit()) {
		return -1;
	}


	if (Global::Variables.fullscreen) {
		window = glfwCreateWindow(Global::Variables.initialWidth, Global::Variables.initialHeight, "Atlas", glfwGetPrimaryMonitor(), NULL);
	}
	else {
		if (Global::Variables.forceFullscreen) {
			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			if (mode->width == Global::Variables.currentWidth && mode->height == Global::Variables.currentHeight) {
				window = glfwCreateWindow(Global::Variables.initialWidth, Global::Variables.initialHeight, "Atlas", glfwGetPrimaryMonitor(), NULL);
			}
			else {
				//glfwWindowHint(GLFW_DECORATED, false);
				window = glfwCreateWindow(Global::Variables.initialWidth, Global::Variables.initialHeight, "Atlas", NULL, NULL);
			}
		}
		else {
			//glfwWindowHint(GLFW_DECORATED, false);
			window = glfwCreateWindow(Global::Variables.initialWidth, Global::Variables.initialHeight, "Atlas", NULL, NULL);
		}
	}

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	//glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);

	glfwSwapInterval(Global::Variables.VSyncPreference);

	if (glewInit() != GLEW_OK) {
		System::Err("Error initializing GLEW (OpenGL)");
	}

	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();

	System::Log("Vendor: " + std::string((char*)glGetString(GL_VENDOR)));
	System::Log("Model: " + std::string((char*)glGetString(GL_RENDERER)));
	System::Log("Version: " + std::string((char*)glGetString(GL_VERSION)));

	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if (Global::Variables.mouseMode == MouseMode::raw) {
			if (glfwRawMouseMotionSupported())
				glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		}
		glfwSetCursorPosCallback(window, Callbacks::cursorPositionCallback);
		glfwSetFramebufferSizeCallback(window, Callbacks::framebufferSizeCallback);
		glfwSetErrorCallback(Callbacks::errorCallback);

		System::Log("Register OpenGL debug callback ");
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(Callbacks::openglCallbackFunction, nullptr);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//const char* attackSFXFilename = "res/audio/sfx/attack.wav";
		//const char* explosionSFXFilename = "res/audio/sfx/explosion.wav";
		//const char* jumpSFXFilename = "res/audio/sfx/jump.wav";
		//const char* pickupSFXFilename = "res/audio/sfx/pickup.wav";
		//const char* selectSFXFilename = "res/audio/sfx/select.wav";
		//const char* shootSFXFilename = "res/audio/sfx/shoot.wav";
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//engine->setSoundVolume(0);
		//irrklang::ISound* attackSFX = engine->play2D(attackSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		//irrklang::ISound* explosionSFX = engine->play2D(explosionSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		//irrklang::ISound* jumpSFX = engine->play2D(jumpSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		//irrklang::ISound* pickupSFX = engine->play2D(pickupSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		//irrklang::ISound* selectSFX = engine->play2D(selectSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		//irrklang::ISound* shootSFX = engine->play2D(shootSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		//engine->play2D(steamSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		glBlendEquation(GL_FUNC_ADD);
		glEnable(GL_DEPTH_TEST);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glFrontFace(GL_CW);

		bool GUIEnabled = true;

		SimpleRenderer renderer;

		LevelEditor::Mode currentMode(LevelEditor::cam);

		Font arial24pt = Font("res/fonts/arial/", "arial.ttf", 24);
		Font timesnewroman32pt = Font("res/fonts/times new roman/", "times.ttf", 32);

		Global::Variables.currentScene.lightsOnScene.push_back(new Light(LightIntensity(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec3(0.1f, 0.1f, 0.1f), type::cubeInvertedLighting, "", "", "res/images/colors/", "yellow.png", "res/shaders/", "Lighting.shader", true, true, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), Material(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f)));

		Global::Variables.currentScene.preloadedObjectsOnScene.push_back(new Object(glm::vec3(-50.0f, -50.0f, -50.0f), glm::vec3(50.0f, 50.0f, 50.0f), type::skyBox, "", "", "res/images/textures/", "skybox.png", "res/shaders/", "Basic.shader", true, false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
		Global::Variables.currentScene.preloadedObjectsOnScene.push_back(new Object(glm::vec3(-5.0f, -5.0f, -5.0f), glm::vec3(5.0f, 5.0f, 5.0f), type::normalModel, "res/models/", "plane.obj", "res/images/colors/", "white.png", "res/shaders/", "Lighting.shader", true, true, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -3.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), Material(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f)));

		bool loadFile = true;
		if (loadFile) {
			IO::LoadFile(Global::Variables.currentScene.objectsOnScene, "res/other/", "level.lvl");
		}

		//GLuint leftEyeFrameBuffer;
		//glGenFramebuffers(1, &leftEyeFrameBuffer);
		//GLuint rightEyeFrameBuffer;
		//glGenFramebuffers(1, &rightEyeFrameBuffer);
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//GLuint leftEyeFrameBuffer;
		//glGenFramebuffers(1, &leftEyeFrameBuffer);
		//GLuint rightEyeFrameBuffer;
		//glGenFramebuffers(1, &rightEyeFrameBuffer);
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);

		LevelEditor::EditorType currentEditorType(LevelEditor::scene);

		
		GUI::Initialize(window);


		glm::vec3 camPos(0.0f, 0.0f, 0.0f);
		glfwSetCursorPos(window, 0.0, 0.0);

		bool EditorEnabled = true;

		float timeConstant = 1.0f;
		double lastTime = glfwGetTime();
		double deltaT = 0, nowTime = 0;
		engine->setSoundVolume(1);

		unsigned int selectedObject;
		if (Global::Variables.currentScene.objectsOnScene.size() > 0) {
			selectedObject = Global::Variables.currentScene.objectsOnScene.size() - 1;
		}
		else {
			selectedObject = 0;
		}

		if (Global::Variables.hasVR) {
			VRHandler::Setup();
		}
		
		while (!glfwWindowShouldClose(window))
		{
			///////////////////////////////////////////////////////////////////////////
			glfwPollEvents();
			///////////////////////////////////////////////////////////////////////////
			nowTime = glfwGetTime();
			deltaT = (nowTime - lastTime);
			lastTime = nowTime;
			///////////////////////////////////////////////////////////////////////////
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			///////////////////////////////////////////////////////////////////////////
			InputHandler::ProcessEvents(&Global::Variables.keyIn, &Global::Variables.mouseIn);
			///////////////////////////////////////////////////////////////////////////
			if (Global::Variables.keyIn.sixPressed) {
				System::Warn("--------------------------------");
				for (auto it : Global::Variables.meshCache) {
					System::Log("First: " + it.first);
				}
			}
			///////////////////////////////////////////////////////////////////////////
			float deltaTime = (float)deltaT * timeConstant;
			///////////////////////////////////////////////////////////////////////////
			if ((Global::Variables.keyIn.leftControlHeld && Global::Variables.keyIn.fHeld) || (Global::Variables.keyIn.leftControlPressed && Global::Variables.keyIn.fPressed)) {
				glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, Global::Variables.currentWidth, Global::Variables.currentHeight, GLFW_DONT_CARE);
				//glfwSetWindowMonitor(window, NULL, 0, 0, Global::Variables.currentWidth, Global::Variables.currentHeight, GLFW_DONT_CARE);
			}
			else if ((Global::Variables.keyIn.leftControlHeld && Global::Variables.keyIn.qHeld) || (Global::Variables.keyIn.leftControlPressed && Global::Variables.keyIn.qPressed)) {
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
			else if ((Global::Variables.keyIn.leftControlHeld && Global::Variables.keyIn.sHeld) || (Global::Variables.keyIn.leftControlPressed && Global::Variables.keyIn.sPressed) || (Global::Variables.keyIn.leftControlHeld && Global::Variables.keyIn.sPressed) || (Global::Variables.keyIn.leftControlPressed && Global::Variables.keyIn.sHeld)) {
				Global::Variables.currentScene.Save("res/other/", "level.lvl");
			}
			///////////////////////////////////////////////////////////////////////////
			if (EditorEnabled) {
				LevelEditor::SceneEditorControl::Control(currentEditorType, currentMode, selectedObject, deltaTime);
			}
			///////////////////////////////////////////////////////////////////////////
			Global::Variables.camera.ChangeMovementSpeed(Global::Variables.movementSpeed);
			camPos = Global::Variables.camera.GetTranslation();
			Global::Variables.camera.BringWith(Global::Variables.currentScene.preloadedObjectsOnScene[0]);
			glm::mat4 viewMatrix = Global::Variables.camera.GetViewTransformMatrix();
			Global::Variables.currentScene.Submit(&renderer, camPos, viewMatrix);
			///////////////////////////////////////////////////////////////////////////
			if (GUIEnabled) {
				GUI::LoadLevelEditorGUI(window, currentEditorType, currentMode, selectedObject);
			}
			///////////////////////////////////////////////////////////////////////////
			//if (hasVR) {
			//	vr::TrackedDevicePose_t trackedDevicePose;
			//	vr_pointer->GetDeviceToAbsoluteTrackingPose(
			//		vr::TrackingUniverseStanding, 0, &trackedDevicePose, 1);
			//	vr::VRCompositor()->WaitGetPoses(&trackedDevicePose, vr::k_unMaxTrackedDeviceCount, NULL, 0);
			//
			//	glBlitNamedFramebuffer(0, leftEyeFrameBuffer, 0, 0, currentWidth, currentHeight, 0, 0, currentWidth, currentHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
			//	const vr::Texture_t tex = { reinterpret_cast<void*>(intptr_t(leftEyeFrameBuffer)), vr::TextureType_OpenGL, vr::ColorSpace_Gamma };
			//	vr::EVRCompositorError value = vr::VRCompositor()->Submit(vr::Eye_Left, &tex);
			//	if (value != vr::VRCompositorError_None)
			//	{
			//		printf("VRCompositorError: %i \n", value);
			//		//vr::VRCompositorError_DoNotHaveFocus;
			//		//vr::VRCompositorError
			//	}
			//}
			//VRHandler::Submit();
			///////////////////////////////////////////////////////////////////////////
			renderer.SimpleFlush(&Global::Variables.camera, Global::Variables.currentWidth, Global::Variables.currentHeight, Global::Variables.FOV, Global::Variables.currentScene.lightsOnScene.at(0));
			///////////////////////////////////////////////////////////////////////////
			GUI::Draw();
			glfwSwapBuffers(window);
			///////////////////////////////////////////////////////////////////////////
			InputHandler::Flush(&Global::Variables.keyIn, &Global::Variables.mouseIn);
			///////////////////////////////////////////////////////////////////////////
		}
		Global::Variables.currentScene.Save("res/other/", "level.lvl");
		Global::Variables.config.WriteConfig("res/other/", "config.cfg");
		Mesh::FlushCache();
		Object::FlushCache();
		VRHandler::Cleanup();
	}
	GUI::Terminate();
	glfwTerminate();
	return 0;
}
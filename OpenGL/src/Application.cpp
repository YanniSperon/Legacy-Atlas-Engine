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
#include <openvr.h>

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
#include "BoundingSphere.h"
#include "AxisAlignedBoundingBox.h"
#include "Plane.h"
#include "AABBCollidable.h"
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
#include "Window.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/quaternion.hpp"
#include "primitives/Vertex.h"
#include "primitives/ShapeGenerator.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"



using namespace Atlas;



int main(void)
{
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
				glfwWindowHint(GLFW_DECORATED, false);
				window = glfwCreateWindow(Global::Variables.initialWidth, Global::Variables.initialHeight, "Atlas", NULL, NULL);
			}
		}
		else {
			glfwWindowHint(GLFW_DECORATED, false);
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

	vr::IVRSystem* vr_pointer = NULL;

	if (Global::Variables.hasVR) {
		vr::EVRInitError eError = vr::VRInitError_None;
		vr_pointer = VR_Init(&eError, vr::VRApplication_Scene); // VRApplication_Background OR VRApplication_Scene OR VRApplication_Overlay OR VRApplication_Utility
		if (eError != vr::VRInitError_None)
		{
			vr_pointer = NULL;
			std::string error = VR_GetVRInitErrorAsEnglishDescription(eError);
			System::Err("Unable to init VR runtime: \"" + error + "\"");
		}
	}

	for (int i = 0; i < 10; i++) {
		Global::Variables.consoleLog.push_back("");
	}
	
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

		std::vector<Object*> objectsOnScene;
		std::vector<Object*> preloadedObjectsOnScene;

		LevelEditor::Mode currentMode(LevelEditor::cam);

		Font arial24pt = Font("res/fonts/arial/", "arial.ttf", 24);
		Font timesnewroman32pt = Font("res/fonts/times new roman/", "times.ttf", 32);

		preloadedObjectsOnScene.push_back(new Object(glm::vec3(-50.0f, -50.0f, -50.0f), glm::vec3(50.0f, 50.0f, 50.0f), type::skyBox, "", "", "res/images/textures/2d/", "skybox.png", "res/shaders/", "Basic.shader", true, false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
		preloadedObjectsOnScene.push_back(new Object(glm::vec3(-5.0f, -5.0f, -5.0f), glm::vec3(5.0f, 5.0f, 5.0f), type::normalModel, "res/models/", "plane.obj", "res/images/colors/", "white.png", "res/shaders/", "Lighting.shader", true, true, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -3.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), Material(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f)));

		bool loadFile = true;
		if (loadFile) {
			IO::LoadFile(objectsOnScene, "res/other/", "level.lvl");
		}

		Light* light = new Light(LightIntensity(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec3(0.1f, 0.1f, 0.1f), type::cubeInvertedLighting, "", "", "res/images/colors/", "yellow.png", "res/shaders/", "Lighting.shader", true, true, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), Material(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f));

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

		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();

		glm::vec3 camPos(0.0f, 0.0f, 0.0f);
		glfwSetCursorPos(window, 0.0, 0.0);

		bool EditorEnabled = true;

		float timeConstant = 1.0f;
		double lastTime = glfwGetTime();
		double deltaT = 0, nowTime = 0;
		engine->setSoundVolume(1);

		unsigned int selectedObject;
		if (objectsOnScene.size() > 0) {
			selectedObject = objectsOnScene.size() - 1;
		}
		else {
			selectedObject = 0;
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
			ImGui_ImplGlfwGL3_NewFrame();
			///////////////////////////////////////////////////////////////////////////
			InputHandler::ProcessEvents(&Global::Variables.keyIn, &Global::Variables.mouseIn);
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
				IO::SaveToFile(objectsOnScene, "res/other/", "level.lvl");
			}
			///////////////////////////////////////////////////////////////////////////
			if (EditorEnabled) {
				if (Global::Variables.keyIn.onePressed) {
					currentEditorType = LevelEditor::EditorType::scene;
				}

				if (Global::Variables.keyIn.twoPressed) {
					currentEditorType = LevelEditor::EditorType::light;
				}

				if ((objectsOnScene.size() > 0 && currentEditorType == LevelEditor::EditorType::scene) || (currentEditorType == LevelEditor::EditorType::light)) {
					if (Global::Variables.keyIn.cPressed) {
						currentMode = LevelEditor::Mode::cam;
					}
					else if (Global::Variables.keyIn.ePressed) {
						currentMode = LevelEditor::Mode::scale;
					}
					else if (Global::Variables.keyIn.rPressed) {
						currentMode = LevelEditor::Mode::rotate;
					}
					else if (Global::Variables.keyIn.vPressed) {
						currentMode = LevelEditor::Mode::translate;
					}
					else if (Global::Variables.keyIn.tPressed) {
						currentMode = LevelEditor::Mode::texture;
					}
				}
				else {
					currentMode = LevelEditor::Mode::cam;
				}
				///////////////////////////////////////////////////////////////////////////
				if (currentEditorType == LevelEditor::EditorType::scene) {
					if (currentMode == LevelEditor::Mode::scale) {
						if (Global::Variables.keyIn.wHeld) {
							objectsOnScene[selectedObject]->ScaleAdd3f(0.0f, 0.0f, -Global::Variables.movementSpeed * deltaTime);
						}
						if (Global::Variables.keyIn.sHeld) {
							objectsOnScene[selectedObject]->ScaleAdd3f(0.0f, 0.0f, Global::Variables.movementSpeed * deltaTime);
						}
						if (Global::Variables.keyIn.aHeld) {
							objectsOnScene[selectedObject]->ScaleAdd3f(-Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (Global::Variables.keyIn.dHeld) {
							objectsOnScene[selectedObject]->ScaleAdd3f(Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (Global::Variables.keyIn.spaceHeld) {
							objectsOnScene[selectedObject]->ScaleAdd3f(0.0f, Global::Variables.movementSpeed * deltaTime, 0.0f);
						}
						if (Global::Variables.keyIn.leftControlHeld) {
							objectsOnScene[selectedObject]->ScaleAdd3f(0.0f, -Global::Variables.movementSpeed * deltaTime, 0.0f);
						}
					}
					else if (currentMode == LevelEditor::Mode::translate) {
						if (Global::Variables.keyIn.wHeld) {
							objectsOnScene[selectedObject]->TranslateAdd3f(0.0f, 0.0f, -Global::Variables.movementSpeed * deltaTime);
						}
						if (Global::Variables.keyIn.sHeld) {
							objectsOnScene[selectedObject]->TranslateAdd3f(0.0f, 0.0f, Global::Variables.movementSpeed * deltaTime);
						}
						if (Global::Variables.keyIn.aHeld) {
							objectsOnScene[selectedObject]->TranslateAdd3f(-Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (Global::Variables.keyIn.dHeld) {
							objectsOnScene[selectedObject]->TranslateAdd3f(Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (Global::Variables.keyIn.spaceHeld) {
							objectsOnScene[selectedObject]->TranslateAdd3f(0.0f, Global::Variables.movementSpeed * deltaTime, 0.0f);
						}
						if (Global::Variables.keyIn.leftControlHeld) {
							objectsOnScene[selectedObject]->TranslateAdd3f(0.0f, -Global::Variables.movementSpeed * deltaTime, 0.0f);
						}
					}
					else if (currentMode == LevelEditor::Mode::cam) {
						if (Global::Variables.keyIn.wHeld) {
							Global::Variables.camera.MoveForward(deltaTime);
						}
						if (Global::Variables.keyIn.sHeld) {
							Global::Variables.camera.MoveBackward(deltaTime);
						}
						if (Global::Variables.keyIn.aHeld) {
							Global::Variables.camera.StrafeLeft(deltaTime);
						}
						if (Global::Variables.keyIn.dHeld) {
							Global::Variables.camera.StrafeRight(deltaTime);
						}
						if (Global::Variables.keyIn.spaceHeld) {
							Global::Variables.camera.MoveUp(deltaTime);
						}
						if (Global::Variables.keyIn.leftControlHeld) {
							Global::Variables.camera.MoveDown(deltaTime);
						}
					}
					else if (currentMode == LevelEditor::Mode::rotate) {
						if (Global::Variables.keyIn.wHeld) {
							objectsOnScene[selectedObject]->RotateAdd3f(0.0f, 0.0f, glm::degrees(-Global::Variables.movementSpeed * deltaTime));
						}
						if (Global::Variables.keyIn.sHeld) {
							objectsOnScene[selectedObject]->RotateAdd3f(0.0f, 0.0f, glm::degrees(Global::Variables.movementSpeed * deltaTime));
						}
						if (Global::Variables.keyIn.aHeld) {
							objectsOnScene[selectedObject]->RotateAdd3f(glm::degrees(-Global::Variables.movementSpeed * deltaTime), 0.0f, 0.0f);
						}
						if (Global::Variables.keyIn.dHeld) {
							objectsOnScene[selectedObject]->RotateAdd3f(glm::degrees(Global::Variables.movementSpeed * deltaTime), 0.0f, 0.0f);
						}
						if (Global::Variables.keyIn.spaceHeld) {
							objectsOnScene[selectedObject]->RotateAdd3f(0.0f, glm::degrees(Global::Variables.movementSpeed * deltaTime), 0.0f);
						}
						if (Global::Variables.keyIn.leftControlHeld) {
							objectsOnScene[selectedObject]->RotateAdd3f(0.0f, glm::degrees(-Global::Variables.movementSpeed * deltaTime), 0.0f);
						}
					}

					if (Global::Variables.keyIn.leftBracketPressed) {
						if (selectedObject > 0) {
							selectedObject--;
						}
					}
					if (Global::Variables.keyIn.rightBracketPressed) {
						if (selectedObject < objectsOnScene.size() - 1) {
							selectedObject++;
						}
					}
					if (Global::Variables.keyIn.nPressed) {
						System::Log("Cube created!");
						objectsOnScene.push_back(new AABBCollidable(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), type::cubeModel, "", "", "res/images/textures/2d/", "newcow.png", "res/shaders/", "Lighting.shader", true, true, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), Material(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f)));
						selectedObject = objectsOnScene.size() - 1;
					}
					if (Global::Variables.keyIn.backspacePressed) {
						if (objectsOnScene.size() > 0) {
							System::Log("Object deleted!");
							delete objectsOnScene[selectedObject];
							objectsOnScene.erase(objectsOnScene.begin() + selectedObject);

							if (selectedObject > 0) {
								selectedObject--;
							}
							else {
								selectedObject = 0;
							}
						}
					}
				}
				else if (currentEditorType == LevelEditor::EditorType::light) {
					if (currentMode == LevelEditor::Mode::scale) {
						if (Global::Variables.keyIn.wHeld) {
							light->ScaleAdd3f(0.0f, 0.0f, -Global::Variables.movementSpeed * deltaTime);
						}
						if (Global::Variables.keyIn.sHeld) {
							light->ScaleAdd3f(0.0f, 0.0f, Global::Variables.movementSpeed * deltaTime);
						}
						if (Global::Variables.keyIn.aHeld) {
							light->ScaleAdd3f(-Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (Global::Variables.keyIn.dHeld) {
							light->ScaleAdd3f(Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (Global::Variables.keyIn.spaceHeld) {
							light->ScaleAdd3f(0.0f, Global::Variables.movementSpeed * deltaTime, 0.0f);
						}
						if (Global::Variables.keyIn.leftControlHeld) {
							light->ScaleAdd3f(0.0f, -Global::Variables.movementSpeed * deltaTime, 0.0f);
						}
					}
					else if (currentMode == LevelEditor::Mode::translate) {
						if (Global::Variables.keyIn.wHeld) {
							light->TranslateAdd3f(0.0f, 0.0f, -Global::Variables.movementSpeed * deltaTime);
						}
						if (Global::Variables.keyIn.sHeld) {
							light->TranslateAdd3f(0.0f, 0.0f, Global::Variables.movementSpeed * deltaTime);
						}
						if (Global::Variables.keyIn.aHeld) {
							light->TranslateAdd3f(-Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (Global::Variables.keyIn.dHeld) {
							light->TranslateAdd3f(Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (Global::Variables.keyIn.spaceHeld) {
							light->TranslateAdd3f(0.0f, Global::Variables.movementSpeed * deltaTime, 0.0f);
						}
						if (Global::Variables.keyIn.leftControlHeld) {
							light->TranslateAdd3f(0.0f, -Global::Variables.movementSpeed * deltaTime, 0.0f);
						}
					}
					else if (currentMode == LevelEditor::Mode::cam) {
						if (Global::Variables.keyIn.wHeld) {
							Global::Variables.camera.MoveForward(deltaTime);
						}
						if (Global::Variables.keyIn.sHeld) {
							Global::Variables.camera.MoveBackward(deltaTime);
						}
						if (Global::Variables.keyIn.aHeld) {
							Global::Variables.camera.StrafeLeft(deltaTime);
						}
						if (Global::Variables.keyIn.dHeld) {
							Global::Variables.camera.StrafeRight(deltaTime);
						}
						if (Global::Variables.keyIn.spaceHeld) {
							Global::Variables.camera.MoveUp(deltaTime);
						}
						if (Global::Variables.keyIn.leftControlHeld) {
							Global::Variables.camera.MoveDown(deltaTime);
						}
					}
					else if (currentMode == LevelEditor::Mode::rotate) {
						if (Global::Variables.keyIn.wHeld) {
							light->RotateAdd3f(0.0f, 0.0f, glm::degrees(-Global::Variables.movementSpeed * deltaTime));
						}
						if (Global::Variables.keyIn.sHeld) {
							light->RotateAdd3f(0.0f, 0.0f, glm::degrees(Global::Variables.movementSpeed * deltaTime));
						}
						if (Global::Variables.keyIn.aHeld) {
							light->RotateAdd3f(glm::degrees(-Global::Variables.movementSpeed * deltaTime), 0.0f, 0.0f);
						}
						if (Global::Variables.keyIn.dHeld) {
							light->RotateAdd3f(glm::degrees(Global::Variables.movementSpeed* deltaTime), 0.0f, 0.0f);
						}
						if (Global::Variables.keyIn.spaceHeld) {
							light->RotateAdd3f(0.0f, glm::degrees(Global::Variables.movementSpeed * deltaTime), 0.0f);
						}
						if (Global::Variables.keyIn.leftControlHeld) {
							light->RotateAdd3f(0.0f, glm::degrees(-Global::Variables.movementSpeed * deltaTime), 0.0f);
						}
					}
				}
			}
			///////////////////////////////////////////////////////////////////////////
			Global::Variables.camera.ChangeMovementSpeed(Global::Variables.movementSpeed);
			camPos = Global::Variables.camera.GetTranslation();
			Global::Variables.camera.BringWith(preloadedObjectsOnScene[0]);
			///////////////////////////////////////////////////////////////////////////
			glm::mat4 viewMatrix = Global::Variables.camera.GetViewTransformMatrix();
			for (unsigned int i = 0; i < preloadedObjectsOnScene.size(); i++) {
				if (i == 0) {
					renderer.SubmitForceRender3D(preloadedObjectsOnScene[i]);
				}
				else {
					renderer.Submit3D(preloadedObjectsOnScene[i], camPos);
				}
			}
			for (unsigned int i = 0; i < objectsOnScene.size(); i++) {
				renderer.Submit3D(objectsOnScene[i], camPos);
			}
			///////////////////////////////////////////////////////////////////////////
			if (GUIEnabled) {
				static bool EnableDebug = true;
				static bool EnableSpawnMenu = true;
				static bool EnableConsole = true;
				static bool EnableInfoPage = true;
				static bool ShouldToggleVSync = false;
				static bool GUIEnabled = true;
				static bool EnableObjectInfoPage = true;
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
						IO::SaveToFile(objectsOnScene, "res/other/", "level.lvl");
					}
					if (ImGui::Button("Close##closeButton")) {
						glfwSetWindowShouldClose(window, GLFW_TRUE);
					}
					ImGui::End();
				}

				if (EnableDebug) {
					Window::DrawDebug(EnableConsole);
				}

				if (EnableSpawnMenu) {
					Window::DrawSpawnWindow(objectsOnScene, selectedObject);
				}

				if (EnableInfoPage) {
					Window::DrawInfoWindow(currentEditorType, currentMode);
				}

				if (EnableObjectInfoPage) {
					if (objectsOnScene.size() > 0 && selectedObject < objectsOnScene.size() && selectedObject >= 0) {
						Window::DrawObjectSettingsWindow(objectsOnScene[selectedObject]);
					}
				}

				if (EnableConsole) {
					System::DrawConsole();
				}
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
			///////////////////////////////////////////////////////////////////////////
			renderer.SimpleFlush(&Global::Variables.camera, Global::Variables.currentWidth, Global::Variables.currentHeight, Global::Variables.FOV, light);
			///////////////////////////////////////////////////////////////////////////
			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
			glfwSwapBuffers(window);
			///////////////////////////////////////////////////////////////////////////
			InputHandler::Flush(&Global::Variables.keyIn, &Global::Variables.mouseIn);
			///////////////////////////////////////////////////////////////////////////
		}
		IO::SaveToFile(objectsOnScene, "res/other/", "level.lvl");
		Global::Variables.config.WriteConfig("res/other/", "config.cfg");
		Mesh::CleanUpCache();
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}
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

	glfwWindowHint(GLFW_DECORATED, false);

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
				window = glfwCreateWindow(Global::Variables.initialWidth, Global::Variables.initialHeight, "Atlas", NULL, NULL);
			}
		}
		else {
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

		bool EnableDebug = true;
		bool EnableSpawnMenu = true;
		bool EnableConsole = true;
		bool EnableInfoPage = true;
		bool ShouldToggleVSync = false;
		bool GUIEnabled = true;


		bool EnableObjectModificationRenderingPage = true;
		bool EnableObjectModificationPositionPage = true;
		bool EnableObjectModificationLightingPage = true;

		bool InputModelHasTexture = false;
		bool InputShaderHasLighting = true;
		bool EnableObjectInfoPage = true;
		char InputStringMeshDirectory[128] = "res/models/";
		char InputStringMeshName[128] = "";
		char InputStringTextureDirectory[128] = "res/images/textures/3d/";
		char InputStringTextureName[128] = "";
		char InputStringShaderDirectory[128] = "res/shaders/";
		char InputStringShaderName[128] = "Lighting.shader";
		glm::vec3 InputRotation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 InputTranslation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 InputScale = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 InputAmbient = glm::vec3(0.5f, 0.5f, 0.5f);
		glm::vec3 InputDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		glm::vec3 InputSpecular = glm::vec3(0.5f, 0.5f, 0.5f);
		int InputShininess = 32;

		char InputModificationStringTextureDirectory[128] = "res/images/textures/3d/";
		char InputModificationStringTextureName[128] = "";
		char InputModificationStringShaderDirectory[128] = "res/shaders/";
		char InputModificationStringShaderName[128] = "Lighting.shader";
		glm::vec3 InputModificationRotation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 InputModificationTranslation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 InputModificationScale = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 InputModificationAmbient = glm::vec3(0.5f, 0.5f, 0.5f);
		glm::vec3 InputModificationDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		glm::vec3 InputModificationSpecular = glm::vec3(0.5f, 0.5f, 0.5f);
		int InputModificationShininess = 32;

		char* items[] = { "Position", "Lighting", "Rendering" };
		char* current_item = items[0];

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

		GLuint selectedObject;
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
			else if ((Global::Variables.keyIn.leftControlHeld && Global::Variables.keyIn.sHeld) || (Global::Variables.keyIn.leftControlPressed && Global::Variables.keyIn.sPressed)) {
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
			if (GUIEnabled) {
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
				//if (ShouldToggleVSync) {
				//	glfwSwapInterval(Global::Variables.VSyncPreference);
				//}

				{
					ImGui::Begin("File", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
					ImGui::Checkbox("Enable Info Page##infoControl", &EnableInfoPage);
					ImGui::Checkbox("Enable Spawn Menu##spawnControl", &EnableSpawnMenu);
					ImGui::Checkbox("Enable Debug Options##debugControl", &EnableDebug);
					ImGui::Checkbox("Enable Object Settings##objectSettingsControl", &EnableObjectInfoPage);
					//ImGui::Separator();
					//ImGui::Checkbox("Enable VSync", &Global::Variables.VSyncPreference);
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
					ImGui::Begin("Debug", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
					ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
					ImGui::Separator();
					ImGui::Checkbox("Enable Console##consoleControl", &EnableConsole);
					ImGui::End();
				}

				if (EnableSpawnMenu) {
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

				if (EnableInfoPage) {
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

				if (EnableObjectInfoPage) {
					if (objectsOnScene.size() > 0 && selectedObject < objectsOnScene.size() && selectedObject >= 0) {

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
								objectsOnScene[selectedObject]->SetTexture(std::string(InputModificationStringTextureDirectory), std::string(InputModificationStringTextureName));
							}
							ImGui::Text("");
							ImGui::Separator();
							ImGui::Text("");
							ImGui::Text("Shader Directory");
							ImGui::InputText("##sin1", InputModificationStringShaderDirectory, IM_ARRAYSIZE(InputModificationStringShaderDirectory));
							ImGui::Text("Shader Name");
							ImGui::InputText("##sin2", InputModificationStringShaderName, IM_ARRAYSIZE(InputModificationStringShaderName));
							if (ImGui::Button("Apply##s1")) {
								objectsOnScene[selectedObject]->SetShader(std::string(InputModificationStringShaderDirectory), std::string(InputModificationStringShaderName));
							}
						}
						else if (current_item == "Position") {

							ImGui::Text("Rotation");
							ImGui::InputFloat3("##in1", &InputModificationRotation[0]);
							if (ImGui::Button("Apply##in1")) {
								objectsOnScene[selectedObject]->RotateVec3(InputModificationRotation);
							}

							ImGui::Separator();

							ImGui::Text("Translation");
							ImGui::InputFloat3("##in2", &InputModificationTranslation[0]);
							if (ImGui::Button("Apply##in2")) {
								objectsOnScene[selectedObject]->TranslateVec3(InputModificationTranslation);
							}

							ImGui::Separator();

							ImGui::Text("Scale");
							ImGui::InputFloat3("##in3", &InputModificationScale[0]);
							if (ImGui::Button("Apply##in3")) {
								objectsOnScene[selectedObject]->ScaleVec3(InputModificationScale);
							}
						}
						else if (current_item == "Lighting") {

							if (ImGui::Button("Toggle Lighting##l1")) {
								objectsOnScene[selectedObject]->SetHasLighting(!objectsOnScene[selectedObject]->GetHasLighting());
							}

							ImGui::Separator();

							ImGui::Text("Ambient Reflection");
							ImGui::InputFloat3("##lin2", &InputModificationAmbient[0]);
							if (ImGui::Button("Apply##lin2")) {
								auto temp = objectsOnScene[selectedObject]->GetMaterial();
								temp.ambient = InputModificationAmbient;
								objectsOnScene[selectedObject]->SetMaterial(temp);
							}

							ImGui::Separator();

							ImGui::Text("Diffuse Reflection");
							ImGui::InputFloat3("##lin3", &InputModificationDiffuse[0]);
							if (ImGui::Button("Apply##lin3")) {
								auto temp = objectsOnScene[selectedObject]->GetMaterial();
								temp.diffuse = InputModificationDiffuse;
								objectsOnScene[selectedObject]->SetMaterial(temp);
							}

							ImGui::Separator();

							ImGui::Text("Specular Reflection");
							ImGui::InputFloat3("##lin4", &InputModificationSpecular[0]);
							if (ImGui::Button("Apply##lin4")) {
								auto temp = objectsOnScene[selectedObject]->GetMaterial();
								temp.ambient = InputModificationSpecular;
								objectsOnScene[selectedObject]->SetMaterial(temp);
							}

							ImGui::Separator();

							ImGui::Text("Reflection Shininess");
							ImGui::SliderInt("##lin5", &InputModificationShininess, 0, 512);
							if (ImGui::Button("Apply##lin5")) {
								auto temp = objectsOnScene[selectedObject]->GetMaterial();
								temp.shininess = InputModificationShininess;
								objectsOnScene[selectedObject]->SetMaterial(temp);
							}
						}

						ImGui::End();
					}
				}

				if (EnableConsole) {
					System::DrawConsole();
				}
			}
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
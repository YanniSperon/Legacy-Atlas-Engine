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

		bool InputModelHasTexture = false;
		char InputStringDirectory[128] = "res/models/";
		char InputStringName[128] = "";
		glm::vec3 InputRotation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 InputTranslation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 InputScale = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 InputAmbient = glm::vec3(0.5f, 0.5f, 0.5f);
		glm::vec3 InputDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		glm::vec3 InputSpecular = glm::vec3(0.5f, 0.5f, 0.5f);
		int InputShininess = 32;
		int InputTexture = 0;

		SimpleRenderer renderer;

		Shader shader("res/shaders/Lighting.shader");
		Shader basic("res/shaders/Basic.shader");
		Shader glassShader("res/shaders/Window.shader");
		Shader shader2D("res/shaders/2D.shader");
		Shader textShader("res/shaders/Text.shader");

		GLuint new4kTex = Loader::LoadTexture("res/images/textures/", "4krgba.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint skyboxTex = Loader::LoadTexture("res/images/other/", "skybox.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);

		GLuint sphereCowTex = Loader::LoadTexture("res/images/other/", "newcow.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint wallTex = Loader::LoadTexture("res/images/textures/", "wall.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint texture1024 = Loader::LoadTexture("res/images/textures/", "texture1024.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint whiteTex = Loader::LoadTexture("res/images/colors/", "white.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint whitetransparentTex = Loader::LoadTexture("res/images/colors/", "whitetransparent.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint blueTex = Loader::LoadTexture("res/images/colors/", "blue.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint redTex = Loader::LoadTexture("res/images/colors/", "red.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint greenTex = Loader::LoadTexture("res/images/colors/", "green.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint glassTex = Loader::LoadTexture("res/images/colors/", "glass.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint yellowTex = Loader::LoadTexture("res/images/colors/", "yellow.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint yellowtransparentTex = Loader::LoadTexture("res/images/colors/", "yellowtransparent.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint tex2D = Loader::LoadTexture("res/images/2d/", "2D.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint pauseMenuTex = Loader::LoadTexture("res/images/menus/", "pausemenu.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint boxTex = Loader::LoadTexture("res/images/textures/", "box.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		TexCoords cursorCoords = Loader::GetTextureCoordinates(0, 15, 1, 16, 16, 16);

		std::vector<GLuint> textures;
		textures.push_back(sphereCowTex);
		textures.push_back(wallTex);
		textures.push_back(whiteTex);
		textures.push_back(whitetransparentTex);
		textures.push_back(blueTex);
		textures.push_back(redTex);
		textures.push_back(greenTex);
		textures.push_back(glassTex);
		textures.push_back(yellowTex);
		textures.push_back(yellowtransparentTex);
		textures.push_back(new4kTex);
		textures.push_back(skyboxTex);
		textures.push_back(texture1024);
		textures.push_back(boxTex);
		textures.push_back(pauseMenuTex);
		textures.push_back(0);

		std::vector<Object*> objectsOnScene;
		std::vector<Object*> preloadedObjectsOnScene;

		LevelEditor::Mode currentMode(LevelEditor::cam);

		Font arial24pt = Font("res/fonts/arial/", "arial.ttf", 24);
		Font timesnewroman32pt = Font("res/fonts/times new roman/", "times.ttf", 32);

		preloadedObjectsOnScene.push_back(new Object(glm::vec3(-50.0f, -50.0f, -50.0f), glm::vec3(50.0f, 50.0f, 50.0f), type::skyBox, "", "", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), skyboxTex, basic.GetShaderID(), true, false));
		preloadedObjectsOnScene.push_back(new Object(glm::vec3(-5.0f, -5.0f, -5.0f), glm::vec3(5.0f, 5.0f, 5.0f), type::blankModel, "res/models/", "plane.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -3.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), whiteTex, shader.GetShaderID(), Material(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f), true, true));

		bool loadFile = true;
		if (loadFile) {
			IO::LoadFile(objectsOnScene, "res/other/", "level.lvl");
		}

		Light* light = new Light(LightIntensity(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec3(0.1f, 0.1f, 0.1f), type::cubeInvertedLighting, "", "", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), yellowTex, shader.GetShaderID(), Material(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f), true, false);

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
		GLuint selectedObjectTexture = 0;

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
					else if (currentMode == LevelEditor::Mode::texture) {
						if (Global::Variables.keyIn.kPressed) {
							if (selectedObjectTexture > 0) {
								selectedObjectTexture--;
							}
						}
						if (Global::Variables.keyIn.lPressed) {
							if (selectedObjectTexture < textures.size() - 1) {
								selectedObjectTexture++;
							}
						}
						if (selectedObject >= 0 && selectedObject < objectsOnScene.size()) {
							objectsOnScene[selectedObject]->SetTexture(textures[selectedObjectTexture]);
						}
					}

					if (Global::Variables.keyIn.leftBracketPressed) {
						if (selectedObject > 0) {
							selectedObject--;
							selectedObjectTexture = Search::LinearSearchVector(textures, objectsOnScene[selectedObject]->GetTextureID());;
						}
					}
					if (Global::Variables.keyIn.rightBracketPressed) {
						if (selectedObject < objectsOnScene.size() - 1) {
							selectedObject++;
							selectedObjectTexture = Search::LinearSearchVector(textures, objectsOnScene[selectedObject]->GetTextureID());;
						}
					}
					if (Global::Variables.keyIn.nPressed) {
						System::Log("Object created!");
						objectsOnScene.push_back(new AABBCollidable(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), type::cubeModel, "", "", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), sphereCowTex, shader.GetShaderID(), Material(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), true, true));
						selectedObject = objectsOnScene.size() - 1;
						selectedObjectTexture = Search::LinearSearchVector(textures, sphereCowTex);;
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

							if (objectsOnScene.size() > 0) {
								selectedObjectTexture = Search::LinearSearchVector(textures, objectsOnScene[selectedObject]->GetTextureID());
							}
							else {
								selectedObjectTexture = 0;
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
				}
				if (Global::Variables.keyIn.tildePressed) {
					EnableConsole = !EnableConsole;
				}
				//if (ShouldToggleVSync) {
				//	glfwSwapInterval(Global::Variables.VSyncPreference);
				//}

				{
					ImGui::Begin("File", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
					ImGui::Checkbox("Enable Debug", &EnableDebug);
					ImGui::Checkbox("Enable Spawn Menu", &EnableSpawnMenu);
					ImGui::Checkbox("Enable Info Page", &EnableInfoPage);
					//ImGui::Separator();
					//ImGui::Checkbox("Enable VSync", &Global::Variables.VSyncPreference);
					ImGui::Separator();
					if (ImGui::Button("Save")) {
						IO::SaveToFile(objectsOnScene, "res/other/", "level.lvl");
					}
					if (ImGui::Button("Close")) {
						glfwSetWindowShouldClose(window, GLFW_TRUE);
					}
					ImGui::End();
				}

				if (EnableDebug) {
					ImGui::Begin("Debug", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
					ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
					ImGui::Separator();
					ImGui::Checkbox("Enable Console", &EnableConsole);
					ImGui::End();
				}

				if (EnableSpawnMenu) {
					ImGui::Begin("Spawn Menu", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
					ImGui::Checkbox("Textured Model", &InputModelHasTexture);
					ImGui::Separator();
					ImGui::SliderInt("Texture", &InputTexture, 0, (textures.size() - 1));
					ImGui::Separator();
					ImGui::InputText("Model Directory", InputStringDirectory, IM_ARRAYSIZE(InputStringDirectory));
					ImGui::InputText("Model Name", InputStringName, IM_ARRAYSIZE(InputStringName));
					ImGui::Separator();
					ImGui::Text("Position");
					ImGui::InputFloat3("Rotation", &InputRotation[0]);
					ImGui::InputFloat3("Translation", &InputTranslation[0]);
					ImGui::InputFloat3("Scale", &InputScale[0]);
					ImGui::Separator();
					ImGui::Text("Lighting");
					ImGui::InputFloat3("Ambient", &InputAmbient[0]);
					ImGui::InputFloat3("Diffuse", &InputDiffuse[0]);
					ImGui::InputFloat3("Specular", &InputSpecular[0]);
					ImGui::SliderInt("Shininess", &InputShininess, 0, 512);
					ImGui::Separator();
					if (ImGui::Button("Spawn")) {
						System::Log("Spawned object with model \"" + std::string(InputStringDirectory) + std::string(InputStringName) + "\" at (" + std::to_string(InputTranslation.x) + ", " + std::to_string(InputTranslation.y) + ", " + std::to_string(InputTranslation.z) + ")");
						if (InputModelHasTexture) {
							objectsOnScene.push_back(new Object(glm::vec3(-5.0f, -5.0f, -5.0f), glm::vec3(5.0f, 5.0f, 5.0f), type::texturedModel, std::string(InputStringDirectory), std::string(InputStringName), InputRotation, InputTranslation, InputScale, textures[InputTexture], shader.GetShaderID(), Material(InputAmbient, InputDiffuse, InputSpecular, ((float)InputShininess)), true, true));
						}
						else {
							objectsOnScene.push_back(new Object(glm::vec3(-5.0f, -5.0f, -5.0f), glm::vec3(5.0f, 5.0f, 5.0f), type::blankModel, std::string(InputStringDirectory), std::string(InputStringName), InputRotation, InputTranslation, InputScale, textures[InputTexture], shader.GetShaderID(), Material(InputAmbient, InputDiffuse, InputSpecular, ((float)InputShininess)), true, true));
						}
						selectedObject = objectsOnScene.size() - 1;
						selectedObjectTexture = textures[InputTexture];
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
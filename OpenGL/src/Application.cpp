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
#include <chrono>
#include <thread>
#include <map>

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

using namespace Engine;



int main(void)
{
	Global::Initialize();
	GLFWwindow* window;

	if (!glfwInit()) {
		return -1;
	}

	if (Global::fullscreen) {
		window = glfwCreateWindow(Global::initialWidth, Global::initialHeight, "Atlas", glfwGetPrimaryMonitor(), NULL);
	}
	else {
		if (Global::forceFullscreen) {
			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			if (mode->width == Global::currentWidth && mode->height == Global::currentHeight) {
				window = glfwCreateWindow(Global::initialWidth, Global::initialHeight, "Atlas", glfwGetPrimaryMonitor(), NULL);
			}
			else {
				window = glfwCreateWindow(Global::initialWidth, Global::initialHeight, "Atlas", NULL, NULL);
			}
		}
		else {
			window = glfwCreateWindow(Global::initialWidth, Global::initialHeight, "Atlas", NULL, NULL);
		}
	}

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	//glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);

	glfwSwapInterval(Global::VSyncPreference);

	if (glewInit() != GLEW_OK) {
		System::Err("Error initializing GLEW (OpenGL)");
	}

	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();

	vr::IVRSystem* vr_pointer = NULL;

	if (Global::hasVR) {
		vr::EVRInitError eError = vr::VRInitError_None;
		vr_pointer = VR_Init(&eError, vr::VRApplication_Scene); // VRApplication_Background OR VRApplication_Scene OR VRApplication_Overlay OR VRApplication_Utility
		if (eError != vr::VRInitError_None)
		{
			Global::hasVR = false;
			vr_pointer = NULL;
			std::string error = VR_GetVRInitErrorAsEnglishDescription(eError);
			System::Err("Unable to init VR runtime: \"" + error + "\"");
		}
	}

	printf("Vendor: %s\nModel: %s\nVersion: %s\n", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));

	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if (Global::mouseMode == MouseMode::raw) {
			if (glfwRawMouseMotionSupported())
				glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		}
		glfwSetCursorPosCallback(window, Callbacks::cursorPositionCallback);
		glfwSetKeyCallback(window, Callbacks::keyCallback);
		glfwSetMouseButtonCallback(window, Callbacks::mouseButtonCallback);
		glfwSetFramebufferSizeCallback(window, Callbacks::framebufferSizeCallback);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		const char* attackSFXFilename = "res/audio/sfx/attack.wav";
		const char* explosionSFXFilename = "res/audio/sfx/explosion.wav";
		const char* jumpSFXFilename = "res/audio/sfx/jump.wav";
		const char* pickupSFXFilename = "res/audio/sfx/pickup.wav";
		const char* selectSFXFilename = "res/audio/sfx/select.wav";
		const char* shootSFXFilename = "res/audio/sfx/shoot.wav";
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		engine->setSoundVolume(0);
		irrklang::ISound* attackSFX = engine->play2D(attackSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		irrklang::ISound* explosionSFX = engine->play2D(explosionSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		irrklang::ISound* jumpSFX = engine->play2D(jumpSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		irrklang::ISound* pickupSFX = engine->play2D(pickupSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		irrklang::ISound* selectSFX = engine->play2D(selectSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		irrklang::ISound* shootSFX = engine->play2D(shootSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		//engine->play2D(steamSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glEnable(GL_DEPTH_TEST);
		
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glFrontFace(GL_CW);

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

		Object2D pausemenu = Object2D(glm::vec2(0.0f, 0.0f), glm::vec2(1920.0f, 1080.0f), 0.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), pauseMenuTex, shader2D.GetShaderID(), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
		LevelEditor::Mode currentMode(LevelEditor::cam);

		Font arial24pt = Font("res/fonts/arial/", "arial.ttf", 24);
		Font timesnewroman32pt = Font("res/fonts/times new roman/", "times.ttf", 32);

		preloadedObjectsOnScene.push_back(new Object(glm::vec3(-50.0f, -50.0f, -50.0f), glm::vec3(50.0f, 50.0f, 50.0f), type::skyBox, "", "", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), skyboxTex, basic.GetShaderID(), true, false));
		preloadedObjectsOnScene.push_back(new Object(glm::vec3(-5.0f, -5.0f, -5.0f), glm::vec3(5.0f, 5.0f, 5.0f), type::blankModel, "res/models/", "plane.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -3.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), whiteTex, shader.GetShaderID(), Material(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f), true, true));
		


		bool loadFile = true;
		if (loadFile) {
			//IO::LoadFile(gui, "res/other/", "gui.gui");
			IO::LoadFile(objectsOnScene, "res/other/", "level.lvl");
		}



		Light* light = new Light(LightIntensity(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec3(0.1f, 0.1f, 0.1f), type::cubeInvertedLighting, "", "", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), yellowTex, shader.GetShaderID(), Material(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f), true, true);

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
		ImGui_ImplGlfwGL3_Init(window, false);
		ImGui::StyleColorsDark();

		glm::vec3 camPos(0.0f, 0.0f, 0.0f);
		glfwSetCursorPos(window, 0.0, 0.0);

		bool editorEnabled = true;

		float timeConstant = 1.0f;
		double lastTime = glfwGetTime();
		double deltaT = 0, nowTime = 0;
		engine->setSoundVolume(1);

		Timer textureChangeTimer(0.5f);
		textureChangeTimer.Start();
		Timer selectionChangeTimer(0.5f);
		selectionChangeTimer.Start();
		Timer spawnTimer(0.5f);
		spawnTimer.Start();

		GLuint selectedObject = objectsOnScene.size() - 1;
		GLuint selectedObjectTexture = 0;// Search::LinearSearchVector(textures, objectsOnScene[selectedObject]->GetTextureID());



		while (!glfwWindowShouldClose(window))
		{
			///////////////////////////////////////////////////////////////////////////
			nowTime = glfwGetTime();
			deltaT = (nowTime - lastTime);
			lastTime = nowTime;
			///////////////////////////////////////////////////////////////////////////
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			ImGui_ImplGlfwGL3_NewFrame();
			///////////////////////////////////////////////////////////////////////////
			float deltaTime = (float)deltaT * timeConstant;
			///////////////////////////////////////////////////////////////////////////
			if (Global::keyIn.fPressed) {
				glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, Global::currentWidth, Global::currentHeight, GLFW_DONT_CARE);
			}
			///////////////////////////////////////////////////////////////////////////
			if (Global::isPaused) {
				editorEnabled = false;
				currentMode = LevelEditor::Mode::cam;
			}
			else {
				editorEnabled = true;
			}
			///////////////////////////////////////////////////////////////////////////
			if (editorEnabled) {
				///////////////////////////////////////////////////////////////////////////
				textureChangeTimer.ElapseTime(deltaTime);
				selectionChangeTimer.ElapseTime(deltaTime);
				spawnTimer.ElapseTime(deltaTime);

				if (Global::keyIn.leftControlPressed && Global::keyIn.qPressed) {
					glfwSetWindowShouldClose(window, GLFW_TRUE);
				}
				if (Global::keyIn.onePressed) {
					currentEditorType = LevelEditor::EditorType::scene;
				}
				else if (Global::keyIn.twoPressed) {
					currentEditorType = LevelEditor::EditorType::text;
				}
				else if (Global::keyIn.threePressed) {
					currentEditorType = LevelEditor::EditorType::light;
				}
				if ((objectsOnScene.size() > 0 && currentEditorType == LevelEditor::EditorType::scene) || (currentEditorType == LevelEditor::EditorType::light)) {
					if (Global::keyIn.cPressed) {
						currentMode = LevelEditor::Mode::cam;
					}
					else if (Global::keyIn.ePressed) {
						currentMode = LevelEditor::Mode::scale;
					}
					else if (Global::keyIn.rPressed) {
						currentMode = LevelEditor::Mode::rotate;
					}
					else if (Global::keyIn.vPressed) {
						currentMode = LevelEditor::Mode::translate;
					}
					else if (Global::keyIn.tPressed) {
						currentMode = LevelEditor::Mode::texture;
					}
					else if (Global::keyIn.oPressed) {
						currentMode = LevelEditor::Mode::output;
					}
				}
				else {
					currentMode = LevelEditor::Mode::cam;
				}
				///////////////////////////////////////////////////////////////////////////
				if (currentEditorType == LevelEditor::EditorType::scene) {
					if (currentMode == LevelEditor::Mode::scale) {
						if (Global::keyIn.wPressed) {
							objectsOnScene[selectedObject]->ScaleAdd3f(0.0f, 0.0f, -Global::movementSpeed * deltaTime);
						}
						if (Global::keyIn.sPressed) {
							objectsOnScene[selectedObject]->ScaleAdd3f(0.0f, 0.0f, Global::movementSpeed * deltaTime);
						}
						if (Global::keyIn.aPressed) {
							objectsOnScene[selectedObject]->ScaleAdd3f(-Global::movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (Global::keyIn.dPressed) {
							objectsOnScene[selectedObject]->ScaleAdd3f(Global::movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (Global::keyIn.spacePressed) {
							objectsOnScene[selectedObject]->ScaleAdd3f(0.0f, Global::movementSpeed * deltaTime, 0.0f);
						}
						if (Global::keyIn.leftControlPressed) {
							objectsOnScene[selectedObject]->ScaleAdd3f(0.0f, -Global::movementSpeed * deltaTime, 0.0f);
						}
					}
					else if (currentMode == LevelEditor::Mode::translate) {
						if (Global::keyIn.wPressed) {
							objectsOnScene[selectedObject]->TranslateAdd3f(0.0f, 0.0f, -Global::movementSpeed * deltaTime);
						}
						if (Global::keyIn.sPressed) {
							objectsOnScene[selectedObject]->TranslateAdd3f(0.0f, 0.0f, Global::movementSpeed * deltaTime);
						}
						if (Global::keyIn.aPressed) {
							objectsOnScene[selectedObject]->TranslateAdd3f(-Global::movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (Global::keyIn.dPressed) {
							objectsOnScene[selectedObject]->TranslateAdd3f(Global::movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (Global::keyIn.spacePressed) {
							objectsOnScene[selectedObject]->TranslateAdd3f(0.0f, Global::movementSpeed * deltaTime, 0.0f);
						}
						if (Global::keyIn.leftControlPressed) {
							objectsOnScene[selectedObject]->TranslateAdd3f(0.0f, -Global::movementSpeed * deltaTime, 0.0f);
						}
					}
					else if (currentMode == LevelEditor::Mode::cam) {
						if (Global::keyIn.wPressed) {
							Global::camera.MoveForward(deltaTime);
						}
						if (Global::keyIn.sPressed) {
							Global::camera.MoveBackward(deltaTime);
						}
						if (Global::keyIn.aPressed) {
							Global::camera.StrafeLeft(deltaTime);
						}
						if (Global::keyIn.dPressed) {
							Global::camera.StrafeRight(deltaTime);
						}
						if (Global::keyIn.spacePressed) {
							Global::camera.MoveUp(deltaTime);
						}
						if (Global::keyIn.leftControlPressed) {
							Global::camera.MoveDown(deltaTime);
						}
					}
					else if (currentMode == LevelEditor::Mode::rotate) {
						if (Global::keyIn.wPressed) {
							objectsOnScene[selectedObject]->RotateAdd3f(0.0f, 0.0f, glm::degrees(-Global::movementSpeed * deltaTime));
						}
						if (Global::keyIn.sPressed) {
							objectsOnScene[selectedObject]->RotateAdd3f(0.0f, 0.0f, glm::degrees(Global::movementSpeed * deltaTime));
						}
						if (Global::keyIn.aPressed) {
							objectsOnScene[selectedObject]->RotateAdd3f(glm::degrees(-Global::movementSpeed * deltaTime), 0.0f, 0.0f);
						}
						if (Global::keyIn.dPressed) {
							objectsOnScene[selectedObject]->RotateAdd3f(glm::degrees(Global::movementSpeed * deltaTime), 0.0f, 0.0f);
						}
						if (Global::keyIn.spacePressed) {
							objectsOnScene[selectedObject]->RotateAdd3f(0.0f, glm::degrees(Global::movementSpeed * deltaTime), 0.0f);
						}
						if (Global::keyIn.leftControlPressed) {
							objectsOnScene[selectedObject]->RotateAdd3f(0.0f, glm::degrees(-Global::movementSpeed * deltaTime), 0.0f);
						}
					}
					else if (currentMode == LevelEditor::Mode::texture) {
						if (Global::keyIn.kPressed) {
							if (textureChangeTimer.HasFinished()) {
								if (selectedObjectTexture > 0) {
									selectedObjectTexture--;
									textureChangeTimer.Reset(0.5f);
									textureChangeTimer.Start();
								}
							}
						}
						if (Global::keyIn.lPressed) {
							if (textureChangeTimer.HasFinished()) {
								if (selectedObjectTexture < textures.size() - 1) {
									selectedObjectTexture++;
									textureChangeTimer.Reset(0.5f);
									textureChangeTimer.Start();
								}
							}
						}
						if (selectedObject >= 0 && selectedObject < objectsOnScene.size()) {
							objectsOnScene[selectedObject]->SetTexture(textures[selectedObjectTexture]);
						}
					}
					else if (currentMode == LevelEditor::Mode::output) {
						if (Global::keyIn.sPressed) {
							IO::SaveToFile(objectsOnScene, "res/other/", "level.lvl");
							currentMode = LevelEditor::Mode::cam;
						}
					}
					if (Global::keyIn.leftBracketPressed) {
						if (selectionChangeTimer.HasFinished()) {
							if (selectedObject > 0) {
								selectedObject--;
								selectedObjectTexture = Search::LinearSearchVector(textures, objectsOnScene[selectedObject]->GetTextureID());
								selectionChangeTimer.Reset(0.5f);
								selectionChangeTimer.Start();
							}
						}
					}
					if (Global::keyIn.rightBracketPressed) {
						if (selectionChangeTimer.HasFinished()) {
							if (selectedObject < objectsOnScene.size() - 1) {
								selectedObject++;
								selectedObjectTexture = Search::LinearSearchVector(textures, objectsOnScene[selectedObject]->GetTextureID());
								selectionChangeTimer.Reset(0.5f);
								selectionChangeTimer.Start();
							}
						}
					}
					if (Global::keyIn.nPressed) {
						if (spawnTimer.HasFinished()) {
							objectsOnScene.push_back(new AABBCollidable(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), type::cubeModel, "", "", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), sphereCowTex, shader.GetShaderID(), Material(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), true, true));
							selectedObject = objectsOnScene.size() - 1;
							selectedObjectTexture = 0;
							spawnTimer.Reset(0.5f);
							spawnTimer.Start();
						}
					}
					if (Global::keyIn.backspacePressed) {
						if (spawnTimer.HasFinished()) {
							if (objectsOnScene.size() > 0) {
								delete objectsOnScene[selectedObject];
								objectsOnScene.erase(objectsOnScene.begin() + selectedObject);
								if (selectedObject > 0) {
									selectedObject--;
								}
								if (objectsOnScene.size() >= 0) {
									selectedObjectTexture = Search::LinearSearchVector(textures, objectsOnScene[selectedObject]->GetTextureID());
								} else {
									selectedObjectTexture = 0;
								}
								spawnTimer.Reset(0.5f);
								spawnTimer.Start();
							}
						}
					}
				}
				else if (currentEditorType == LevelEditor::EditorType::light) {
					if (currentMode == LevelEditor::Mode::scale) {
						if (Global::keyIn.wPressed) {
							light->ScaleAdd3f(0.0f, 0.0f, -Global::movementSpeed * deltaTime);
						}
						if (Global::keyIn.sPressed) {
							light->ScaleAdd3f(0.0f, 0.0f, Global::movementSpeed * deltaTime);
						}
						if (Global::keyIn.aPressed) {
							light->ScaleAdd3f(-Global::movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (Global::keyIn.dPressed) {
							light->ScaleAdd3f(Global::movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (Global::keyIn.spacePressed) {
							light->ScaleAdd3f(0.0f, Global::movementSpeed * deltaTime, 0.0f);
						}
						if (Global::keyIn.leftControlPressed) {
							light->ScaleAdd3f(0.0f, -Global::movementSpeed * deltaTime, 0.0f);
						}
					}
					else if (currentMode == LevelEditor::Mode::translate) {
						if (Global::keyIn.wPressed) {
							light->TranslateAdd3f(0.0f, 0.0f, -Global::movementSpeed * deltaTime);
						}
						if (Global::keyIn.sPressed) {
							light->TranslateAdd3f(0.0f, 0.0f, Global::movementSpeed * deltaTime);
						}
						if (Global::keyIn.aPressed) {
							light->TranslateAdd3f(-Global::movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (Global::keyIn.dPressed) {
							light->TranslateAdd3f(Global::movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (Global::keyIn.spacePressed) {
							light->TranslateAdd3f(0.0f, Global::movementSpeed * deltaTime, 0.0f);
						}
						if (Global::keyIn.leftControlPressed) {
							light->TranslateAdd3f(0.0f, -Global::movementSpeed * deltaTime, 0.0f);
						}
					}
					else if (currentMode == LevelEditor::Mode::cam) {
						if (Global::keyIn.wPressed) {
							Global::camera.MoveForward(deltaTime);
						}
						if (Global::keyIn.sPressed) {
							Global::camera.MoveBackward(deltaTime);
						}
						if (Global::keyIn.aPressed) {
							Global::camera.StrafeLeft(deltaTime);
						}
						if (Global::keyIn.dPressed) {
							Global::camera.StrafeRight(deltaTime);
						}
						if (Global::keyIn.spacePressed) {
							Global::camera.MoveUp(deltaTime);
						}
						if (Global::keyIn.leftControlPressed) {
							Global::camera.MoveDown(deltaTime);
						}
					}
					else if (currentMode == LevelEditor::Mode::rotate) {
						if (Global::keyIn.wPressed) {
							light->RotateAdd3f(0.0f, 0.0f, glm::degrees(-Global::movementSpeed * deltaTime));
						}
						if (Global::keyIn.sPressed) {
							light->RotateAdd3f(0.0f, 0.0f, glm::degrees(Global::movementSpeed * deltaTime));
						}
						if (Global::keyIn.aPressed) {
							light->RotateAdd3f(glm::degrees(-Global::movementSpeed * deltaTime), 0.0f, 0.0f);
						}
						if (Global::keyIn.dPressed) {
							light->RotateAdd3f(glm::degrees(Global::movementSpeed* deltaTime), 0.0f, 0.0f);
						}
						if (Global::keyIn.spacePressed) {
							light->RotateAdd3f(0.0f, glm::degrees(Global::movementSpeed * deltaTime), 0.0f);
						}
						if (Global::keyIn.leftControlPressed) {
							light->RotateAdd3f(0.0f, glm::degrees(-Global::movementSpeed * deltaTime), 0.0f);
						}
					}
				}
			}
			///////////////////////////////////////////////////////////////////////////
			Global::camera.ChangeMovementSpeed(Global::movementSpeed);
			camPos = Global::camera.GetTranslation();
			Global::camera.BringWith(preloadedObjectsOnScene[0]);
			///////////////////////////////////////////////////////////////////////////
			glm::mat4 viewMatrix = Global::camera.GetViewTransformMatrix();
			///////////////////////////////////////////////////////////////////////////
			for (unsigned int i = 0; i < preloadedObjectsOnScene.size(); i++) {
				if (i == 0) {
					renderer.SubmitForceRender3D(preloadedObjectsOnScene[i]);
				}
				else {
					renderer.Submit3D(preloadedObjectsOnScene[i], camPos);
				}
			}
			///////////////////////////////////////////////////////////////////////////
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
			renderer.SimpleFlush(&Global::camera, Global::currentWidth, Global::currentHeight, Global::FOV, light);
			///////////////////////////////////////////////////////////////////////////
			{
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}
			///////////////////////////////////////////////////////////////////////////
			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
			glfwSwapBuffers(window);
			glfwPollEvents();
			///////////////////////////////////////////////////////////////////////////
		}
		IO::SaveToFile(objectsOnScene, "res/other/", "level.lvl");
		Global::config.WriteConfig("res/other/", "config.cfg");
		Mesh::CleanUpCache();
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}
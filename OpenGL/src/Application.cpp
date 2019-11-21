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
#include "Console.h"
#include "Overlay.h"
#include "Button.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/quaternion.hpp"
#include "primitives/Vertex.h"
#include "primitives/ShapeGenerator.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

Config config = Config("res/other/", "config.cfg");
//#define DGPU

#ifdef DGPU
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}
#endif

static bool fullscreen = config.GetFullscreenPreference();
static bool forceFullscreen = config.GetForceFullscreen();
static float mouseSensitivity = config.GetMouseSensitivityPreference();
static float FOV = config.GetFOVPreference();

static bool isPaused = false;


static int oldMouseX = 0;
static int oldMouseY = 0;
static float movementSpeed = 10.0f;

Camera camera = Camera(true, movementSpeed, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), mouseSensitivity);

static int initialWidth = config.GetInitialWidthPreference();
static int initialHeight = config.GetInitialHeightPreference();

static bool hasVR = config.GetVRPreference();

static MouseMode mouseMode = config.GetMouseMode();

static int currentWidth = initialWidth;
static int currentHeight = initialHeight;

static int HP = 100;

static bool VSyncPreference = config.GetVSyncPreference();

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		aPressed = true;
	}
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
		aPressed = false;
	}

	if (key == GLFW_KEY_B && action == GLFW_PRESS) {
		bPressed = true;
	}
	else if (key == GLFW_KEY_B && action == GLFW_RELEASE) {
		bPressed = false;
	}

	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		cPressed = true;
	}
	else if (key == GLFW_KEY_C && action == GLFW_RELEASE) {
		cPressed = false;
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		dPressed = true;
	}
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
		dPressed = false;
	}

	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		ePressed = true;
	}
	else if (key == GLFW_KEY_E && action == GLFW_RELEASE) {
		ePressed = false;
	}

	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		fPressed = true;
	}
	else if (key == GLFW_KEY_F && action == GLFW_RELEASE) {
		fPressed = false;
	}

	if (key == GLFW_KEY_G && action == GLFW_PRESS) {
		gPressed = true;
	}
	else if (key == GLFW_KEY_G && action == GLFW_RELEASE) {
		gPressed = false;
	}

	if (key == GLFW_KEY_H && action == GLFW_PRESS) {
		hPressed = true;
	}
	else if (key == GLFW_KEY_H && action == GLFW_RELEASE) {
		hPressed = false;
	}

	if (key == GLFW_KEY_I && action == GLFW_PRESS) {
		iPressed = true;
	}
	else if (key == GLFW_KEY_I && action == GLFW_RELEASE) {
		iPressed = false;
	}

	if (key == GLFW_KEY_J && action == GLFW_PRESS) {
		jPressed = true;
	}
	else if (key == GLFW_KEY_J && action == GLFW_RELEASE) {
		jPressed = false;
	}

	if (key == GLFW_KEY_K && action == GLFW_PRESS) {
		kPressed = true;
	}
	else if (key == GLFW_KEY_K && action == GLFW_RELEASE) {
		kPressed = false;
	}

	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		lPressed = true;
	}
	else if (key == GLFW_KEY_L && action == GLFW_RELEASE) {
		lPressed = false;
	}

	if (key == GLFW_KEY_M && action == GLFW_PRESS) {
		mPressed = true;
	}
	else if (key == GLFW_KEY_M && action == GLFW_RELEASE) {
		mPressed = false;
	}

	if (key == GLFW_KEY_N && action == GLFW_PRESS) {
		nPressed = true;
	}
	else if (key == GLFW_KEY_N && action == GLFW_RELEASE) {
		nPressed = false;
	}

	if (key == GLFW_KEY_O && action == GLFW_PRESS) {
		oPressed = true;
	}
	else if (key == GLFW_KEY_O && action == GLFW_RELEASE) {
		oPressed = false;
	}

	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		pPressed = true;
	}
	else if (key == GLFW_KEY_P && action == GLFW_RELEASE) {
		pPressed = false;
	}

	if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		qPressed = true;
	}
	else if (key == GLFW_KEY_Q && action == GLFW_RELEASE) {
		qPressed = false;
	}

	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		rPressed = true;
	}
	else if (key == GLFW_KEY_R && action == GLFW_RELEASE) {
		rPressed = false;
	}

	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		sPressed = true;
	}
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
		sPressed = false;
	}

	if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		tPressed = true;
	}
	else if (key == GLFW_KEY_T && action == GLFW_RELEASE) {
		tPressed = false;
	}

	if (key == GLFW_KEY_U && action == GLFW_PRESS) {
		uPressed = true;
	}
	else if (key == GLFW_KEY_U && action == GLFW_RELEASE) {
		uPressed = false;
	}

	if (key == GLFW_KEY_V && action == GLFW_PRESS) {
		vPressed = true;
	}
	else if (key == GLFW_KEY_V && action == GLFW_RELEASE) {
		vPressed = false;
	}

	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		wPressed = true;
	}
	else if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
		wPressed = false;
	}

	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		xPressed = true;
	}
	else if (key == GLFW_KEY_X && action == GLFW_RELEASE) {
		xPressed = false;
	}

	if (key == GLFW_KEY_Y && action == GLFW_PRESS) {
		yPressed = true;
	}
	else if (key == GLFW_KEY_Y && action == GLFW_RELEASE) {
		yPressed = false;
	}

	if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		zPressed = true;
	}
	else if (key == GLFW_KEY_Z && action == GLFW_RELEASE) {
		zPressed = false;
	}

	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS) {
		leftControlPressed = true;
	}
	else if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE) {
		leftControlPressed = false;
	}

	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
		leftShiftPressed = true;
		movementSpeed *= 2.0f;
	}
	else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) {
		leftShiftPressed = false;
		movementSpeed /= 2.0f;
	}

	if (key == GLFW_KEY_CAPS_LOCK && action == GLFW_PRESS) {
		capsLockPressed = true;
		movementSpeed /= 2.0f;
	}
	else if (key == GLFW_KEY_CAPS_LOCK && action == GLFW_RELEASE) {
		capsLockPressed = false;
		movementSpeed *= 2.0f;
	}

	if (key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS) {
		leftAltPressed = true;
	}
	else if (key == GLFW_KEY_LEFT_ALT && action == GLFW_RELEASE) {
		leftAltPressed = false;
	}

	if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
		tabPressed = true;
	}
	else if (key == GLFW_KEY_TAB && action == GLFW_RELEASE) {
		tabPressed = false;
	}

	if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS) {
		tildePressed = true;
	}
	else if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_RELEASE) {
		tildePressed = false;
	}

	if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
		zeroPressed = true;
	}
	else if (key == GLFW_KEY_0 && action == GLFW_RELEASE) {
		zeroPressed = false;
	}

	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		onePressed = true;
	}
	else if (key == GLFW_KEY_1 && action == GLFW_RELEASE) {
		onePressed = false;
	}

	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		twoPressed = true;
	}
	else if (key == GLFW_KEY_2 && action == GLFW_RELEASE) {
		twoPressed = false;
	}

	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		threePressed = true;
	}
	else if (key == GLFW_KEY_3 && action == GLFW_RELEASE) {
		threePressed = false;
	}

	if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
		fourPressed = true;
	}
	else if (key == GLFW_KEY_4 && action == GLFW_RELEASE) {
		fourPressed = false;
	}

	if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
		fivePressed = true;
	}
	else if (key == GLFW_KEY_5 && action == GLFW_RELEASE) {
		fivePressed = false;
	}

	if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
		sixPressed = true;
	}
	else if (key == GLFW_KEY_6 && action == GLFW_RELEASE) {
		sixPressed = false;
	}

	if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
		sevenPressed = true;
	}
	else if (key == GLFW_KEY_7 && action == GLFW_RELEASE) {
		sevenPressed = false;
	}

	if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
		eightPressed = true;
	}
	else if (key == GLFW_KEY_8 && action == GLFW_RELEASE) {
		eightPressed = false;
	}

	if (key == GLFW_KEY_9 && action == GLFW_PRESS) {
		ninePressed = true;
	}
	else if (key == GLFW_KEY_9 && action == GLFW_RELEASE) {
		ninePressed = false;
	}

	if (key == GLFW_KEY_MINUS && action == GLFW_PRESS) {
		minusPressed = true;
	}
	else if (key == GLFW_KEY_MINUS && action == GLFW_RELEASE) {
		minusPressed = false;
	}

	if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS) {
		equalPressed = true;
	}
	else if (key == GLFW_KEY_EQUAL && action == GLFW_RELEASE) {
		equalPressed = false;
	}

	if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS) {
		backspacePressed = true;
	}
	else if (key == GLFW_KEY_BACKSPACE && action == GLFW_RELEASE) {
		backspacePressed = false;
	}

	if (key == GLFW_KEY_DELETE && action == GLFW_PRESS) {
		deletePressed = true;
	}
	else if (key == GLFW_KEY_DELETE && action == GLFW_RELEASE) {
		deletePressed = false;
	}

	if (key == GLFW_KEY_LEFT_BRACKET && action == GLFW_PRESS) {
		leftBracketPressed = true;
	}
	else if (key == GLFW_KEY_LEFT_BRACKET && action == GLFW_RELEASE) {
		leftBracketPressed = false;
	}

	if (key == GLFW_KEY_RIGHT_BRACKET && action == GLFW_PRESS) {
		rightBracketPressed = true;
	}
	else if (key == GLFW_KEY_RIGHT_BRACKET && action == GLFW_RELEASE) {
		rightBracketPressed = false;
	}

	if (key == GLFW_KEY_BACKSLASH && action == GLFW_PRESS) {
		backslashPressed = true;
	}
	else if (key == GLFW_KEY_BACKSLASH && action == GLFW_RELEASE) {
		backslashPressed = false;
	}

	if (key == GLFW_KEY_SLASH && action == GLFW_PRESS) {
		frontslashPressed = true;
	}
	else if (key == GLFW_KEY_SLASH && action == GLFW_RELEASE) {
		frontslashPressed = false;
	}

	if (key == GLFW_KEY_COMMA && action == GLFW_PRESS) {
		commaPressed = true;
	}
	else if (key == GLFW_KEY_COMMA && action == GLFW_RELEASE) {
		commaPressed = false;
	}

	if (key == GLFW_KEY_PERIOD && action == GLFW_PRESS) {
		periodPressed = true;
	}
	else if (key == GLFW_KEY_PERIOD && action == GLFW_RELEASE) {
		periodPressed = false;
	}

	if (key == GLFW_KEY_BACKSLASH && action == GLFW_PRESS) {
		backslashPressed = true;
	}
	else if (key == GLFW_KEY_BACKSLASH && action == GLFW_RELEASE) {
		backslashPressed = false;
	}

	if (key == GLFW_KEY_SEMICOLON && action == GLFW_PRESS) {
		semiColonPressed = true;
	}
	else if (key == GLFW_KEY_SEMICOLON && action == GLFW_RELEASE) {
		semiColonPressed = false;
	}

	if (key == GLFW_KEY_APOSTROPHE && action == GLFW_PRESS) {
		apostrophePressed = true;
	}
	else if (key == GLFW_KEY_APOSTROPHE && action == GLFW_RELEASE) {
		apostrophePressed = false;
	}

	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
		enterPressed = true;
	}
	else if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE) {
		enterPressed = false;
	}

	if (key == GLFW_KEY_DELETE && action == GLFW_PRESS) {
		deletePressed = true;
	}
	else if (key == GLFW_KEY_DELETE && action == GLFW_RELEASE) {
		deletePressed = false;
	}

	if (key == GLFW_KEY_RIGHT_SHIFT && action == GLFW_PRESS) {
		rightShiftPressed = true;
	}
	else if (key == GLFW_KEY_RIGHT_SHIFT && action == GLFW_RELEASE) {
		rightShiftPressed = false;
	}

	if (key == GLFW_KEY_RIGHT_CONTROL && action == GLFW_PRESS) {
		rightControlPressed = true;
	}
	else if (key == GLFW_KEY_RIGHT_CONTROL && action == GLFW_RELEASE) {
		rightControlPressed = false;
	}

	if (key == GLFW_KEY_RIGHT_ALT && action == GLFW_PRESS) {
		rightAltPressed = true;
	}
	else if (key == GLFW_KEY_RIGHT_ALT && action == GLFW_RELEASE) {
		rightAltPressed = false;
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		leftPressed = true;
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
		leftPressed = false;
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		rightPressed = true;
	}
	else if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
		rightPressed = false;
	}

	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		upPressed = true;
	}
	else if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
		upPressed = false;
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		downPressed = true;
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
		downPressed = false;
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		if (!escapePressed) {
			if (!isPaused) {
				oldMouseX = mouseXPos;
				oldMouseY = mouseYPos;
				isPaused = true;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				glfwSetCursorPos(window, (double)(currentWidth / 2), (double)(currentHeight / 2));
			}
			else {
				mouseXPos = oldMouseX;
				mouseYPos = oldMouseY;
				isPaused = false;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				glfwSetCursorPos(window, mouseXPos, mouseYPos);
			}
		}
		else {
			escapePressed = true;
		}
	}
	else if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
		escapePressed = false;
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		spacePressed = true;
	}
	else if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
		spacePressed = false;
	}
}
static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	mouseXPos = xpos;
	mouseYPos = ypos;
	if (!isPaused) {
		if (ypos * mouseSensitivity > 89.0f) {
			double newMouseY = 89.0f / mouseSensitivity;
			glfwSetCursorPos(window, xpos, newMouseY);
			camera.LookAt(xpos, newMouseY);
		}
		else if (ypos * mouseSensitivity < -89.0f) {
			double newMouseY = -89.0f / mouseSensitivity;
			glfwSetCursorPos(window, xpos, newMouseY);
			camera.LookAt(xpos, newMouseY);
		}
		else {
			camera.LookAt(xpos, ypos);
		}
	}
}
static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	currentWidth = width;
	currentHeight = height;
	if (width > 0 && height > 0) {
		glViewport(0, 0, width, height);
	}
}
static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		leftClicked = true;
		printf("Left clicked at (%f, %f)\n", mouseXPos, mouseYPos);
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		leftClicked = false;
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		rightClicked = true;
		printf("Right clicked at (%f, %f)\n", mouseXPos, mouseYPos);
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
		rightClicked = false;
	}
}
int main(void)
{
	Console::Setup();
	GLFWwindow* window;

	if (!glfwInit()) {
		return -1;
	}

	if (fullscreen) {
		window = glfwCreateWindow(initialWidth, initialHeight, "Atlas", glfwGetPrimaryMonitor(), NULL);
	}
	else {
		if (forceFullscreen) {
			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			if (mode->width == currentWidth && mode->height == currentHeight) {
				window = glfwCreateWindow(initialWidth, initialHeight, "Atlas", glfwGetPrimaryMonitor(), NULL);
			}
			else {
				window = glfwCreateWindow(initialWidth, initialHeight, "Atlas", NULL, NULL);
			}
		}
		else {
			window = glfwCreateWindow(initialWidth, initialHeight, "Atlas", NULL, NULL);
		}
	}

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	//glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);

	glfwSwapInterval(VSyncPreference);

	if (glewInit() != GLEW_OK) {
		Console::Err("Error initializing GLEW (OpenGL)");
	}

	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();

	vr::IVRSystem* vr_pointer = NULL;

	if (hasVR) {
		vr::EVRInitError eError = vr::VRInitError_None;
		vr_pointer = VR_Init(&eError, vr::VRApplication_Scene); // VRApplication_Background OR VRApplication_Scene OR VRApplication_Overlay OR VRApplication_Utility
		if (eError != vr::VRInitError_None)
		{
			hasVR = false;
			vr_pointer = NULL;
			std::string error = VR_GetVRInitErrorAsEnglishDescription(eError);
			Console::Err("Unable to init VR runtime: \"" + error + "\"");
		}
	}

	printf("Vendor: %s\nModel: %s\nVersion: %s\n", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));

	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if (mouseMode == MouseMode::raw) {
			if (glfwRawMouseMotionSupported())
				glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		}
		glfwSetCursorPosCallback(window, cursorPositionCallback);
		glfwSetKeyCallback(window, keyCallback);
		glfwSetMouseButtonCallback(window, mouseButtonCallback);
		glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
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
		Mode currentMode(cam);

		Font arial24pt = Font("res/fonts/arial/", "arial.ttf", 24);
		Font timesnewroman32pt = Font("res/fonts/times new roman/", "times.ttf", 32);

		preloadedObjectsOnScene.push_back(new Object(glm::vec3(-50.0f, -50.0f, -50.0f), glm::vec3(50.0f, 50.0f, 50.0f), type::skyBox, "", "", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), skyboxTex, basic.GetShaderID(), true, false));
		preloadedObjectsOnScene.push_back(new Object(glm::vec3(-5.0f, -5.0f, -5.0f), glm::vec3(5.0f, 5.0f, 5.0f), type::blankModel, "res/models/", "plane.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -3.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), whiteTex, shader.GetShaderID(), Material(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f), true, true));
		
		
		
		Overlay pauseMenuOverlay;
		pauseMenuOverlay.AddObject2D(new Object2D(glm::vec2(0.0f, 0.0f), glm::vec2(1920.0f, 1080.0f), 0.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), pauseMenuTex, shader2D.GetShaderID(), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)));
		pauseMenuOverlay.AddButton(new Button(glm::vec2(-262.5f, -262.5f), glm::vec2(-12.5f, -12.5f), 0.0f, glm::vec2(1920.0f, 1080.0f), glm::vec2(1.0f, 1.0f), redTex, shader2D.GetShaderID(), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f),
			[]()
			{
				Console::Log("Test printing from lambda");
			} // lamda expression
		));
		Overlay defaultOverlay;
		defaultOverlay.AddObject2D(new Object2D(glm::vec2(-25.0f, -25.0f), glm::vec2(25.0f, 25.0f), 0.0f, glm::vec2(1920.0f / 2.0f, 1080.0f / 2.0f), glm::vec2(1.0f, 1.0f), tex2D, shader2D.GetShaderID(), cursorCoords.min, cursorCoords.max));
		defaultOverlay.AddObject2D(new Object2D(glm::vec2(-262.5f, -262.5f), glm::vec2(-12.5f, -12.5f), 0.0f, glm::vec2(1920.0f, 1080.0f), glm::vec2(1.0f, 1.0f), redTex, shader2D.GetShaderID(), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)));
		defaultOverlay.AddObject2D(new Object2D(glm::vec2(-275.0f, -275.0f), glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(1920.0f, 1080.0f), glm::vec2(1.0f, 1.0f), whiteTex, shader2D.GetShaderID(), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)));
		defaultOverlay.AddObject2D(new Object2D(glm::vec2(0.0f, 0.0f), glm::vec2(720.0f, 270.0f), 0.0f, glm::vec2(25.0f, 800.0f), glm::vec2(1.0f, 1.0f), whitetransparentTex, shader2D.GetShaderID(), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)));

		defaultOverlay.AddText(new Sentence(&textShader, &timesnewroman32pt, "Editor Type: ", 1.0f, glm::vec2(1500.0f, 150.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
		defaultOverlay.AddText(new Sentence(&textShader, &timesnewroman32pt, "Mode: ", 1.0f, glm::vec2(1500.0f, 100.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
		defaultOverlay.AddText(new Sentence(&textShader, &arial24pt, "Mini-Map", 1.0f, glm::vec2(1700.0f, 1000.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
		defaultOverlay.AddText(new Sentence(&textShader, &arial24pt, "Keybinds:", 1.0f, glm::vec2(337.5f, 1030.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
		defaultOverlay.AddText(new Sentence(&textShader, &arial24pt, "  C:Camera      V:Move      R:Rotate", 1.0f, glm::vec2(175.0f, 980.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
		defaultOverlay.AddText(new Sentence(&textShader, &arial24pt, "E:Scale      F:Fullscreen      T:Texture", 1.0f, glm::vec2(175.0f, 930.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
		defaultOverlay.AddText(new Sentence(&textShader, &arial24pt, "[: Change Selection Left                       K: Change Texture Left", 1.0f, glm::vec2(50.0f, 880.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
		defaultOverlay.AddText(new Sentence(&textShader, &arial24pt, "]: Change Selection Right                   L: Change Texture Right", 1.0f, glm::vec2(59.0f, 830.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

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

		GLuint leftEyeFrameBuffer;
		glGenFramebuffers(1, &leftEyeFrameBuffer);
		GLuint rightEyeFrameBuffer;
		glGenFramebuffers(1, &rightEyeFrameBuffer);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//std::chrono::milliseconds duration(2500);
		//std::this_thread::sleep_for(duration);

		EditorType currentEditorType(scene);

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
			if (fPressed) {
				glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, currentWidth, currentHeight, GLFW_DONT_CARE);
			}
			///////////////////////////////////////////////////////////////////////////
			if (isPaused) {
				editorEnabled = false;
				currentMode = Mode::cam;

				pauseMenuOverlay.Submit(&renderer);
				pauseMenuOverlay.CheckTouches(mouseXPos, mouseYPos, currentWidth, currentHeight, leftClicked);
			}
			else {
				editorEnabled = true;

				defaultOverlay.Submit(&renderer);
			}
			///////////////////////////////////////////////////////////////////////////
			if (editorEnabled) {
				///////////////////////////////////////////////////////////////////////////
				textureChangeTimer.ElapseTime(deltaTime);
				selectionChangeTimer.ElapseTime(deltaTime);
				spawnTimer.ElapseTime(deltaTime);

				if (leftControlPressed && qPressed) {
					glfwSetWindowShouldClose(window, GLFW_TRUE);
				}
				if (onePressed) {
					currentEditorType = EditorType::scene;
				}
				else if (twoPressed) {
					currentEditorType = EditorType::text;
				}
				else if (threePressed) {
					currentEditorType = EditorType::light;
				}
				if ((objectsOnScene.size() > 0 && currentEditorType == EditorType::scene) || (currentEditorType == EditorType::light)) {
					if (cPressed) {
						currentMode = Mode::cam;
					}
					else if (ePressed) {
						currentMode = Mode::scale;
					}
					else if (rPressed) {
						currentMode = Mode::rotate;
					}
					else if (vPressed) {
						currentMode = Mode::translate;
					}
					else if (tPressed) {
						currentMode = Mode::texture;
					}
					else if (oPressed) {
						currentMode = Mode::output;
					}
				}
				else {
					currentMode = Mode::cam;
				}
				///////////////////////////////////////////////////////////////////////////
				if (currentEditorType == EditorType::scene) {
					if (currentMode == Mode::scale) {
						if (wPressed) {
							objectsOnScene[selectedObject]->ScaleAdd3f(0.0f, 0.0f, -movementSpeed * deltaTime);
						}
						if (sPressed) {
							objectsOnScene[selectedObject]->ScaleAdd3f(0.0f, 0.0f, movementSpeed * deltaTime);
						}
						if (aPressed) {
							objectsOnScene[selectedObject]->ScaleAdd3f(-movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (dPressed) {
							objectsOnScene[selectedObject]->ScaleAdd3f(movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (spacePressed) {
							objectsOnScene[selectedObject]->ScaleAdd3f(0.0f, movementSpeed * deltaTime, 0.0f);
						}
						if (leftControlPressed) {
							objectsOnScene[selectedObject]->ScaleAdd3f(0.0f, -movementSpeed * deltaTime, 0.0f);
						}
					}
					else if (currentMode == Mode::translate) {
						if (wPressed) {
							objectsOnScene[selectedObject]->TranslateAdd3f(0.0f, 0.0f, -movementSpeed * deltaTime);
						}
						if (sPressed) {
							objectsOnScene[selectedObject]->TranslateAdd3f(0.0f, 0.0f, movementSpeed * deltaTime);
						}
						if (aPressed) {
							objectsOnScene[selectedObject]->TranslateAdd3f(-movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (dPressed) {
							objectsOnScene[selectedObject]->TranslateAdd3f(movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (spacePressed) {
							objectsOnScene[selectedObject]->TranslateAdd3f(0.0f, movementSpeed * deltaTime, 0.0f);
						}
						if (leftControlPressed) {
							objectsOnScene[selectedObject]->TranslateAdd3f(0.0f, -movementSpeed * deltaTime, 0.0f);
						}
					}
					else if (currentMode == Mode::cam) {
						if (wPressed) {
							camera.MoveForward(deltaTime);
						}
						if (sPressed) {
							camera.MoveBackward(deltaTime);
						}
						if (aPressed) {
							camera.StrafeLeft(deltaTime);
						}
						if (dPressed) {
							camera.StrafeRight(deltaTime);
						}
						if (spacePressed) {
							camera.MoveUp(deltaTime);
						}
						if (leftControlPressed) {
							camera.MoveDown(deltaTime);
						}
					}
					else if (currentMode == Mode::rotate) {
						if (wPressed) {
							objectsOnScene[selectedObject]->RotateAdd3f(0.0f, 0.0f, glm::degrees(-movementSpeed * deltaTime));
						}
						if (sPressed) {
							objectsOnScene[selectedObject]->RotateAdd3f(0.0f, 0.0f, glm::degrees(movementSpeed * deltaTime));
						}
						if (aPressed) {
							objectsOnScene[selectedObject]->RotateAdd3f(glm::degrees(-movementSpeed * deltaTime), 0.0f, 0.0f);
						}
						if (dPressed) {
							objectsOnScene[selectedObject]->RotateAdd3f(glm::degrees(movementSpeed * deltaTime), 0.0f, 0.0f);
						}
						if (spacePressed) {
							objectsOnScene[selectedObject]->RotateAdd3f(0.0f, glm::degrees(movementSpeed * deltaTime), 0.0f);
						}
						if (leftControlPressed) {
							objectsOnScene[selectedObject]->RotateAdd3f(0.0f, glm::degrees(-movementSpeed * deltaTime), 0.0f);
						}
					}
					else if (currentMode == Mode::texture) {
						if (kPressed) {
							if (textureChangeTimer.HasFinished()) {
								if (selectedObjectTexture > 0) {
									selectedObjectTexture--;
									textureChangeTimer.Reset(0.5f);
									textureChangeTimer.Start();
								}
							}
						}
						if (lPressed) {
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
					else if (currentMode == Mode::output) {
						if (sPressed) {
							IO::SaveToFile(objectsOnScene, "res/other/", "level.lvl");
							currentMode = Mode::cam;
						}
					}
					if (leftBracketPressed) {
						if (selectionChangeTimer.HasFinished()) {
							if (selectedObject > 0) {
								selectedObject--;
								selectedObjectTexture = Search::LinearSearchVector(textures, objectsOnScene[selectedObject]->GetTextureID());
								selectionChangeTimer.Reset(0.5f);
								selectionChangeTimer.Start();
							}
						}
					}
					if (rightBracketPressed) {
						if (selectionChangeTimer.HasFinished()) {
							if (selectedObject < objectsOnScene.size() - 1) {
								selectedObject++;
								selectedObjectTexture = Search::LinearSearchVector(textures, objectsOnScene[selectedObject]->GetTextureID());
								selectionChangeTimer.Reset(0.5f);
								selectionChangeTimer.Start();
							}
						}
					}
					if (nPressed) {
						if (spawnTimer.HasFinished()) {
							objectsOnScene.push_back(new AABBCollidable(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), type::cubeModel, "", "", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), sphereCowTex, shader.GetShaderID(), Material(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), true, true));
							selectedObject = objectsOnScene.size() - 1;
							selectedObjectTexture = 0;
							spawnTimer.Reset(0.5f);
							spawnTimer.Start();
						}
					}
					if (backspacePressed) {
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
				else if (currentEditorType == EditorType::light) {
					if (currentMode == Mode::scale) {
						if (wPressed) {
							light->ScaleAdd3f(0.0f, 0.0f, -movementSpeed * deltaTime);
						}
						if (sPressed) {
							light->ScaleAdd3f(0.0f, 0.0f, movementSpeed * deltaTime);
						}
						if (aPressed) {
							light->ScaleAdd3f(-movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (dPressed) {
							light->ScaleAdd3f(movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (spacePressed) {
							light->ScaleAdd3f(0.0f, movementSpeed * deltaTime, 0.0f);
						}
						if (leftControlPressed) {
							light->ScaleAdd3f(0.0f, -movementSpeed * deltaTime, 0.0f);
						}
					}
					else if (currentMode == Mode::translate) {
						if (wPressed) {
							light->TranslateAdd3f(0.0f, 0.0f, -movementSpeed * deltaTime);
						}
						if (sPressed) {
							light->TranslateAdd3f(0.0f, 0.0f, movementSpeed * deltaTime);
						}
						if (aPressed) {
							light->TranslateAdd3f(-movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (dPressed) {
							light->TranslateAdd3f(movementSpeed * deltaTime, 0.0f, 0.0f);
						}
						if (spacePressed) {
							light->TranslateAdd3f(0.0f, movementSpeed * deltaTime, 0.0f);
						}
						if (leftControlPressed) {
							light->TranslateAdd3f(0.0f, -movementSpeed * deltaTime, 0.0f);
						}
					}
					else if (currentMode == Mode::cam) {
						if (wPressed) {
							camera.MoveForward(deltaTime);
						}
						if (sPressed) {
							camera.MoveBackward(deltaTime);
						}
						if (aPressed) {
							camera.StrafeLeft(deltaTime);
						}
						if (dPressed) {
							camera.StrafeRight(deltaTime);
						}
						if (spacePressed) {
							camera.MoveUp(deltaTime);
						}
						if (leftControlPressed) {
							camera.MoveDown(deltaTime);
						}
					}
					else if (currentMode == Mode::rotate) {
						if (wPressed) {
							light->RotateAdd3f(0.0f, 0.0f, glm::degrees(-movementSpeed * deltaTime));
						}
						if (sPressed) {
							light->RotateAdd3f(0.0f, 0.0f, glm::degrees(movementSpeed * deltaTime));
						}
						if (aPressed) {
							light->RotateAdd3f(glm::degrees(-movementSpeed * deltaTime), 0.0f, 0.0f);
						}
						if (dPressed) {
							light->RotateAdd3f(glm::degrees(movementSpeed * deltaTime), 0.0f, 0.0f);
						}
						if (spacePressed) {
							light->RotateAdd3f(0.0f, glm::degrees(movementSpeed * deltaTime), 0.0f);
						}
						if (leftControlPressed) {
							light->RotateAdd3f(0.0f, glm::degrees(-movementSpeed * deltaTime), 0.0f);
						}
					}
				}
				///////////////////////////////////////////////////////////////////////////
				if (currentMode == Mode::cam) {
					defaultOverlay.SetText(0, "Mode: Camera");
				}
				else if (currentMode == Mode::output) {
					defaultOverlay.SetText(0, "Mode: Output");
				}
				else if (currentMode == Mode::rotate) {
					defaultOverlay.SetText(0, "Mode: Rotate");
				}
				else if (currentMode == Mode::scale) {
					defaultOverlay.SetText(0, "Mode: Scale");
				}
				else if (currentMode == Mode::texture) {
					defaultOverlay.SetText(0, "Mode: Texture");
				}
				else if (currentMode == Mode::translate) {
					defaultOverlay.SetText(0, "Mode: Translate");
				}
				if (currentEditorType == EditorType::overlay) {
					defaultOverlay.SetText(1, "Editor Type: Overlay");
				}
				else if (currentEditorType == EditorType::scene) {
					defaultOverlay.SetText(1, "Editor Type: Scene");
				}
				else if (currentEditorType == EditorType::text) {
					defaultOverlay.SetText(1, "Editor Type: Text");
				}
				else if (currentEditorType == EditorType::light) {
					defaultOverlay.SetText(1, "Editor Type: Light");
				}
				///////////////////////////////////////////////////////////////////////////
			}
			///////////////////////////////////////////////////////////////////////////
			camera.ChangeMovementSpeed(movementSpeed);
			camPos = camera.GetTranslation();
			camera.BringWith(preloadedObjectsOnScene[0]);
			///////////////////////////////////////////////////////////////////////////
			glm::mat4 viewMatrix = camera.GetViewTransformMatrix();
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
			renderer.SimpleFlush(&camera, currentWidth, currentHeight, FOV, light);
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
		config.WriteConfig("res/other/", "config.cfg");
		Mesh::CleanUpCache();
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}
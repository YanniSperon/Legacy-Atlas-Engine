#include "GlobalVariables.h"

namespace Atlas {

	GlobalVariables::GlobalVariables()
	{
		systemStartTime = std::chrono::high_resolution_clock::now();
		config = Config("res/other/", "config.cfg");

		mouseX = 0.0;
		mouseY = 0.0;
		movementSpeed = 10.0f;
		originalMovementSpeed = movementSpeed;
		isPaused = false;

		fullscreen = config.GetFullscreenPreference();
		forceFullscreen = config.GetForceFullscreen();
		mouseSensitivity = config.GetMouseSensitivityPreference();
		FOV = config.GetFOVPreference();
		initialWidth = config.GetInitialWidthPreference();
		initialHeight = config.GetInitialHeightPreference();
		hasVR = config.GetVRPreference();
		VSyncPreference = config.GetVSyncPreference();
		mouseMode = config.GetMouseMode();

		activeCamera = new Camera(true, movementSpeed, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), mouseSensitivity, NULL);

		currentWidth = initialWidth;
		currentHeight = initialHeight;

		keyIn = KeyboardInput();
		mouseIn = MouseInput();

		enableMouseClick = true;
		enableMouseMove = true;
		enableKeyboard = true;

		consoleLog = std::vector<std::string>();
		commandMap = std::unordered_map<std::string, std::function<void(std::vector<std::string>&)>>();

		for (int i = 0; i < 10; i++) {
			consoleLog.push_back("");
		}

		meshCache = std::unordered_map<std::string, ShapeData>();
		
		shaderCache = std::unordered_map<std::string, Shader*>();

		textureCache = std::unordered_map<std::string, GLuint>();

		loadedMeshCache = std::unordered_map<std::string, std::string>();
		
		loadedTextureCache = std::unordered_map<std::string, std::string>();
		
		loadedShaderCache = std::unordered_map<std::string, std::string>();

		loadedPostProcessingShaderCache = std::unordered_map<std::string, std::string>();

		currentScene = Scene();
		currentScene.camerasOnScene.push_back(activeCamera);

		window = NULL;

		currentRenderer = NULL;
	}
}
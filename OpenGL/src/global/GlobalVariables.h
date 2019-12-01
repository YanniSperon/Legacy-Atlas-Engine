#pragma once

#include "Config.h"
#include "Camera.h"
#include "Input.h"
#include "Shader.h"
#include "Scene.h"
#include <chrono>
#include <unordered_map>
#include <vector>

namespace Atlas {

	class GlobalVariables {
	public:
		GlobalVariables();
		
		std::vector<std::string> consoleLog;

		std::chrono::steady_clock::time_point systemStartTime;

		Config config;

		double mouseX;
		double mouseY;

		float movementSpeed;
		bool isPaused;

		bool fullscreen;
		bool forceFullscreen;
		float mouseSensitivity;
		float FOV;
		int initialWidth;
		int initialHeight;
		bool hasVR;
		bool VSyncPreference;
		MouseMode mouseMode;

		Camera camera;

		int currentWidth;
		int currentHeight;

		KeyboardInput keyIn;
		MouseInput mouseIn;
		
		bool enableMouseClick;
		bool enableMouseMove;
		bool enableKeyboard;
		
		std::unordered_map<std::string, ShapeData> meshCache;

		std::unordered_map<std::string, Shader*> shaderCache;
	
		std::unordered_map<std::string, GLuint> textureCache;

		Scene currentScene;
	};

}
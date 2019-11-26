#pragma once

#include "Config.h"
#include "Camera.h"
#include "Input.h"
#include <chrono>
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
	};

}
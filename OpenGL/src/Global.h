#pragma once

#include "Config.h"
#include "Camera.h"
#include "Input.h"

namespace Engine {
	namespace Global {
		//class Global {
		//public:
			static Config config;

			static double mouseX;
			static double mouseY;

			static float movementSpeed;
			static bool isPaused;

			static bool fullscreen;
			static bool forceFullscreen;
			static float mouseSensitivity;
			static float FOV;
			static int initialWidth;
			static int initialHeight;
			static bool hasVR;
			static bool VSyncPreference;
			static MouseMode mouseMode;

			static Camera camera;

			static int currentWidth;
			static int currentHeight;

			static KeyboardInput keyIn;
			static MouseInput mouseIn;

			static void Initialize();
		//};
	}
}
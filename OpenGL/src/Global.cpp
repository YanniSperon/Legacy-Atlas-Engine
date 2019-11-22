#include "Global.h"



namespace Engine {

	void Global::Initialize()
	{
		config = Config("res/other/", "config.cfg");

		mouseX = 0.0;
		mouseY = 0.0;
		movementSpeed = 10.0f;
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

		camera = Camera(true, movementSpeed, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), mouseSensitivity);

		currentWidth = initialWidth;
		currentHeight = initialHeight;

		keyIn = KeyboardInput();
		mouseIn = MouseInput();
	}
}
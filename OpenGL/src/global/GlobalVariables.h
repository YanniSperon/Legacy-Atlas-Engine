#pragma once

#include "Config.h"
#include "Camera.h"
#include "Input.h"
#include "Shader.h"
#include "Scene.h"
#include "Object2D.h"
#include <chrono>
#include <unordered_map>
#include <vector>
#include "PhysicsEngine.h"

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
		float originalMovementSpeed;
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

		std::unordered_map<std::string, std::string> loadedMeshCache;

		std::unordered_map<std::string, std::string> loadedTextureCache;

		std::unordered_map<std::string, std::string> loadedShaderCache;

		std::unordered_map<std::string, std::string> loadedPostProcessingShaderCache;

		Scene currentScene;
	};

}
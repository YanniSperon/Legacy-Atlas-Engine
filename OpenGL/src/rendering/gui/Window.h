#pragma once
#include "Object.h"
#include "LevelEditor.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <vector>

struct GLFWwindow;

namespace Atlas {

	class Window {
	public:
		static void DrawUI(GLFWwindow* window, bool& EnableWireframe);
		static void DrawControl(GLFWwindow* window, bool& isMovingCamera);
		static void DrawFPSCounter();
		static void DrawSceneViewer();
		static void DrawPostProcessingManager(GLFWwindow* window);
		static void DrawObjectSettingsWindow();
	};
}
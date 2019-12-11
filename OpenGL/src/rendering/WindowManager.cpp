#include "WindowManager.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "PostProcessor.h"
#include "System.h"
#include "Global.h"
#include "Callbacks.h"

namespace Atlas {
	bool Atlas::WindowManager::Initialize()
	{
		if (!glfwInit()) {
			System::Err("Error initializing GLFW!");
			return false;
		}

		if (Global::Variables.fullscreen) {
			Global::Variables.window = glfwCreateWindow(Global::Variables.initialWidth, Global::Variables.initialHeight, "Atlas", glfwGetPrimaryMonitor(), NULL);
		}
		else {
			if (Global::Variables.forceFullscreen) {
				const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
				if (mode->width == Global::Variables.currentWidth && mode->height == Global::Variables.currentHeight) {
					Global::Variables.window = glfwCreateWindow(Global::Variables.initialWidth, Global::Variables.initialHeight, "Atlas", glfwGetPrimaryMonitor(), NULL);
				}
				else {
					//glfwWindowHint(GLFW_DECORATED, false);
					Global::Variables.window = glfwCreateWindow(Global::Variables.initialWidth, Global::Variables.initialHeight, "Atlas", NULL, NULL);
				}
			}
			else {
				//glfwWindowHint(GLFW_DECORATED, false);
				Global::Variables.window = glfwCreateWindow(Global::Variables.initialWidth, Global::Variables.initialHeight, "Atlas", NULL, NULL);
			}
		}

		if (!Global::Variables.window)
		{
			System::Err("Error initializing GLFW!");
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(Global::Variables.window);

		//glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);

		glfwSwapInterval(Global::Variables.VSyncPreference);
		
		if (glewInit() != GLEW_OK) {
			System::Err("Error initializing GLEW (OpenGL)");
			return false;
		}

		glfwSetInputMode(Global::Variables.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if (Global::Variables.mouseMode == MouseMode::raw) {
			if (glfwRawMouseMotionSupported()) {
				glfwSetInputMode(Global::Variables.window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
			}
		}
		glfwSetCursorPosCallback(Global::Variables.window, Callbacks::cursorPositionCallback);
		glfwSetFramebufferSizeCallback(Global::Variables.window, Callbacks::framebufferSizeCallback);
		glfwSetErrorCallback(Callbacks::errorCallback);
		
		return true;
	}
}
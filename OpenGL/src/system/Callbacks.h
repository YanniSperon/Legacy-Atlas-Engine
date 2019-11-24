#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Global.h"

namespace Engine {

	class Callbacks {
	public:
		static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
		{
			Global::Variables.mouseX = xpos;
			Global::Variables.mouseY = ypos;
			if (ypos * Global::Variables.mouseSensitivity > 89.0f) {
				double newMouseY = 89.0f / Global::Variables.mouseSensitivity;
				glfwSetCursorPos(window, xpos, newMouseY);
				Global::Variables.camera.LookAt(xpos, newMouseY);
			}
			else if (ypos * Global::Variables.mouseSensitivity < -89.0f) {
				double newMouseY = -89.0f / Global::Variables.mouseSensitivity;
				glfwSetCursorPos(window, xpos, newMouseY);
				Global::Variables.camera.LookAt(xpos, newMouseY);
			}
			else {
				Global::Variables.camera.LookAt(xpos, ypos);
			}
		}

		static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
		{
			Global::Variables.currentWidth = width;
			Global::Variables.currentHeight = height;
			if (width > 0 && height > 0) {
				glViewport(0, 0, width, height);
			}
		}
	};
}
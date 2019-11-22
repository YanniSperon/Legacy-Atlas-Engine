#pragma once

#include "GLFW/glfw3.h"
#include "Global.h"

namespace Engine {

	class Callbacks {
	public:
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			InputHandler::KeyCallback(&Global::keyIn, window, key, scancode, action, mods);
		}

		static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
		{
			Global::mouseX = xpos;
			Global::mouseY = ypos;
			if (ypos * Global::mouseSensitivity > 89.0f) {
				double newMouseY = 89.0f / Global::mouseSensitivity;
				glfwSetCursorPos(window, xpos, newMouseY);
				Global::camera.LookAt(xpos, newMouseY);
			}
			else if (ypos * Global::mouseSensitivity < -89.0f) {
				double newMouseY = -89.0f / Global::mouseSensitivity;
				glfwSetCursorPos(window, xpos, newMouseY);
				Global::camera.LookAt(xpos, newMouseY);
			}
			else {
				Global::camera.LookAt(xpos, ypos);
			}
		}

		static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
		{
			Global::currentWidth = width;
			Global::currentHeight = height;
			if (width > 0 && height > 0) {
				glViewport(0, 0, width, height);
			}
		}

		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
		{
			if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
				Global::mouseIn.leftClicked = true;
			}
			else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
				Global::mouseIn.leftClicked = false;
			}

			if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
				Global::mouseIn.rightClicked = true;
			}
			else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
				Global::mouseIn.rightClicked = false;
			}
		}
	};
}
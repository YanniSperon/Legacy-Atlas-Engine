#pragma once
#include <Input.h>
#include <GLFW/glfw3.h>

class InputHandler {
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		mouseXPos = xpos;
		mouseYPos = ypos;
		if (!isPaused) {
			if (ypos * mouseSensitivity > 89.0f) {
				double newMouseY = 89.0f / mouseSensitivity;
				glfwSetCursorPos(window, xpos, newMouseY);
				camera.LookAt(xpos, newMouseY);
			}
			else if (ypos * mouseSensitivity < -89.0f) {
				double newMouseY = -89.0f / mouseSensitivity;
				glfwSetCursorPos(window, xpos, newMouseY);
				camera.LookAt(xpos, newMouseY);
			}
			else {
				camera.LookAt(xpos, ypos);
			}
		}
	}
};
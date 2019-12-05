#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Global.h"

namespace Atlas {

	class Callbacks {
	public:
		static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
		{
			if (Global::Variables.enableMouseMove) {
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
		}

		static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
		{
			Global::Variables.currentWidth = width;
			Global::Variables.currentHeight = height;
			if (width > 0 && height > 0) {
				glViewport(0, 0, width, height);
			}
		}

		static void errorCallback(int error, const char* description)
		{
			std::cerr << "Error " << error << " : " << description << std::endl;
		}

		static void APIENTRY openglCallbackFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
			if (severity != GL_DEBUG_SEVERITY_LOW) {
				(void)source; (void)type; (void)id;
				(void)severity; (void)length; (void)userParam;
				System::Err("GLError: \"" + std::string((const char*)message));
				if (severity == GL_DEBUG_SEVERITY_HIGH) {
					System::Err("    FATAL GLERROR!");
					abort();
				}
			}
		}
	};
}
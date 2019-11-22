#pragma once
#include <Input.h>
#include <GLFW/glfw3.h>
namespace Engine {
	class InputHandler {
	public:
		static void KeyCallback(KeyboardInput* input, GLFWwindow* window, int key, int scancode, int action, int mods);

		static void Flush(KeyboardInput keyIn, MouseInput mouseIn);
	};
}
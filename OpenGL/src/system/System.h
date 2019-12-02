#pragma once
#include <string>
#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

namespace Atlas {
	class System {
	public:
		static bool DoesFileExist(const std::string& filePath);
		static bool HasValidFileAttributes(const std::string& filePath);
		static bool CopyFileAtlas(const std::string& originalFilePathAndName, const std::string& finalFilePath);

		static void Log(std::string text);
		static void Warn(std::string text);
		static void Err(std::string text);

		static void SendConsoleCommand(std::string command);

		static void DrawConsole();

		static std::string FileOpenDialog(std::string label, LPCSTR filter, GLFWwindow* window);
	};
};
#pragma once
#include <string>
#include <vector>
#include <functional>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

namespace Atlas {
	struct Filepath {
		std::string directory;
		std::string filename;

		Filepath()
			: directory(""), filename("")
		{

		}

		Filepath(std::string dir, std::string name)
			: directory(dir), filename(name)
		{

		}
	};

	class System {
	public:
		static std::vector<std::string> GetFilesInDirectory(const std::string& directory);

		static std::string GetEXEDirectory();
		static std::string GetEXEName();
		static void SetWorkingDirectory();
		static std::string GetWorkingDirectory();
		static bool IsFilePathInWorkingDirectory(const std::string& filePath);
		static bool IsFilePathInEXEDirectory(const std::string& filePath);

		static std::string ConvertFilePathToAbsolute(const std::string& localFilePath);
		static std::string ConvertFilePathToLocal(const std::string& absoluteFilePath);
		
		static bool DoesFileExist(const std::string& filePath);
		static bool HasValidFileAttributes(const std::string& filePath);
		static bool CopyFileAtlas(const std::string& originalFilePathAndName, const std::string& finalFilePath);


		static void Log(const std::string& text);
		static void Warn(const std::string& text);
		static void Err(const std::string& text);

		static void DispatchCommand(std::string& command, std::vector<std::string>& args);
		static void RegisterCommand(std::string& command, std::function<void(std::vector<std::string>&)> func);

		static void SendConsoleInput(const std::string& input);
		static void SetConsoleLogFile(const std::string& logFile);


		static void DrawConsole(float offset);

		static std::string FileOpenDialog(const std::string& label, LPCSTR filter, GLFWwindow* window);

		static Filepath SeperateFilepath(const std::string& filePath);

		static void AddEventToGlobalQueue(std::function<void()> func);
		static void AddPriorityEventToGlobalQueue(std::function<void()> func);

		static void ProcessGlobalEvents();
	};
};
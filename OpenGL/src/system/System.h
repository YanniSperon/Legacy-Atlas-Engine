#pragma once
#include <string>
#include <vector>

namespace Atlas {
	class System {
	public:
		static void Log(std::string text);
		static void Warn(std::string text);
		static void Err(std::string text);

		static void SendConsoleCommand(std::string command);

		static void DrawConsole();
	};
};
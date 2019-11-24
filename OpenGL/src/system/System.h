#pragma once
#include <string>

namespace Engine {
	class System {
	public:
		static void Log(std::string text);
		static void Warn(std::string text);
		static void Err(std::string text);
	};
};
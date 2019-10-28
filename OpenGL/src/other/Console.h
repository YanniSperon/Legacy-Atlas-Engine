#pragma once
#include <string>

class Console {
public:
	static void Setup();

	static void Log(std::string text);
	static void Warn(std::string text);
	static void Err(std::string text);
};
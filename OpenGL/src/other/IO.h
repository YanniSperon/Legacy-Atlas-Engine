#pragma once
#include <vector>
#include <string>
#include "Object.h"
class IO {
public:
	static void LoadFile(std::vector<Object>& vec, const std::string dir, const std::string fileName);
	static void SaveToFile(std::vector<Object> &vec, const std::string dir, const std::string fileName);
};
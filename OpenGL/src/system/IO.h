#pragma once

#include <vector>
#include <string>
#include "Object.h"
#include "Object2D.h"
#include "Sentence.h"

namespace Engine {

	class IO {
	public:
		static void LoadFile(std::vector<Object*>& vec, const std::string dir, const std::string fileName);
		static void SaveToFile(std::vector<Object*>& vec, const std::string dir, const std::string fileName);

		static void LoadFile(std::vector<Object2D*>& vec, const std::string dir, const std::string fileName);
		static void SaveToFile(std::vector<Object2D*>& vec, const std::string dir, const std::string fileName);

		static void LoadFile(std::vector<Sentence*>& vec, const std::string dir, const std::string fileName);
		static void SaveToFile(std::vector<Sentence*>& vec, const std::string dir, const std::string fileName);
	};
}
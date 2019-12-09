#pragma once

#include "ShapeData.h"
#include <string>

namespace Atlas {

	class ShapeGenerator {
	public:
		static ShapeData makeTriangle(const glm::vec3& min, const glm::vec3& max);
		static ShapeData makeCube(const glm::vec3& min, const glm::vec3& max);
		static ShapeData makeInvertedLightingCube(const glm::vec3& min, const glm::vec3& max);
		static ShapeData makeSkybox(const glm::vec3& min, const glm::vec3& max);
		static ShapeData loadShape(const std::string& fileName);
		static ShapeData loadTexturedShape(const std::string& directory, const std::string& name);

		static ShapeData2D makeSquare(const glm::vec2& min, const glm::vec2& max, const glm::vec2& minTexCoords, const glm::vec2& maxTexCoords);
	};
}
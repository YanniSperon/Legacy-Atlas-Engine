#pragma once
#include "ShapeData.h"
#include <string>
class ShapeGenerator {
public:
	static ShapeData makeTriangle(glm::vec3& min, glm::vec3& max);
	static ShapeData makeCube(glm::vec3& min, glm::vec3& max);
	static ShapeData makeInvertedLightingCube(glm::vec3& min, glm::vec3& max);
	static ShapeData makeSkybox(glm::vec3& min, glm::vec3& max);
	static ShapeData loadShape(std::string fileName, glm::vec3& min, glm::vec3& max);
	static ShapeData loadTexturedShape(std::string directory, std::string name, glm::vec3& min, glm::vec3& max);
	static ShapeData2D makeSquare(glm::vec2& min, glm::vec2& max, glm::vec2& minTexCoords, glm::vec2& maxTexCoords);
};
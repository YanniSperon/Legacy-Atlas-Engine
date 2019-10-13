#pragma once
#include "GL/glew.h"
#include "glm/glm.hpp"
#include <string>

struct TexCoords {
	glm::vec2 min;
	glm::vec2 max;
};

class Loader {
public:
	static GLuint LoadTexture(const std::string texDir, const std::string texName, GLint textureWrapS, GLint textureWrapT, GLint textureMinFilter, GLint textureMaxFilter);
	static TexCoords GetTextureCoordinates(GLuint minX, GLuint minY, GLuint maxX, GLuint maxY, GLuint width, GLuint height);
};
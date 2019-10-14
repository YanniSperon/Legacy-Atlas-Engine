#pragma once
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "Shader.h"
#include <map>

struct Character {
	GLuint     TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};

class Font {
private:
	std::map<GLchar, Character> Characters;
	GLuint VAO;
	GLuint VBO;
public:
	Font();
	Font(std::string fontDirectory, std::string fontName, GLuint characterSize);

	void RenderText(Shader& s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, glm::mat4 projection);
};
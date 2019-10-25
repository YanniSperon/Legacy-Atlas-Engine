#pragma once
#include <vector>
#include <string>
#include "glm/glm.hpp"
#include "GL/glew.h"
#include "Font.h"

struct CharInSentence {
	GLuint textureID;
	GLuint VBO;
	CharInSentence()
		: textureID(0), VBO(0)
	{}
	CharInSentence(GLuint tex, GLuint vertexBufferID)
		: textureID(tex), VBO(vertexBufferID)
	{}
};

class Text {
private:
	std::vector<CharInSentence> text;
public:
	Text();
	Text(Font* font, std::string text, float x, float y, float scale, glm::vec3 color);
};
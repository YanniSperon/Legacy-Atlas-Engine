#pragma once
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

class Sentence {
private:
	//Shader& shader;


	GLuint shaderID;
	Font& font;
	std::string text;
	float scale;
	glm::vec2 position;
	glm::vec3 color;
	std::vector<CharInSentence> VBOs;
public:
	//Sentence(Shader& shdr, Font& f, std::string t, float s, glm::vec2 pos, glm::vec3 col);
	Sentence(Font& f, std::string t, float s, glm::vec2 pos, glm::vec3 col, GLuint shader);
	~Sentence();

	//Shader& GetShader();
	//void SetShader(Shader& shdr);

	Font& GetFont();
	void SetFont(Font& f);

	std::string GetText();
	void SetText(std::string newText);

	float GetScale();
	void SetScale(float s);

	glm::vec2 GetPosition();
	void SetPosition(glm::vec2 newPos);

	glm::vec3 GetColor();
	void SetColor(glm::vec3 newColor);

	glm::mat4 GetModelTransformMatrix();

	void GenerateVBOs(std::string text);

	void DeleteVBOs();

	void Draw(glm::mat4 proj);
};
#pragma once
#include "Font.h"

class Sentence {
private:
	Shader& shader;
	Font& font;
	std::string text;
	float scale;
	glm::vec2 position;
	glm::vec3 color;
public:
	Sentence(Shader& shdr, Font& f, std::string t, float s, glm::vec2 pos, glm::vec3 col);
	~Sentence();

	Shader& GetShader();
	void SetShader(Shader& shdr);

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
};
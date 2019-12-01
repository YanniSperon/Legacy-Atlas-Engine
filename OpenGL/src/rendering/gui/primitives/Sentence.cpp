#include "Sentence.h"
#include "System.h"

namespace Atlas {
	Sentence::Sentence()
		: shader(new Shader()), font(new Font()), scale(0.0f)
	{
	}

	Sentence::Sentence(Shader* shdr, Font* f, std::string t, float s, glm::vec2 pos, glm::vec3 col)
		: shader(shdr), font(f), text(t), scale(s), position(pos), color(col)
	{

	}

	Sentence::~Sentence()
	{

	}

	Shader* Sentence::GetShader()
	{
		return shader;
	}

	void Sentence::SetShader(Shader* shdr)
	{
		shader = shdr;
	}

	Font* Sentence::GetFont()
	{
		return font;
	}

	void Sentence::SetFont(Font* f)
	{
		font = f;
	}

	std::string Sentence::GetText()
	{
		return text;
	}

	void Sentence::SetText(std::string newText)
	{
		text = newText;
	}

	float Sentence::GetScale()
	{
		return scale;
	}

	void Sentence::SetScale(float s)
	{
		scale = s;
	}

	glm::vec2 Sentence::GetPosition()
	{
		return position;
	}

	void Sentence::SetPosition(glm::vec2 newPos)
	{
		position = newPos;
	}

	glm::vec3 Sentence::GetColor()
	{
		return color;
	}

	void Sentence::SetColor(glm::vec3 newColor)
	{
		color = newColor;
	}
}
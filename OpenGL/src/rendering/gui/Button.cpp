#include "Button.h"

Button::Button()
	: Object2D()
{

}

Button::Button(glm::vec2 minCorner, glm::vec2 maxCorner, float rot, glm::vec2 trans, glm::vec2 s, GLuint tex, GLuint shader, glm::vec2 minTexCoord, glm::vec2 maxTexCoord, std::function<void()> function)
	: Object2D(minCorner, maxCorner, rot, trans, s, tex, shader, minTexCoord, maxTexCoord)
{
	func = function;
}

Button::~Button()
{
}

bool Button::IsPressed(double mouseX, double mouseY, int width, int height)
{
	glm::vec2 translation = GetTranslation();
	glm::vec2 min = GetMinExtents() + translation;
	glm::vec2 max = GetMaxExtents() + translation;
	if (mouseX > min.x && mouseX < max.x && mouseY < ((double)height) - min.y && mouseY > ((double)height) - max.y) {
		return true;
	}
	return false;
}

void Button::Callback()
{
	func();
}

void Button::CheckPress(double mouseX, double mouseY, int width, int height)
{
	if (IsPressed(mouseX, mouseY, width, height)) {
		Callback();
	}
}

#pragma once
#include <functional>
#include "Object2D.h"

class Button : public Object2D {
private:
	std::function<void()> func;
public:
	Button();
	Button(glm::vec2 minCorner, glm::vec2 maxCorner, float rot, glm::vec2 trans, glm::vec2 s, GLuint tex, GLuint shader, glm::vec2 minTexCoord, glm::vec2 maxTexCoord, std::function<void ()> function);
	~Button();

	bool IsPressed(double mouseX, double mouseY, int width, int height);
	
	void Callback();

	void CheckPress(double mouseX, double mouseY, int width, int height);
};
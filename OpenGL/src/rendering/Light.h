#pragma once
#include "Object.h"

class Light : public Object {
private:
	glm::vec3 lightColor;
public:
	Light(glm::vec3 lColor, glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, GLuint tex, GLuint shader);

	void SetLightColor(glm::vec3 newValue);
	glm::vec3 GetLightColor();
};
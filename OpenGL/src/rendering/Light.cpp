#include "Light.h"

Light::Light(glm::vec3 lColor, glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, GLuint tex, GLuint shader)
	: Object(minCorner, maxCorner, type, dir, name, rot, trans, s, tex, shader), lightColor(lColor)
{

}

void Light::SetLightColor(glm::vec3 newValue)
{
	lightColor = newValue;
}

glm::vec3 Light::GetLightColor()
{
	return lightColor;
}
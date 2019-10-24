#include "Light.h"

Light::Light(LightIntensity lightIntensity, glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, GLuint tex, GLuint shader, bool glInit, bool lighting)
	: Object(minCorner, maxCorner, type, dir, name, rot, trans, s, tex, shader, glInit, lighting), intensity(lightIntensity)
{

}

Light::Light(LightIntensity lightIntensity, glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, GLuint tex, GLuint shader, Material mat, bool glInit, bool lighting)
	: Object(minCorner, maxCorner, type, dir, name, rot, trans, s, tex, shader, mat, glInit, lighting), intensity(lightIntensity)
{

}

void Light::SetLightIntensity(LightIntensity newValue)
{
	intensity = newValue;
}

LightIntensity Light::GetLightIntensity()
{
	return intensity;
}

std::string Light::GetType()
{
	return "Light";
}

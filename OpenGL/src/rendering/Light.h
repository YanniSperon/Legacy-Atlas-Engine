#pragma once
#include "Object.h"

struct LightIntensity {
	glm::vec3 ambient, diffuse, specular;

	LightIntensity()
		: ambient(1.0f, 1.0f, 1.0f), diffuse(1.0f, 1.0f, 1.0f), specular(1.0f, 1.0f, 1.0f)
	{
	}

	LightIntensity(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec)
		: ambient(amb), diffuse(diff), specular(spec)
	{
	}
};

class Light : public Object {
private:
	LightIntensity intensity;
public:
	Light(LightIntensity lightIntensity, glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, GLuint tex, GLuint shader, bool glInit);
	Light(LightIntensity lightIntensity, glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, GLuint tex, GLuint shader, Material mat, bool glInit);

	void SetLightIntensity(LightIntensity newValue);
	LightIntensity GetLightIntensity();

	virtual std::string GetType() override;
};
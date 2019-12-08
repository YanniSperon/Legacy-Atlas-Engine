#include "Light.h"

namespace Atlas {
	Light::Light()
		: Object(), intensity()
	{
	}
	Light::Light(LightIntensity lightIntensity, glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderName, bool glInit, bool hasLighting, bool hasPhysics, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, float mass)
		: Object(minCorner, maxCorner, type, meshDir, meshName, texDir, texName, shaderDir, shaderName, glInit, hasLighting, hasPhysics, rot, trans, s, mass), intensity(lightIntensity)
	{

	}

	Light::Light(LightIntensity lightIntensity, glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderName, bool glInit, bool hasLighting, bool hasPhysics, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, float mass, Material mat)
		: Object(minCorner, maxCorner, type, meshDir, meshName, texDir, texName, shaderDir, shaderName, glInit, hasLighting, hasPhysics, rot, trans, s, mass, mat), intensity(lightIntensity)
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
}
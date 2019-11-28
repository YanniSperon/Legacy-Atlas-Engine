#include "Light.h"

namespace Atlas {

	Light::Light(LightIntensity lightIntensity, glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderName, bool glInit, bool hasLighting, glm::vec3 rot, glm::vec3 trans, glm::vec3 s)
		: Object(minCorner, maxCorner, type, meshDir, meshName, texDir, texName, shaderDir, shaderName, glInit, hasLighting, rot, trans, s), intensity(lightIntensity)
	{

	}

	Light::Light(LightIntensity lightIntensity, glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderName, bool glInit, bool hasLighting, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, Material mat)
		: Object(minCorner, maxCorner, type, meshDir, meshName, texDir, texName, shaderDir, shaderName, glInit, hasLighting, rot, trans, s, mat), intensity(lightIntensity)
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
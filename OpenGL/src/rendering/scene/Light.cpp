#include "Light.h"

namespace Atlas {
	Light::Light()
		: Object(), intensity()
	{
	}
	Light::Light(LightIntensity lightIntensity, type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderName, bool glInit, bool hasLighting, unsigned long long int uid, glm::vec3 rot, glm::vec3 trans, glm::vec3 s)
		: Object(type, meshDir, meshName, texDir, texName, shaderDir, shaderName, glInit, hasLighting, uid, rot, trans, s), intensity(lightIntensity)
	{

	}

	Light::Light(LightIntensity lightIntensity, type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderName, bool glInit, bool hasLighting, unsigned long long int uid, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, Material mat)
		: Object(type, meshDir, meshName, texDir, texName, shaderDir, shaderName, glInit, hasLighting, uid, rot, trans, s, mat), intensity(lightIntensity)
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
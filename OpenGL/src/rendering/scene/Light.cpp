#include "Light.h"

namespace Atlas {
	Light::Light()
		: Object(), intensity()
	{
	}
	Light::Light(LightIntensity lightIntensity, type t, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderName, bool glInit, bool hasLighting, const UUID& uid, glm::vec3 rot, glm::vec3 trans, glm::vec3 s)
		: Object(t, meshDir, meshName, texDir, texName, shaderDir, shaderName, glInit, hasLighting, uid, rot, trans, s), intensity(lightIntensity)
	{

	}

	Light::Light(LightIntensity lightIntensity, type t, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderName, bool glInit, bool hasLighting, const UUID& uid, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, Material mat)
		: Object(t, meshDir, meshName, texDir, texName, shaderDir, shaderName, glInit, hasLighting, uid, rot, trans, s, mat), intensity(lightIntensity)
	{

	}

	Light::Light(type t, std::string meshDir, std::string meshName, Light& otherLight)
		: Object(t, meshDir, meshName, otherLight), intensity(otherLight.intensity)
	{

	}

	void Light::SetLightIntensity(LightIntensity newValue)
	{
		intensity = newValue;
	}

	LightIntensity& Light::GetLightIntensity()
	{
		return intensity;
	}

	std::string Light::GetType()
	{
		return "Light";
	}
}
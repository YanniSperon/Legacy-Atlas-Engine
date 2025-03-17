#pragma once

#include "UUID.h"
#include "Object.h"

namespace Atlas {

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
		Light();
		Light(LightIntensity lightIntensity, type t, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderName, bool glInit, bool hasLighting, const UUID& uid, glm::vec3 rot, glm::vec3 trans, glm::vec3 s);
		Light(LightIntensity lightIntensity, type t, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderName, bool glInit, bool hasLighting, const UUID& uid, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, Material mat);
		Light(type t, std::string meshDir, std::string meshName, Light& otherLight);

		void SetLightIntensity(LightIntensity newValue);
		LightIntensity& GetLightIntensity();

		virtual std::string GetType() override;
	};
}
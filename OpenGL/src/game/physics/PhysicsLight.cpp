#include "PhysicsLight.h"

namespace Atlas {

	PhysicsLight::PhysicsLight()
	{

	}

	PhysicsLight::PhysicsLight(Light* light)
		: PhysicsObject(light, 0.0f)
	{
		intensity = light->GetLightIntensity();
	}

	PhysicsLight::~PhysicsLight()
	{
		
	}

	void PhysicsLight::SetLightIntensity(LightIntensity newValue)
	{
		intensity = newValue;
	}

	LightIntensity PhysicsLight::GetLightIntensity()
	{
		return intensity;
	}
}
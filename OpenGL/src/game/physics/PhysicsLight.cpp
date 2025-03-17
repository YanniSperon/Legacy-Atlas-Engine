#include "PhysicsLight.h"

namespace Atlas {

	PhysicsLight::PhysicsLight()
	{

	}

	PhysicsLight::PhysicsLight(Light* light, float mass, PhysicsObject::typeShape t)
		: PhysicsObject(light, 0.0f, t)
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
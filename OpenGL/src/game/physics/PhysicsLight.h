#pragma once
#include "PhysicsObject.h"
#include "Light.h"

namespace Atlas {

	class PhysicsLight : public PhysicsObject {
	private:
		LightIntensity intensity;
	public:
		PhysicsLight();
		PhysicsLight(Light* light, float mass, PhysicsObject::typeShape t);
		~PhysicsLight();

		void SetLightIntensity(LightIntensity newValue);
		LightIntensity GetLightIntensity();
	};
}
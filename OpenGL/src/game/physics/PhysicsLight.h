#pragma once
#include "PhysicsObject.h"
#include "Light.h"

namespace Atlas {

	class PhysicsLight : public PhysicsObject {
	public:
		PhysicsLight();
		PhysicsLight(Light* light);
		~PhysicsLight();
	};
}
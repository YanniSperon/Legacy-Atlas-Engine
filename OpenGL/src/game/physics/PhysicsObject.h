#pragma once
#include "Object.h"

namespace Atlas {
	
	class PhysicsObject : public Object {
	private:

	public:
		PhysicsObject();
		~PhysicsObject();

		void Update();
	};
}
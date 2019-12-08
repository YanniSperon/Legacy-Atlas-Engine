#pragma once

#include "btBulletDynamicsCommon.h"

namespace Atlas {
	class PhysicsEngine {
	public:
		static void Initialize();
		static void Update(float deltaT);
		static btCollisionObject* AddRigidBody(btCollisionShape* shape, btTransform& transformation, float mass);
		static void Cleanup();
	};
}
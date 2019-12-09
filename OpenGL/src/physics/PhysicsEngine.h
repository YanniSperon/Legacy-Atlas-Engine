#pragma once

#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionShapes/btTriangleMesh.h"
#include "PhysicsDebugDrawer.h"
#include "ShapeData.h"

namespace Atlas {
	class PhysicsEngine {
	public:
		static void Initialize();
		static void Update(float deltaT);
		static btCollisionObject* AddPhysicsBody(btCollisionShape* shape, btTransform& transformation, float mass);
		static void Recalculate(btCollisionObject* object);
		static void DrawDebug();
		static void Cleanup();
		static void ToggleDebugger();
		static void RemovePhysicsBody(btCollisionObject* object);
		static void SetGravity(btVector3 newGravity);
		static btTriangleMesh* CreatePhysicsBodyMesh(ShapeData* data);
	};
}
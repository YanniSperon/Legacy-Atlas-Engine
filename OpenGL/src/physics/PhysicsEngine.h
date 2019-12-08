#pragma once

#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionShapes/btTriangleMesh.h"
#include "PhysicsDebugDrawer.h"
#include "ShapeData.h"

namespace Atlas {
	class PhysicsEngine {
	private:
		btDefaultCollisionConfiguration* collisionConfiguration;
		btCollisionDispatcher* dispatcher;
		btBroadphaseInterface* overlappingPairCache;
		btSequentialImpulseConstraintSolver* solver;
		btDiscreteDynamicsWorld* dynamicsWorld;
		btAlignedObjectArray<btCollisionShape*> collisionShapes;
		PhysicsDebugDrawer* debugDrawer;
	public:
		PhysicsEngine();
		~PhysicsEngine();

		void Initialize();
		void Update(float deltaT);
		btCollisionObject* AddPhysicsBody(btCollisionShape* shape, btTransform& transformation, float mass);
		void Recalculate(btCollisionObject* object);
		void DrawDebug();
		void Cleanup();
		void ToggleDebugger();
		void RemovePhysicsBody(btCollisionObject* object);
		static btTriangleMesh* CreatePhysicsBodyMesh(ShapeData* data);
	};
}
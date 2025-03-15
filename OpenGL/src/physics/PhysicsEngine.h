#pragma once

#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionShapes/btTriangleMesh.h"
#include "PhysicsObject.h"
#include "PhysicsScene.h"
#include "ShapeData.h"
#include "Scene.h"

namespace Atlas {
	class PhysicsEngine {
	public:
		static void Initialize(SceneSettings s);
		static void Update(double deltaT);
		static void SetPhysicsScene(PhysicsScene* scene);
		static btCollisionObject* AddPhysicsBody(btCollisionShape* shape, btTransform& transformation, float mass, PhysicsObject* pObj);
		static void Recalculate(btCollisionObject* object);
		static void DrawDebug();
		static void Cleanup();
		static void ToggleDebugger();
		static void RemovePhysicsBody(btCollisionObject* object);
		static void SetGravity(btVector3 newGravity);
		static btTriangleMesh* CreatePhysicsBodyMesh(ShapeData& data);
		static void SetPhysics(bool togglePhysics);
	};
}
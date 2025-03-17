#pragma once

#include "btBulletDynamicsCommon.h"
#include "bullet/BulletCollision/CollisionShapes/btTriangleMesh.h"
#include "bullet/BulletCollision/CollisionShapes/btConvexHullShape.h"
#include "bullet/BulletCollision/CollisionShapes/btTriangleIndexVertexArray.h"

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
		static btTriangleMesh* CreateTriangleMesh(ShapeData& data);
		static btTriangleIndexVertexArray* CreateIndexVertexArray(btTriangleMesh* m);
		static void SetPhysics(bool togglePhysics);
	};
}
#include "PhysicsEngine.h"
#include "Global.h"
#include "System.h"
#include "Convert.h"
#include "Player.h"
#include "PhysicsLinker.h"
#include <iostream>

namespace Atlas {

	static btDefaultCollisionConfiguration* collisionConfiguration;
	static btCollisionDispatcher* dispatcher;
	static btBroadphaseInterface* overlappingPairCache;
	static btSequentialImpulseConstraintSolver* solver;
	static btDiscreteDynamicsWorld* dynamicsWorld;
	//static PhysicsDebugDrawer* debugDrawer;
	static bool physicsEnabled;

	static PhysicsScene* physicsScene;



	bool BulletCollisionCallbackFunc(btManifoldPoint& cp, const btCollisionObjectWrapper* obj1, int id1, int index1, const btCollisionObjectWrapper* obj2, int id2, int index2) {
		const btCollisionObject* obj1Object = obj1->getCollisionObject();
		const btCollisionObject* obj2Object = obj1->getCollisionObject();
		if (obj1Object == NULL || obj1Object == nullptr) {
			System::Err("This is our problem1");
		}
		if (obj2Object == NULL || obj2Object == nullptr) {
			System::Err("This is our problem2");
		}
		BulletPhysicsObject* userPtr1 = (BulletPhysicsObject*)obj1Object->getUserPointer();
		BulletPhysicsObject* userPtr2 = (BulletPhysicsObject*)obj2Object->getUserPointer();
		if (userPtr1 == NULL || userPtr1 == nullptr) {
			System::Err("This is our problem ptr1");
		}
		if (userPtr2 == NULL || userPtr2 == nullptr) {
			System::Err("This is our problem ptr2");
		}
		userPtr1->collisionData.obj1 = obj1Object;
		userPtr2->collisionData.obj2 = obj2Object;
		System::Log("First object collided: " + std::to_string(userPtr1->uid) + ".");
		System::Log("Second object collided: " + std::to_string(userPtr2->uid) + ".");
		PhysicsObject* physObj1 = (PhysicsObject*)userPtr1->physicsObject;
		PhysicsObject* physObj2 = (PhysicsObject*)userPtr2->physicsObject;
		physObj1->PrepareForDeletion();
		physObj2->PrepareForDeletion();
		PhysicsLinker::DeleteObjectFromScene(physicsScene, physObj1);
		PhysicsLinker::DeleteObjectFromScene(physicsScene, physObj2);
		delete physObj1;
		delete physObj2;
		return false;
	}

	void PhysicsEngine::Initialize()
	{
		gContactAddedCallback=BulletCollisionCallbackFunc;
		collisionConfiguration = new btDefaultCollisionConfiguration();
		dispatcher = new btCollisionDispatcher(collisionConfiguration);
		overlappingPairCache = new btDbvtBroadphase();
		solver = new btSequentialImpulseConstraintSolver;
		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
		dynamicsWorld->setGravity(btVector3(0, -9.80665, 0));
		
		//debugDrawer = new PhysicsDebugDrawer();
		//debugDrawer->setDebugMode(0);
		//dynamicsWorld->setDebugDrawer(debugDrawer);

		physicsEnabled = true;
	}

	void PhysicsEngine::Update(double deltaT)
	{
		if (physicsEnabled) {
			ToggleDebugger();
			// switch physics frame rate to 30 for better performance \/
			dynamicsWorld->stepSimulation(deltaT, 10/*, 0.033333333333333333f*/);
			Global::Variables.currentScene.Update();
		}
	}

	void PhysicsEngine::SetPhysicsScene(PhysicsScene* scene)
	{
		physicsScene = scene;
	}

	btCollisionObject* PhysicsEngine::AddPhysicsBody(btCollisionShape* shape, btTransform& transformation, float mass, PhysicsObject* pObj)
	{
		if (shape != NULL) {
			btScalar massOfObject(mass);
			bool isDynamic = (massOfObject != 0.0f);
			btVector3 localInertia(0.0, 0.0, 0.0);
			if (isDynamic) {
				shape->calculateLocalInertia(massOfObject, localInertia);
			}
			//printf("%f, %f, %f", transformation.getOrigin()[0], transformation.getOrigin()[1], transformation.getOrigin()[2]);
			if (&transformation == NULL) {
				System::Err("NULL transformation");
			}
			btDefaultMotionState* myMotionState = new btDefaultMotionState(transformation);
			if (myMotionState == NULL) {
				System::Err("NULL myMotionState");
			}
			btRigidBody::btRigidBodyConstructionInfo rbInfo(massOfObject, myMotionState, shape, localInertia);
			if (&rbInfo == NULL) {
				System::Err("NULL rbInfo");
			}
			btRigidBody* body = new btRigidBody(rbInfo);
			if (body == NULL) {
				System::Err("NULL body");
			}
			
			bool shouldCollideWithPlayerBody = true;

			if (mass > 45.0f) {
				body->setActivationState(DISABLE_DEACTIVATION);
				body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CollisionFlags::CF_CUSTOM_MATERIAL_CALLBACK);
				shouldCollideWithPlayerBody = false;
				//body->setCollisionFlags;
				//body->setIgnoreCollisionCheck;
				//body->setFlags;
			}
			//body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
			//body->setActivationState(DISABLE_DEACTIVATION);
			//void* parentPhysicsObject, unsigned long long int objectUID, bool shouldCollideWithPlayerBody
			body->setUserPointer((void*)(new BulletPhysicsObject(pObj, pObj->GetUID(), shouldCollideWithPlayerBody)));
			dynamicsWorld->addRigidBody(body);
			return body;
		}
		else {
			System::Err("NULL shape!");
			return NULL;
		}
	}

	void PhysicsEngine::Recalculate(btCollisionObject* object)
	{
		dynamicsWorld->updateSingleAabb(object);
	}

	void PhysicsEngine::DrawDebug()
	{
		dynamicsWorld->debugDrawWorld();
	}

	void PhysicsEngine::Cleanup()
	{
		for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
		{
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
			{
				delete body->getCollisionShape();
				delete body->getMotionState();
			}
			dynamicsWorld->removeCollisionObject(obj);
			delete obj;
		}
		
		delete dynamicsWorld;
		delete solver;
		delete overlappingPairCache;
		delete dispatcher;
		delete collisionConfiguration;
	}

	void PhysicsEngine::ToggleDebugger()
	{
		//if (Global::Variables.keyIn.ninePressed) {
		//	System::Log("Toggling debug wireframe");
		//	debugDrawer->ToggleDebugFlag(btIDebugDraw::DBG_DrawWireframe);
		//}
		//if (Global::Variables.keyIn.zeroPressed) {
		//	System::Log("Toggling debug AABB");
		//	debugDrawer->ToggleDebugFlag(btIDebugDraw::DBG_DrawAabb);
		//}
	}

	void PhysicsEngine::RemovePhysicsBody(btCollisionObject* object)
	{
		btRigidBody* body = btRigidBody::upcast(object);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
			delete body->getCollisionShape();
		}
		dynamicsWorld->removeCollisionObject(object);
		delete object;
	}

	void PhysicsEngine::SetGravity(btVector3 newGravity)
	{
		dynamicsWorld->setGravity(newGravity);
	}

	btTriangleMesh* PhysicsEngine::CreatePhysicsBodyMesh(ShapeData& data)
	{
		btTriangleMesh* returnValue = new btTriangleMesh();
		for (int i = 0; i < data.numIndices / 3; i++)
		{
			int index0 = data.indices[i * 3];
			int index1 = data.indices[i * 3 + 1];
			int index2 = data.indices[i * 3 + 2];
			btVector3 vertex0(Convert::Vector3(data.vertices[index0].position));
			btVector3 vertex1(Convert::Vector3(data.vertices[index1].position));
			btVector3 vertex2(Convert::Vector3(data.vertices[index2].position));
			returnValue->addTriangle(vertex0, vertex1, vertex2);
		}
		return returnValue;
	}

	void PhysicsEngine::SetPhysics(bool togglePhysics)
	{
		physicsEnabled = togglePhysics;
	}
}
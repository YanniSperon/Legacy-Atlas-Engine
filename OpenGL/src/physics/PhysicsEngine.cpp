#include "PhysicsEngine.h"
#include "Global.h"
#include "System.h"

namespace Atlas {

	static btDefaultCollisionConfiguration* collisionConfiguration;
	static btCollisionDispatcher* dispatcher;
	static btBroadphaseInterface* overlappingPairCache;
	static btSequentialImpulseConstraintSolver* solver;
	static btDiscreteDynamicsWorld* dynamicsWorld;
	static PhysicsDebugDrawer* debugDrawer;
	static bool physicsEnabled;

	void PhysicsEngine::Initialize()
	{
		collisionConfiguration = new btDefaultCollisionConfiguration();
		dispatcher = new btCollisionDispatcher(collisionConfiguration);
		overlappingPairCache = new btDbvtBroadphase();
		solver = new btSequentialImpulseConstraintSolver;
		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
		dynamicsWorld->setGravity(btVector3(0, -9.80665, 0));
		
		debugDrawer = new PhysicsDebugDrawer();
		debugDrawer->setDebugMode(0);
		dynamicsWorld->setDebugDrawer(debugDrawer);

		physicsEnabled = true;
	}

	void PhysicsEngine::Update(float deltaT)
	{
		if (physicsEnabled) {
			ToggleDebugger();
			dynamicsWorld->stepSimulation(deltaT, 10);
			Global::Variables.currentScene.Update();
		}
	}

	btCollisionObject* PhysicsEngine::AddPhysicsBody(btCollisionShape* shape, btTransform& transformation, float mass)
	{
		if (shape != NULL) {
			btScalar massOfObject(mass);
			bool isDynamic = (massOfObject != 0.0f);
			btVector3 localInertia(0.0, 0.0, 0.0);
			if (isDynamic) {
				shape->calculateLocalInertia(massOfObject, localInertia);
			}
			printf("%f, %f, %f", transformation.getOrigin()[0], transformation.getOrigin()[1], transformation.getOrigin()[2]);
			if (&transformation == NULL) {
				System::Log("Null transformation");
			}
			btDefaultMotionState* myMotionState = new btDefaultMotionState(transformation);
			if (myMotionState == NULL) {
				System::Log("Null myMotionState");
			}
			btRigidBody::btRigidBodyConstructionInfo rbInfo(massOfObject, myMotionState, shape, localInertia);
			if (&rbInfo == NULL) {
				System::Log("Null rbInfo");
			}
			btRigidBody* body = new btRigidBody(rbInfo);
			if (body == NULL) {
				System::Log("Null body");
			}
			dynamicsWorld->addRigidBody(body);
			return body;
		}
		else {
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
		if (Global::Variables.keyIn.ninePressed) {
			System::Log("Toggling debug wireframe");
			debugDrawer->ToggleDebugFlag(btIDebugDraw::DBG_DrawWireframe);
		}
		if (Global::Variables.keyIn.zeroPressed) {
			System::Log("Toggling debug AABB");
			debugDrawer->ToggleDebugFlag(btIDebugDraw::DBG_DrawAabb);
		}
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

	btTriangleMesh* PhysicsEngine::CreatePhysicsBodyMesh(ShapeData* data)
	{
		//GLuint numIndices;
		btTriangleMesh* returnValue = new btTriangleMesh();
		for (int i = 0; i < data->numIndices; i++)
		{
			int index0 = data->indices[i * 3];
			int index1 = data->indices[i * 3 + 1];
			int index2 = data->indices[i * 3 + 2];

			btVector3 vertex0(data->vertices[index0].position.x, data->vertices[index0].position.y, data->vertices[index0].position.z);
			btVector3 vertex1(data->vertices[index1].position.x, data->vertices[index1].position.y, data->vertices[index1].position.z);
			btVector3 vertex2(data->vertices[index2].position.x, data->vertices[index2].position.y, data->vertices[index2].position.z);

			returnValue->addTriangle(vertex0, vertex1, vertex2);
		}
		return returnValue;
	}

	void PhysicsEngine::SetPhysics(bool togglePhysics)
	{
		physicsEnabled = togglePhysics;
	}
}
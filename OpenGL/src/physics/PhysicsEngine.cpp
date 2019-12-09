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

	void PhysicsEngine::Initialize()
	{
		collisionConfiguration = new btDefaultCollisionConfiguration();
		dispatcher = new btCollisionDispatcher(collisionConfiguration);
		overlappingPairCache = new btDbvtBroadphase();
		solver = new btSequentialImpulseConstraintSolver;
		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
		dynamicsWorld->setGravity(btVector3(0, -9.80665, 0));
		// add debugger
		debugDrawer = new PhysicsDebugDrawer();
		// set the initial debug level to 0
		debugDrawer->setDebugMode(0);
		// add the debug drawer to the world
		dynamicsWorld->setDebugDrawer(debugDrawer);
		/*{
			btCollisionShape* floor = new btBoxShape(btVector3(btScalar(50.0), btScalar(50.0), btScalar(50.0)));
			collisionShapes.push_back(floor);

			btTransform floorTransformation;
			floorTransformation.setIdentity();
			floorTransformation.setOrigin(btVector3(0.0, -56.0, 0.0));

			btScalar mass(0.0);
			bool isDynamic = (mass != 0.0f);
			btVector3 localInertia(0.0, 0.0, 0.0);
			if (isDynamic) {
				floor->calculateLocalInertia(mass, localInertia);
			}

			btDefaultMotionState* myMotionState = new btDefaultMotionState(floorTransformation);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, floor, localInertia);
			btRigidBody* body = new btRigidBody(rbInfo);

			dynamicsWorld->addRigidBody(body);
			Global::Variables.currentScene.preloadedObjectsOnScene.push_back(new Object(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), type::cubeModel, "", "", "res/images/textures/", "newcow.png", "res/shaders/", "Basic.shader", true, false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
		}

		{
			btCollisionShape* colShape = new btSphereShape(btScalar(1.0));
			collisionShapes.push_back(colShape);

			btTransform startTransform;
			startTransform.setIdentity();

			btScalar mass(1.0);
			bool isDynamic = (mass != 0.0f);
			btVector3 localInertia(0.0, 0.0, 0.0);
			if (isDynamic) {
				colShape->calculateLocalInertia(mass, localInertia);
			}

			btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
			btRigidBody* body = new btRigidBody(rbInfo);

			dynamicsWorld->addRigidBody(body);
			Global::Variables.currentScene.preloadedObjectsOnScene.push_back(new Object(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), type::cubeModel, "", "", "res/images/textures/", "skybox.png", "res/shaders/", "Basic.shader", true, false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
		}*/
	}

	void PhysicsEngine::Update(float deltaT)
	{
		ToggleDebugger();
		//dynamicsWorld->stepSimulation(deltaT, 10);
		//for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
		//{
		//	btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
		//	btRigidBody* body = btRigidBody::upcast(obj);
		//	btTransform trans;
		//	if (body && body->getMotionState())
		//	{
		//		body->getMotionState()->getWorldTransform(trans);
		//	}
		//	else
		//	{
		//		trans = obj->getWorldTransform();
		//	}
		//	printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
		//}
		//////////////////////////////////////////////////////////////////////////
		dynamicsWorld->stepSimulation(deltaT, 10);
		//////////////////////////////////////////////////////////////////////////
		Global::Variables.currentScene.Update();
		//btCollisionObject* obj2 = dynamicsWorld->getCollisionObjectArray()[0];
		//btRigidBody* body2 = btRigidBody::upcast(obj2);
		//btTransform trans2;
		//if (body2 && body2->getMotionState())
		//{
		//	body2->getMotionState()->getWorldTransform(trans2);
		//}
		//else
		//{
		//	trans2 = obj2->getWorldTransform();
		//}
		//Global::Variables.currentScene.preloadedObjectsOnScene.at(3)->Translate3f(float(trans2.getOrigin().getX()), float(trans2.getOrigin().getY()), float(trans2.getOrigin().getZ()));
		////////////////////////////////////////////////////////////////////////////
		//btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[1];
		//btRigidBody* body = btRigidBody::upcast(obj);
		//btTransform trans;
		//if (body && body->getMotionState())
		//{
		//	body->getMotionState()->getWorldTransform(trans);
		//}
		//else
		//{
		//	trans = obj->getWorldTransform();
		//}
		//Global::Variables.currentScene.preloadedObjectsOnScene.at(2)->Translate3f(float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
		//////////////////////////////////////////////////////////////////////////
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
}
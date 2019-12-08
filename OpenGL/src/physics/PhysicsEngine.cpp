#include "PhysicsEngine.h"
#include "Global.h"

namespace Atlas {

	static btDefaultCollisionConfiguration* collisionConfiguration;
	static btCollisionDispatcher* dispatcher;
	static btBroadphaseInterface* overlappingPairCache;
	static btSequentialImpulseConstraintSolver* solver;
	static btDiscreteDynamicsWorld* dynamicsWorld;
	static btAlignedObjectArray<btCollisionShape*> collisionShapes;

	void PhysicsEngine::Initialize()
	{
		collisionConfiguration = new btDefaultCollisionConfiguration();
		dispatcher = new btCollisionDispatcher(collisionConfiguration);
		overlappingPairCache = new btDbvtBroadphase();
		solver = new btSequentialImpulseConstraintSolver;
		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
		dynamicsWorld->setGravity(btVector3(0, -9.80665, 0));

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

	btCollisionObject* PhysicsEngine::AddRigidBody(btCollisionShape* shape, btTransform& transformation, float mass)
	{
		if (shape != NULL) {
			collisionShapes.push_back(shape);

			btScalar massOfObject(mass);
			bool isDynamic = (massOfObject != 0.0f);
			btVector3 localInertia(0.0, 0.0, 0.0);
			if (isDynamic) {
				shape->calculateLocalInertia(massOfObject, localInertia);
			}
			printf("%f, %f, %f", transformation.getOrigin()[0], transformation.getOrigin()[1], transformation.getOrigin()[2]);
			btDefaultMotionState* myMotionState = new btDefaultMotionState(transformation);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(massOfObject, myMotionState, shape, localInertia);
			btRigidBody* body = new btRigidBody(rbInfo);
			dynamicsWorld->addRigidBody(body);
			return body;
		}
		else {
			return NULL;
		}
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

		for (int j = 0; j < collisionShapes.size(); j++)
		{
			btCollisionShape* shape = collisionShapes[j];
			collisionShapes[j] = 0;
			delete shape;
		}
		
		delete dynamicsWorld;
		delete solver;
		delete overlappingPairCache;
		delete dispatcher;
		delete collisionConfiguration;
		collisionShapes.clear();
	}
}
#include "PhysicsScene.h"
#include "Global.h"
#include "System.h"

namespace Atlas {

	PhysicsScene::PhysicsScene()
	{

	}

	PhysicsScene::PhysicsScene(Scene* scene)
		: sceneSettings(scene->sceneSettings)
	{
		System::Log("Preloaded Objects:");
		for (unsigned int i = 0; i < scene->preloadedObjectsOnScene.size(); i++) {
			System::Log("    " + scene->preloadedObjectsOnScene.at(i)->ToString());
			physicsObjectsOnScene.push_back(new PhysicsObject(scene->preloadedObjectsOnScene.at(i), 0.0f, PhysicsObject::typeShape::box));
		}
		System::Log("Objects:");
		for (unsigned int i = 0; i < scene->objectsOnScene.size(); i++) {
			System::Log("    " + scene->objectsOnScene.at(i)->ToString());
			physicsObjectsOnScene.push_back(new PhysicsObject(scene->objectsOnScene.at(i), 1.0f, PhysicsObject::typeShape::box));
		}
		for (unsigned int i = 0; i < scene->preloadedObjectsOnScene.size(); i++) {
			physicsLightsOnScene.push_back(new PhysicsLight(scene->lightsOnScene.at(i), 0.0f, PhysicsObject::typeShape::box));
		}
		for (unsigned int i = 0; i < scene->camerasOnScene.size(); i++) {
			playersOnScene.push_back(new Player(scene->camerasOnScene.at(i)));
		}
		if (playersOnScene.size() == 0) {
			System::Err("Error initializing player!");
		}
	}

	PhysicsScene::~PhysicsScene()
	{
		// MAKE SURE TO SWITCH OUT CAMERA BEFORE THIS GETS DESTROYED BECAUSE THEN ACTIVECAMERA = NULL
		for (unsigned int i = 0; i < physicsObjectsOnScene.size(); i++) {
			delete physicsObjectsOnScene.at(i);
		}
		physicsObjectsOnScene.clear();

		for (unsigned int i = 0; i < physicsLightsOnScene.size(); i++) {
			delete physicsLightsOnScene.at(i);
		}
		physicsLightsOnScene.clear();

		for (unsigned int i = 0; i < playersOnScene.size(); i++) {
			delete playersOnScene.at(i);
		}
		playersOnScene.clear();
	}

	void PhysicsScene::Submit(PhysicsRenderer* renderer, Player* camera)
	{
		for (unsigned int i = 0; i < physicsObjectsOnScene.size(); i++) {
			renderer->Submit3D(physicsObjectsOnScene.at(i), camera->GetTranslation());
		}

		for (unsigned int i = 0; i < physicsLightsOnScene.size(); i++) {
			renderer->Submit3D(physicsLightsOnScene.at(i), camera->GetTranslation());
		}

		for (unsigned int i = 0; i < playersOnScene.size(); i++) {
			renderer->Submit3D(playersOnScene.at(i)->GetPlayerModel(), camera->GetTranslation());
		}

		renderer->SubmitForceRender3DObject(camera->GetSkybox());
	}

	void PhysicsScene::Update()
	{
		for (unsigned int i = 0; i < physicsObjectsOnScene.size(); i++) {
			physicsObjectsOnScene.at(i)->Update();
		}
		
		for (unsigned int i = 0; i < physicsLightsOnScene.size(); i++) {
			physicsLightsOnScene.at(i)->Update();
		}

		for (unsigned int i = 0; i < playersOnScene.size(); i++) {
			playersOnScene.at(i)->GetPlayerModel()->Update();
		}
	}
}
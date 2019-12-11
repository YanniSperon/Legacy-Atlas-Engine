#include "PhysicsScene.h"
#include "Global.h"

namespace Atlas {

	PhysicsScene::PhysicsScene()
	{

	}

	PhysicsScene::PhysicsScene(Scene* scene)
	{

	}

	PhysicsScene::~PhysicsScene()
	{
		// MAKE SURE TO SWITCH OUT CAMERA BEFORE THIS GETS DESTROYED
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

	void PhysicsScene::Submit(Renderer* renderer, Player* camera)
	{
		for (unsigned int i = 0; i < physicsObjectsOnScene.size(); i++) {
			renderer->Submit3D(physicsObjectsOnScene.at(i), camera->Camera::GetTranslation());
		}

		for (unsigned int i = 0; i < physicsLightsOnScene.size(); i++) {
			renderer->Submit3D(physicsLightsOnScene.at(i), camera->Camera::GetTranslation());
		}

		for (unsigned int i = 0; i < playersOnScene.size(); i++) {
			renderer->Submit3D(playersOnScene.at(i), camera->Camera::GetTranslation());
		}

		renderer->SubmitForceRender3D(Global::Variables.activeCamera->GetSkybox());
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
			playersOnScene.at(i)->Update();
		}
	}
}
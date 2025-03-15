#include "Scene.h"
#include "IO.h"
#include "System.h"
#include "Player.h"
#include "Global.h"

namespace Atlas {

	Scene::Scene()
	{

	}

	Scene::Scene(std::vector<Object*> preloadedObjects, std::vector<Object*> objects, std::vector<Light*> lightSource, std::vector<Camera*> cameras, SceneSettings settings)
	{
		preloadedObjectsOnScene = preloadedObjects;
		objectsOnScene = objects;
		lightsOnScene = lightSource;
		camerasOnScene = cameras;
		sceneSettings = settings;
	}

	Scene::~Scene()
	{
		for (unsigned int i = 0; i < preloadedObjectsOnScene.size(); i++) {
			delete preloadedObjectsOnScene.at(i);
		}
		preloadedObjectsOnScene.clear();

		for (unsigned int i = 0; i < objectsOnScene.size(); i++) {
			delete objectsOnScene.at(i);
		}
		objectsOnScene.clear();

		for (unsigned int i = 0; i < lightsOnScene.size(); i++) {
			delete lightsOnScene.at(i);
		}
		lightsOnScene.clear();


		for (unsigned int i = 0; i < camerasOnScene.size(); i++) {
			delete camerasOnScene.at(i);
		}
		camerasOnScene.clear();
	}

	void Scene::Submit(Renderer* renderer, Camera* camera)
	{
		for (unsigned int i = 0; i < preloadedObjectsOnScene.size(); i++) {
			renderer->Submit3D(preloadedObjectsOnScene[i], camera->GetTranslation());
		}

		for (unsigned int i = 0; i < objectsOnScene.size(); i++) {
			renderer->Submit3D(objectsOnScene[i], camera->GetTranslation());
		}

		for (unsigned int i = 0; i < lightsOnScene.size(); i++) {
			renderer->Submit3D(lightsOnScene[i], camera->GetTranslation());
		}

		renderer->SubmitForceRender3D(Global::Variables.activeCamera->GetSkybox());

		//for (unsigned int i = 0; i < camerasOnScene.size(); i++) {
		//	Player* player = dynamic_cast<Player*>(camerasOnScene.at(i));
		//	if (player != nullptr) {
		//		renderer->Submit3D(player, camPos);
		//	}
		//}
	}

	void Scene::Save(std::string directory, std::string name)
	{
		System::Log("Saving");
		IO::SaveToFile(objectsOnScene, directory, name);
	}

	void Scene::Update()
	{
		//for (unsigned int i = 0; i < preloadedObjectsOnScene.size(); i++) {
		//	preloadedObjectsOnScene.at(i)->Update();
		//}
		//
		//for (unsigned int i = 0; i < objectsOnScene.size(); i++) {
		//	objectsOnScene.at(i)->Update();
		//}
		//
		//for (unsigned int i = 0; i < lightsOnScene.size(); i++) {
		//	lightsOnScene.at(i)->Update();
		//}

		//for (unsigned int i = 0; i < camerasOnScene.size(); i++) {
		//	Player* player = dynamic_cast<Player*>(camerasOnScene.at(i));
		//	if (player != nullptr) {
		//		player->Update();
		//	}
		//}
	}
}
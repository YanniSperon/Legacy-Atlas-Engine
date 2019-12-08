#include "Scene.h"
#include "IO.h"
#include "System.h"

namespace Atlas {

	Scene::Scene()
	{
	}

	Scene::Scene(std::vector<Object*> preloadedObjects, std::vector<Object*> objects, std::vector<Light*> lightSource)
	{
		preloadedObjectsOnScene = preloadedObjects;
		objectsOnScene = objects;
		lightsOnScene = lightSource;
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
	}

	void Scene::Submit(Renderer* renderer, glm::vec3 camPos, glm::mat4 viewMatrix)
	{
		for (unsigned int i = 0; i < preloadedObjectsOnScene.size(); i++) {
			if (i == 0) {
				renderer->SubmitForceRender3D(preloadedObjectsOnScene[i]);
			}
			else {
				renderer->Submit3D(preloadedObjectsOnScene[i], camPos);
			}
		}

		for (unsigned int i = 0; i < objectsOnScene.size(); i++) {
			renderer->Submit3D(objectsOnScene[i], camPos);
		}
	}

	void Scene::Save(std::string directory, std::string name)
	{
		System::Log("Saving");
		IO::SaveToFile(objectsOnScene, directory, name);
	}

	void Scene::Update()
	{
		for (unsigned int i = 0; i < preloadedObjectsOnScene.size(); i++) {
			preloadedObjectsOnScene.at(i)->Update();
		}

		for (unsigned int i = 0; i < objectsOnScene.size(); i++) {
			objectsOnScene.at(i)->Update();
		}
	}
}
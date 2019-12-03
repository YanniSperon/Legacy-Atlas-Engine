#include "Scene.h"
#include "IO.h"
#include "System.h"

Atlas::Scene::Scene()
{
}

Atlas::Scene::Scene(std::vector<Object*> preloadedObjects, std::vector<Object*> objects, std::vector<Light*> lightSource)
{
	preloadedObjectsOnScene = preloadedObjects;
	objectsOnScene = objects;
	lightsOnScene = lightSource;
}

Atlas::Scene::~Scene()
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

void Atlas::Scene::Submit(Renderer* renderer, glm::vec3 camPos, glm::mat4 viewMatrix)
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

void Atlas::Scene::Save(std::string directory, std::string name)
{
	System::Log("Saving");
	IO::SaveToFile(objectsOnScene, directory, name);
}

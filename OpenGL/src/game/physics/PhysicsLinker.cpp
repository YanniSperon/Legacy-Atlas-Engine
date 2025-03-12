#include "PhysicsLinker.h"

void Atlas::PhysicsLinker::DeleteObjectFromScene(PhysicsScene* scene, PhysicsObject* obj)
{
	for (unsigned int i = 0; i < scene->physicsObjectsOnScene.size(); i++) {
		if (scene->physicsObjectsOnScene.at(i) == obj) {
			scene->physicsObjectsOnScene.erase(scene->physicsObjectsOnScene.begin() + i);
			return;
		}
	}

	for (unsigned int i = 0; i < scene->physicsLightsOnScene.size(); i++) {
		if (scene->physicsLightsOnScene.at(i) == obj) {
			scene->physicsLightsOnScene.erase(scene->physicsLightsOnScene.begin() + i);
			return;
		}
	}

	for (unsigned int i = 0; i < scene->playersOnScene.size(); i++) {
		if (scene->playersOnScene.at(i)->GetPlayerModel() == obj) {
			scene->playersOnScene.erase(scene->playersOnScene.begin() + i);
			return;
		}
	}
}

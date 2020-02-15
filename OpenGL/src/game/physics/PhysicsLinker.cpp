#include "PhysicsLinker.h"

void Atlas::PhysicsLinker::DeleteObjectFromScene(PhysicsScene* scene, PhysicsObject* obj)
{
	bool found = false;
	for (unsigned int i = 0; i < scene->physicsObjectsOnScene.size(); i++) {
		if (scene->physicsObjectsOnScene.at(i) == obj) {
			scene->physicsObjectsOnScene.erase(scene->physicsObjectsOnScene.begin() + i);
			found = true;
		}
		if (found) {
			break;
		}
	}

	for (unsigned int i = 0; i < scene->physicsLightsOnScene.size(); i++) {
		if (scene->physicsLightsOnScene.at(i) == obj) {
			scene->physicsLightsOnScene.erase(scene->physicsLightsOnScene.begin() + i);
			found = true;
		}
		if (found) {
			break;
		}
	}

	for (unsigned int i = 0; i < scene->playersOnScene.size(); i++) {
		if (scene->playersOnScene.at(i)->GetPlayerModel() == obj) {
			scene->playersOnScene.erase(scene->playersOnScene.begin() + i);
			found = true;
		}
		if (found) {
			break;
		}
	}
}

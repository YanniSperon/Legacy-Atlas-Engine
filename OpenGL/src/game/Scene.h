#pragma once

#include "glm/glm.hpp"
#include "Object.h"
#include "Renderer.h"
#include "Light.h"
#include <string>
#include <vector>
#include "btBulletCollisionCommon.h"
#include "Camera.h"

namespace Atlas {

	class Scene {
	public:
		std::vector<Object*> objectsOnScene;
		std::vector<Object*> preloadedObjectsOnScene;
		std::vector<Light*> lightsOnScene;
		std::vector<Camera*> camerasOnScene;

		Scene();
		Scene(std::vector<Object*> preloadedObjects, std::vector<Object*> objects, std::vector<Light*> lightSource, std::vector<Camera*> cameras);
		~Scene();

		void Submit(Renderer* renderer, Camera* camera);
		void Save(std::string directory, std::string name);
		void Update();
	};
}
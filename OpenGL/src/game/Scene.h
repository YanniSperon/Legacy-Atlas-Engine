#pragma once

#include "glm/glm.hpp"
#include "Object.h"
#include "Renderer.h"
#include "Light.h"
#include <string>
#include <vector>

namespace Atlas {

	class Scene {
	public:
		std::vector<Object*> objectsOnScene;
		std::vector<Object*> preloadedObjectsOnScene;
		std::vector<Light*> lightsOnScene;

		Scene();
		Scene(std::vector<Object*> preloadedObjects, std::vector<Object*> objects, std::vector<Light*> lightSources);
		~Scene();

		void Submit(Renderer* renderer, glm::vec3 camPos, glm::mat4 viewMatrix);
		void Save(std::string directory, std::string name);
	};
}
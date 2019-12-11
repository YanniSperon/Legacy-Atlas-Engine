#pragma once
#include "Scene.h"
#include "PhysicsObject.h"
#include "PhysicsLight.h"
#include "Player.h"

namespace Atlas {
	
	class PhysicsScene {
	private:

	public:
		std::vector<PhysicsObject*> physicsObjectsOnScene;
		std::vector<PhysicsLight*> physicsLightsOnScene;
		std::vector<Player*> playersOnScene;

		PhysicsScene();
		PhysicsScene(Scene* scene);
		~PhysicsScene();

		void Submit(Renderer* renderer, Player* camera);
		void Update();
	};
}
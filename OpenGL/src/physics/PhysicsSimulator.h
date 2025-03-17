#pragma once
#include "Scene.h"

namespace Atlas {
	class PhysicsSimulator {
	public:
		static void LaunchSimulation(Scene* sceneToSimulate);
	};
}
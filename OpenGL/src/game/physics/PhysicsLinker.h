#pragma once
#include "PhysicsObject.h"
#include "PhysicsScene.h"

namespace Atlas {
	class PhysicsLinker {
	public:
		static void DeleteObjectFromScene(PhysicsScene* scene, PhysicsObject* obj);
	};
}
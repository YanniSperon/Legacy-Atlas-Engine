#pragma once

#include <deque>
#include "PhysicsObject.h"
#include "PhysicsLight.h"
#include "Object2D.h"
#include "Player.h"

namespace Atlas {

	class PhysicsRenderer {
	private:
		std::deque<PhysicsObject*> renderQueue3D;
		std::deque<Object*> renderQueueObject3D;
		std::deque<Object2D*> renderQueue2D;
		glm::mat4 projectionMatrix;
		glm::mat4 orthographicMatrix;
		int localWidthBuffer = 0;
		int localHeightBuffer = 0;
	public:
		void Submit2D(Object2D* renderable);
		void Submit3D(PhysicsObject* renderable, glm::vec3 camPos);
		void Submit3DObject(Object* renderable, glm::vec3 camPos);
		void SubmitForceRender3D(PhysicsObject* renderable);
		void SubmitForceRender3DObject(Object* renderable);
		void SimpleFlush(Player* camera, int width, int height, float FOV, PhysicsLight* light);
	};
}
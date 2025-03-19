#pragma once

#include <deque>
#include "Renderer.h"

namespace Atlas {

	class SimpleRenderer : public Renderer {
	private:
		std::deque<Object*> renderQueue3D;
		std::deque<Object2D*> renderQueue2D;
		std::deque<Sentence*> renderQueueText;
		glm::mat4 projectionMatrix;
		glm::mat4 orthographicMatrix;
	public:
		void SubmitText(Sentence* renderable) override;
		void Submit2D(Object2D* renderable) override;
		void Submit3D(Object* renderable, glm::vec3 camPos) override;
		void SubmitForceRender3D(Object* renderable) override;
		//void Flush(Camera* camera, int width, int height, float FOV) override;
		//void Flush(Camera* camera, int width, int height, float FOV, Light* light) override;
		//void SimpleFlush(Camera* camera, int width, int height, float FOV) override;
		void SimpleFlush(Camera* camera, int width, int height, float FOV, Light* light) override;
	};
}
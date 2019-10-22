#pragma once

#include <deque>
#include "Renderer.h"

class SimpleRenderer : public Renderer {
private:
	std::deque<Object*> renderQueue3D;
	std::deque<Object2D*> renderQueue2D;
	std::deque<Sentence*> renderQueueText;
	glm::mat4 projectionMatrix;
	glm::mat4 orthographicMatrix;
	int localWidthBuffer = 0;
	int localHeightBuffer = 0;
public:
	void submitText(Sentence* renderable) override;
	void submit2D(Object2D* renderable) override;
	void submit3D(Object* renderable, glm::vec3 camPos) override;
	void submitForceRender3D(Object* renderable) override;
	void flush(glm::mat4 cameraView, int width, int height, float FOV) override;
	void flush(glm::mat4 cameraView, int width, int height, float FOV, Light* light) override;
};
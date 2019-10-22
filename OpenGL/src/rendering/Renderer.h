#pragma once
#include "Object.h"
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "Camera.h"
#include "Shader.h"
#include "Object2D.h"
#include "Font.h"
#include "Sentence.h"
#include "Light.h"

class Renderer {
public:
	virtual void submitText(Sentence* renderable) = 0;
	virtual void submit2D(Object2D* renderable) = 0;
	virtual void submit3D(Object* renderable, glm::vec3 camPos) = 0;
	virtual void submitForceRender3D(Object* renderable) = 0;
	virtual void flush(glm::mat4 cameraView, int width, int height, float FOV) = 0;
	virtual void flush(glm::mat4 cameraView, int width, int height, float FOV, Light* light) = 0;
};
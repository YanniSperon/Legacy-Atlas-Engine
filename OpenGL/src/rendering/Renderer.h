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

namespace Engine {

	class Renderer {
	public:
		virtual void SubmitText(Sentence* renderable) = 0;
		virtual void Submit2D(Object2D* renderable) = 0;
		virtual void Submit3D(Object* renderable, glm::vec3 camPos) = 0;
		virtual void SubmitForceRender3D(Object* renderable) = 0;
		virtual void Flush(Camera* camera, int width, int height, float FOV) = 0;
		virtual void Flush(Camera* camera, int width, int height, float FOV, Light* light) = 0;
		virtual void SimpleFlush(Camera* camera, int width, int height, float FOV) = 0;
		virtual void SimpleFlush(Camera* camera, int width, int height, float FOV, Light* light) = 0;
	};
}
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

namespace Atlas {

	class Renderer {
	public:
		static int GetUniformLocation(const std::string& name, GLuint shaderID)
		{
			int location = glGetUniformLocation(shaderID, name.c_str());
			if (location == -1) {
				if (name == "lightPos" || name == "light.position") {
					return -5;
				}
				printf("Warning: uniform '%s' doesn't exist!\n", name.c_str());
			}
			return location;
		}
		static void UseProgram(GLuint program) {
			glUseProgram(program);
		}
		static void SetUniformMat4f(const std::string& name, const glm::mat4& matrix, GLuint shaderID)
		{
			glUniformMatrix4fv(GetUniformLocation(name, shaderID), 1, GL_FALSE, &matrix[0][0]);
		}
		static bool SetUniformVec3(const std::string& name, const glm::vec3& vector, GLuint shaderID)
		{
			int temp = GetUniformLocation(name, shaderID);
			if (temp >= 0) {
				glUniform3fv(temp, 1, &vector[0]);
				return true;
			}
			else {
				return false;
			}
		}
		static void SetUniform1f(const std::string& name, const float& value, GLuint shaderID)
		{
			glUniform1f(GetUniformLocation(name, shaderID), value);
		}

		virtual void SubmitText(Sentence* renderable) = 0;
		virtual void Submit2D(Object2D* renderable) = 0;
		virtual void Submit3D(Object* renderable, glm::vec3 camPos) = 0;
		virtual void SubmitForceRender3D(Object* renderable) = 0;
		//virtual void Flush(Camera* camera, int width, int height, float FOV) = 0;
		//virtual void Flush(Camera* camera, int width, int height, float FOV, Light* light) = 0;
		//virtual void SimpleFlush(Camera* camera, int width, int height, float FOV) = 0;
		virtual void SimpleFlush(Camera* camera, int width, int height, float FOV, Light* light) = 0;
	};
}
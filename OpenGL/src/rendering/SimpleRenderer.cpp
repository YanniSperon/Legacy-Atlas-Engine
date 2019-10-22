#include "SimpleRenderer.h"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"

int GetUniformLocation(const std::string& name, GLuint shaderID)
{
	int location = glGetUniformLocation(shaderID, name.c_str());
	if (location == -1)
		printf("Warning: uniform '%s' doesn't exist!\n", name.c_str());
	return location;
}

void UseProgram(GLuint program) {
	glUseProgram(program);
}

void SetUniformMat4f(const std::string& name, const glm::mat4& matrix, GLuint shaderID)
{
	glUniformMatrix4fv(GetUniformLocation(name, shaderID), 1, GL_FALSE, &matrix[0][0]);
}

void SetUniformVec3(const std::string& name, const glm::vec3& vector, GLuint shaderID)
{
	glUniform3fv(GetUniformLocation(name, shaderID), 1, &vector[0]);
}


void SimpleRenderer::submitText(Sentence* renderable)
{
	renderQueueText.push_back(renderable);
}

void SimpleRenderer::submit2D(Object2D* renderable)
{
	renderQueue2D.push_back(renderable);
}

void SimpleRenderer::submit3D(Object* renderable, glm::vec3 camPos)
{
	glm::vec3 changeInValues = renderable->GetTranslation() - camPos;
	float distanceSquared = changeInValues.x * changeInValues.x + changeInValues.y * changeInValues.y;
	if (distanceSquared < 100.0f * 100.0f) {
		renderQueue3D.push_back(renderable);
	}
}

void SimpleRenderer::submitForceRender3D(Object* renderable)
{
	renderQueue3D.push_back(renderable);
}

void SimpleRenderer::flush(glm::mat4 cameraView, int width, int height, float FOV)
{
	glm::mat4 viewMatrix = cameraView;
	if (width != localWidthBuffer || height != localHeightBuffer) {
		if (width > 0 && height > 0) {
			projectionMatrix = glm::perspective(glm::radians(FOV), (float)width / (float)height, 0.1f, 100.0f);
			orthographicMatrix = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f);
		}
	}

	GLuint pastShader = 0;
	while (!renderQueue3D.empty())
	{
		Object* renderable = renderQueue3D.front();
		GLuint shaderID = renderable->GetShaderID();
		if (shaderID != pastShader) {
			UseProgram(shaderID);
			SetUniformMat4f("V", viewMatrix, shaderID);
			SetUniformMat4f("P", projectionMatrix, shaderID);
			SetUniformVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f), shaderID);
			SetUniformVec3("lightPos", glm::vec3(0.0f, 5.0f, 0.0f), shaderID);
			pastShader = shaderID;
		}
		SetUniformMat4f("M", renderable->GetModelTransformMatrix(), pastShader);
		renderable->Draw();
		renderQueue3D.pop_front();
	}

	while (!renderQueue2D.empty())
	{
		Object2D* renderable = renderQueue2D.front();
		GLuint shaderID = renderable->GetShaderID();
		if (shaderID != pastShader) {
			UseProgram(shaderID);
			pastShader = shaderID;
			SetUniformMat4f("P", orthographicMatrix, pastShader);
		}
		SetUniformMat4f("M", renderable->GetModelTransformMatrix(), pastShader);
		renderable->Draw();
		renderQueue2D.pop_front();
	}
	glDisable(GL_DEPTH_TEST);
	while (!renderQueueText.empty())
	{
		Sentence* renderable = renderQueueText.front();
		renderable->GetFont().RenderText(renderable->GetShader(), renderable->GetText(), renderable->GetPosition().x, renderable->GetPosition().y, renderable->GetScale(), renderable->GetColor(), orthographicMatrix);
		renderQueueText.pop_front();
	}
	glEnable(GL_DEPTH_TEST);
}

void SimpleRenderer::flush(glm::mat4 cameraView, int width, int height, float FOV, Light* light)
{
	glm::mat4 viewMatrix = cameraView;
	if (width != localWidthBuffer || height != localHeightBuffer) {
		if (width > 0 && height > 0) {
			projectionMatrix = glm::perspective(glm::radians(FOV), (float)width / (float)height, 0.1f, 100.0f);
			orthographicMatrix = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f);
		}
	}

	glm::mat4 VP = projectionMatrix * viewMatrix;
	GLuint pastShader = 0;
	while (!renderQueue3D.empty())
	{
		Object* renderable = renderQueue3D.front();
		GLuint shaderID = renderable->GetShaderID();
		if (shaderID != pastShader) {
			UseProgram(shaderID);
			SetUniformMat4f("V", viewMatrix, shaderID);
			SetUniformMat4f("P", projectionMatrix, shaderID);
			SetUniformVec3("lightColor", light->GetLightColor(), shaderID);
			SetUniformVec3("lightPos", light->GetTranslation(), shaderID);
			pastShader = shaderID;
		}
		SetUniformMat4f("M", renderable->GetModelTransformMatrix(), pastShader);
		renderable->Draw();
		renderQueue3D.pop_front();
	}

	GLuint shaderID = light->GetShaderID();
	if (shaderID != pastShader) {
		UseProgram(shaderID);
		SetUniformMat4f("V", viewMatrix, shaderID);
		SetUniformMat4f("P", projectionMatrix, shaderID);
		SetUniformVec3("lightColor", light->GetLightColor(), shaderID);
		SetUniformVec3("lightPos", light->GetTranslation(), shaderID);
		pastShader = shaderID;
	}
	SetUniformMat4f("M", light->GetModelTransformMatrix(), pastShader);
	light->Draw();

	while (!renderQueue2D.empty())
	{
		Object2D* renderable = renderQueue2D.front();
		GLuint shaderID = renderable->GetShaderID();
		if (shaderID != pastShader) {
			UseProgram(shaderID);
			pastShader = shaderID;
			SetUniformMat4f("P", orthographicMatrix, pastShader);
		}
		SetUniformMat4f("M", renderable->GetModelTransformMatrix(), pastShader);
		renderable->Draw();
		renderQueue2D.pop_front();
	}
	glDisable(GL_DEPTH_TEST);
	while (!renderQueueText.empty())
	{
		Sentence* renderable = renderQueueText.front();
		renderable->GetFont().RenderText(renderable->GetShader(), renderable->GetText(), renderable->GetPosition().x, renderable->GetPosition().y, renderable->GetScale(), renderable->GetColor(), orthographicMatrix);
		renderQueueText.pop_front();
	}
	glEnable(GL_DEPTH_TEST);
}
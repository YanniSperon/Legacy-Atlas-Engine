#pragma once

#include <string>
#include "glm/glm.hpp"
#include "ShapeData.h"

namespace Engine {
	class Mesh2D {
	private:
		glm::vec2 translation;
		float rotation;
		glm::vec2 scale;
		glm::vec2 minExtents;
		glm::vec2 maxExtents;
		glm::vec2 minTexCoords;
		glm::vec2 maxTexCoords;
		ShapeData2D shape;
	public:
		Mesh2D();
		Mesh2D(glm::vec2 min, glm::vec2 max, float rot, glm::vec2 trans, glm::vec2 s, glm::vec2 minTex, glm::vec2 maxTex);
		~Mesh2D();

		glm::mat4 GetModelTransformMatrix();
		void Rotate1f(float x);
		void RotateAdd1f(float x);
		void TranslateX(float x);
		void TranslateY(float y);
		void Translate2f(float x, float y);
		void TranslateVec2(glm::vec2 trans);
		void TranslateAdd2f(float x, float y);
		void TranslateAddVec2(glm::vec2 trans);
		void ScaleX(float x);
		void ScaleY(float y);
		void Scale2f(float x, float y);
		void ScaleVec2(glm::vec2 s);
		void ScaleAdd2f(float x, float y);
		void ScaleAddVec2(glm::vec2 s);
		glm::vec2 GetTranslation();
		float GetRotation();
		glm::vec2 GetScale();
		ShapeData2D GetShape();
		glm::vec2 GetMinExtents();
		glm::vec2 GetMaxExtents();
		glm::vec2 GetMinTexCoords();
		glm::vec2 GetMaxTexCoords();
		void SetShape(ShapeData2D newShape);

		virtual std::string GetType();
	};
}
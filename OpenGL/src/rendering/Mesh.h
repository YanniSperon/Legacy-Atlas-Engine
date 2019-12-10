#pragma once

#include "glm/glm.hpp"
#include "primitives/ShapeData.h"
#include <string>
#include "btBulletCollisionCommon.h"

namespace Atlas {

	enum type
	{
		cubeModel, normalModel, skyBox, cubeInvertedLighting
	};

	enum collidableType
	{

	};

	class Mesh {
	private:
		std::string directory;
		std::string fileName;
		glm::vec3 rotation;
		glm::vec3 translation;
		glm::vec3 scale;
		ShapeData shape;
		glm::vec3 minExtents;
		glm::vec3 maxExtents;
		type objectType;
		float mass;
		btCollisionObject* physicsObject;
	public:
		Mesh();
		Mesh(type type, std::string dir, std::string name, bool enablePhysics);
		Mesh(type type, std::string dir, std::string name, bool enablePhysics, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, float objectMass);
		~Mesh();

		glm::mat4 GetModelTransformMatrix();
		glm::mat4 GetModelTransRotMatrix();
		void RotateX(float x);
		void RotateY(float y);
		void RotateZ(float z);
		void Rotate3f(float x, float y, float z);
		void RotateVec3(glm::vec3 rot);
		void RotateAdd3f(float x, float y, float z);
		void RotateAddVec3(glm::vec3 rot);
		void TranslateX(float x);
		void TranslateY(float y);
		void TranslateZ(float z);
		void Translate3f(float x, float y, float z);
		void TranslateVec3(glm::vec3 trans);
		void TranslateAdd3f(float x, float y, float z);
		void TranslateAddVec3(glm::vec3 trans);
		void ScaleX(float x);
		void ScaleY(float y);
		void ScaleZ(float z);
		void Scale3f(float x, float y, float z);
		void ScaleVec3(glm::vec3 s);
		void ScaleAdd3f(float x, float y, float z);
		void ScaleAddVec3(glm::vec3 s);

		virtual void Update();

		btCollisionObject* GetPhysicsObject();
		void SetPhysicsBody();
		glm::vec3 GetTranslation();
		glm::vec3 GetRotation();
		glm::vec3 GetScale();
		ShapeData GetShape();
		std::string GetModelFileName();
		std::string GetModelFileDirectory();
		void SetShape(ShapeData newShape);
		float GetMass();

		std::string GetModelType();
		virtual std::string GetType();

		void Cleanup();
		static void FlushCache();
	};
}
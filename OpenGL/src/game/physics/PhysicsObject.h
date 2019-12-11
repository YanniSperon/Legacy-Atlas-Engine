#pragma once
#include "Mesh.h"
#include "Object.h"
#include "btBulletDynamicsCommon.h"

namespace Atlas {
	
	class PhysicsObject : public Mesh {
	private:
		unsigned int uid;
		GLuint vertexBufferID;
		GLuint indexBufferID;
		GLuint texID;
		GLuint shaderID;
		GLsizei numIndices;
		Material material;
		bool glInitialized;
		std::string textureDirectory;
		std::string textureName;
		std::string shaderDirectory;
		std::string shaderName;
		bool hasLighting;
		btCollisionObject* physicsObject;
	public:
		PhysicsObject();
		PhysicsObject(Object* obj, float mass);
		~PhysicsObject();

		void Update();
		void InverseUpdate();
		virtual glm::mat4 GetModelTransformMatrix() override;
		bool GetGLInitialized();
		Material GetMaterial();
		bool GetHasLighting();
		GLuint GetShaderID();
		GLuint GetTextureID();
		GLuint GetVBO();
		btCollisionObject* GetPhysicsObject();

		void SetHasLighting(bool newValue);

		void Launch(glm::vec3 viewDirection);

		void Draw();
		void Bind();
		void Unbind();

		void GLInit();
	};
}
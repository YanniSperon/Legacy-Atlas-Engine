#pragma once
#include "Mesh.h"
#include "Object.h"
#include "btBulletDynamicsCommon.h"

namespace Atlas {

	struct Collision {
		const btCollisionObject* obj1;
		const btCollisionObject* obj2;

		Collision() {
			obj1 = NULL;
			obj2 = NULL;
		}

		Collision(const btCollisionObject* object1, const btCollisionObject* object2)
			: obj1(object1), obj2(object2)
		{
			
		}
	};

	struct BulletPhysicsObject {
		unsigned long long int uid;
		Collision collisionData;
		bool shouldCollideWithPlayer;
		void* physicsObject;

		BulletPhysicsObject(void* parentPhysicsObject, unsigned long long int objectUID, bool shouldCollideWithPlayerBody)
			: uid(objectUID), collisionData(), physicsObject(parentPhysicsObject), shouldCollideWithPlayer(shouldCollideWithPlayerBody)
		{

		}

		~BulletPhysicsObject() {

		}
	};
	
	class PhysicsObject : public Mesh {
	private:
		unsigned long long int uid;
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
		unsigned long long int GetUID();

		void SetHasLighting(bool newValue);

		void Launch(glm::vec3 viewDirection);

		void Draw();
		void Bind();
		void Unbind();

		void PrepareForDeletion();

		void GLInit();
	};
}
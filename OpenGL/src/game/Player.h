#pragma once
#include "Object.h"
#include "Camera.h"

namespace Atlas {
	class Player : public Object, public Camera {
	private:
		float cameraYOffset;
	public:
		Player();
		Player(bool canControl, float movementSpeed, glm::vec3 startingLookDirection, glm::vec3 startingUpDirection, float camYOffset, float mouseSensitivity, type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderFileName, bool glInit, bool lighting, bool hasPhysics, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, float mass, Material mat);
		~Player();

		virtual void Update() override;

		virtual void MoveForward(float delta) override;
		virtual void MoveBackward(float delta) override;
		virtual void StrafeLeft(float delta) override;
		virtual void StrafeRight(float delta) override;
		virtual void MoveUp(float delta) override;
		virtual void MoveDown(float delta) override;
		virtual void Follow(Mesh* obj) override;
		virtual void BringWith(Mesh* obj) override;
	};
}
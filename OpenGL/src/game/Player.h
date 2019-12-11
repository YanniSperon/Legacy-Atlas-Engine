#pragma once
#include "Camera.h"
#include "PhysicsObject.h"

namespace Atlas {
	class Player {
	private:
		bool hasControls;
		float movementSpeed;
		glm::vec3 viewDirection;
		glm::vec3 upDirection;
		glm::vec3 cameraTranslation;
		double oldMouseX;
		double oldMouseY;
		float mouseSensitivity;
		//float YModelOffset;
		Object* skybox;
		PhysicsObject* playerModel;

	public:
		Player();
		Player(Camera* camera);
		~Player();

		void EnableMovementControls();
		void DisableMovementControls();
		glm::mat4 GetViewTransformMatrix();
		void LookAt(double xpos, double ypos);
		void MoveForward(float delta);
		void MoveBackward(float delta);
		void StrafeLeft(float delta);
		void StrafeRight(float delta);
		void MoveUp(float delta);
		void MoveDown(float delta);
		void Follow(PhysicsObject* obj);
		void FollowMesh(Mesh* obj);
		void BringWith(PhysicsObject* obj);
		void BringWithMesh(Mesh* obj);
		void ChangeMovementSpeed(float newSpeed);

		void SetYModelOffset(float value);

		void SetSkybox(Object* newSkybox);
		void SetPlayerModel(PhysicsObject* newModel);

		Object* GetSkybox();
		PhysicsObject* GetPlayerModel();
		glm::vec3 GetTranslation();
		glm::vec2 GetOldMousePos();
		glm::vec3 GetViewDirection();
	};
}
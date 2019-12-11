#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Object.h"

namespace Atlas {

	class Camera {
	public:
		bool hasControls;
		float movementSpeed;
		glm::vec3 viewDirection;
		glm::vec3 upDirection;
		glm::vec3 cameraTranslation;
		double oldMouseX;
		double oldMouseY;
		float mouseSensitivity;
		Object* skybox;
	public:
		Camera();
		Camera(bool canControl, float movementSpeed, glm::vec3 startingLookDirection, glm::vec3 startingUpDirection, glm::vec3 startingCameraTranslation, float mouseSensitivity, Object* skyboxObj);
		~Camera();

		void EnableMovementControls();
		void DisableMovementControls();
		glm::mat4 GetViewTransformMatrix();
		void LookAt(double xpos, double ypos);
		virtual void MoveForward(float delta);
		virtual void MoveBackward(float delta);
		virtual void StrafeLeft(float delta);
		virtual void StrafeRight(float delta);
		virtual void MoveUp(float delta);
		virtual void MoveDown(float delta);
		virtual void Follow(Mesh* obj);
		virtual void BringWith(Mesh* obj);
		void ChangeMovementSpeed(float newSpeed);
		glm::vec3 GetTranslation();
		glm::vec2 GetOldMousePos();
		void SetSkybox(Object* newSkybox);
		Object* GetSkybox();

		static void SetFocus(Camera* cam);
	};
}
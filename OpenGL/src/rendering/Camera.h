#pragma once

#include "glm/glm.hpp"
#include "Mesh.h"

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
public:
	Camera();
	Camera(bool canControl, float movementSpeed, glm::vec3 startingLookDirection, glm::vec3 startingUpDirection, glm::vec3 startingCameraTranslation, float mouseSensitivity);
	~Camera();
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
	void ChangeMovementSpeed(float newSpeed);
	void BringWith(Mesh &obj);
	glm::vec3 GetTranslation();
};
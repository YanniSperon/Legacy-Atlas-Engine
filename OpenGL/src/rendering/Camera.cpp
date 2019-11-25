#include "Camera.h"
#include "Config.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Atlas {
	Camera::Camera()
		: hasControls(false), movementSpeed(0.1f), viewDirection(0.0f, 0.0f, -1.0f), upDirection(0.0f, 1.0f, 0.0f), cameraTranslation(0.0f, 0.0f, 0.0f), oldMouseX(0.0), oldMouseY(0.0), mouseSensitivity(0.0f)
	{

	}

	Camera::Camera(bool canControl, float movementSpeed, glm::vec3 startingLookDirection, glm::vec3 startingUpDirection, glm::vec3 startingCameraTranslation, float mouseSensitivity)
		: hasControls(canControl), movementSpeed(movementSpeed), viewDirection(startingLookDirection), upDirection(startingUpDirection),
		cameraTranslation(startingCameraTranslation), oldMouseX(0.0), oldMouseY(0.0), mouseSensitivity(mouseSensitivity)
	{

	}

	Camera::~Camera()
	{

	}

	void Camera::EnableMovementControls()
	{
		hasControls = true;
	}

	void Camera::DisableMovementControls()
	{
		hasControls = false;
	}

	glm::mat4 Camera::GetViewTransformMatrix()
	{
		return glm::lookAt(cameraTranslation, cameraTranslation + viewDirection, upDirection);
	}

	void Camera::LookAt(double xpos, double ypos)
	{
		if (hasControls) {
			glm::vec2 mouseDelta(xpos - oldMouseX, ypos - oldMouseY);

			glm::vec3 toRotateAround = glm::cross(viewDirection, upDirection);
			glm::vec3 vd;
			viewDirection = glm::mat3(
				glm::rotate(glm::mat4(1.0f), -glm::radians(mouseDelta.x * mouseSensitivity), upDirection) *
				glm::rotate(glm::mat4(1.0f), -glm::radians(mouseDelta.y * mouseSensitivity), toRotateAround)
			) * viewDirection;

			viewDirection = glm::mat3() * viewDirection;

			oldMouseX = xpos;
			oldMouseY = ypos;
		}
	}

	void Camera::MoveForward(float delta)
	{
		if (hasControls) {
			glm::vec2 normalizedViewDirection = glm::normalize(glm::vec2(viewDirection.x, viewDirection.z));
			cameraTranslation.x += movementSpeed * normalizedViewDirection.x * delta;
			cameraTranslation.z += movementSpeed * normalizedViewDirection.y * delta;
		}
	}

	void Camera::MoveBackward(float delta)
	{
		if (hasControls) {
			glm::vec2 normalizedViewDirection = glm::normalize(glm::vec2(viewDirection.x, viewDirection.z));
			cameraTranslation.x += -movementSpeed * normalizedViewDirection.x * delta;
			cameraTranslation.z += -movementSpeed * normalizedViewDirection.y * delta;
		}
	}

	void Camera::StrafeLeft(float delta)
	{
		if (hasControls) {
			glm::vec3 strafeDirection = glm::cross(viewDirection, upDirection);
			glm::vec2 normalizedStrafeDirection = glm::normalize(glm::vec2(strafeDirection.x, strafeDirection.z));
			cameraTranslation.x += -movementSpeed * normalizedStrafeDirection.x * delta;
			cameraTranslation.z += -movementSpeed * normalizedStrafeDirection.y * delta;
		}
	}

	void Camera::StrafeRight(float delta)
	{
		if (hasControls) {
			glm::vec3 strafeDirection = glm::cross(viewDirection, upDirection);
			glm::vec2 normalizedStrafeDirection = glm::normalize(glm::vec2(strafeDirection.x, strafeDirection.z));
			cameraTranslation.x += movementSpeed * normalizedStrafeDirection.x * delta;
			cameraTranslation.z += movementSpeed * normalizedStrafeDirection.y * delta;
		}
	}

	void Camera::MoveUp(float delta)
	{
		if (hasControls) {
			cameraTranslation += movementSpeed * upDirection * delta;
		}
	}

	void Camera::MoveDown(float delta)
	{
		if (hasControls) {
			cameraTranslation += -movementSpeed * upDirection * delta;
		}
	}

	void Camera::ChangeMovementSpeed(float newSpeed)
	{
		movementSpeed = newSpeed;
	}

	void Camera::BringWith(Mesh& obj)
	{
		obj.TranslateVec3(cameraTranslation);
	}

	void Camera::BringWith(Mesh* obj)
	{
		obj->TranslateVec3(cameraTranslation);
	}

	glm::vec3 Camera::GetTranslation()
	{
		return cameraTranslation;
	}
}
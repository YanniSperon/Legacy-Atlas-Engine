#include "Camera.h"
#include "Global.h"
#include "Config.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Atlas {

	Camera::Camera()
		: hasControls(false), movementSpeed(0.1f), viewDirection(0.0f, 0.0f, -1.0f), upDirection(0.0f, 1.0f, 0.0f), cameraTranslation(0.0f, 0.0f, 0.0f), oldMouseX(36000000.0), oldMouseY(0.0), mouseSensitivity(0.0f), skybox(NULL), hasLookControls(true)
	{

	}

	Camera::Camera(bool canControl, float movementSpeed, glm::vec3 startingLookDirection, glm::vec3 startingUpDirection, glm::vec3 startingCameraTranslation, float mouseSensitivity, Object* skyboxObj)
		: hasControls(canControl), movementSpeed(movementSpeed), viewDirection(startingLookDirection), upDirection(startingUpDirection), skybox(skyboxObj), cameraTranslation(startingCameraTranslation), oldMouseX(36000000.0), oldMouseY(0.0), mouseSensitivity(mouseSensitivity), hasLookControls(true)
	{

	}

	Camera::~Camera()
	{
		delete skybox;
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
		if (hasLookControls) {
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
			if (skybox != NULL) {
				skybox->TranslateVec3(cameraTranslation);
			}
		}
	}

	void Camera::MoveBackward(float delta)
	{
		if (hasControls) {
			glm::vec2 normalizedViewDirection = glm::normalize(glm::vec2(viewDirection.x, viewDirection.z));
			cameraTranslation.x += -movementSpeed * normalizedViewDirection.x * delta;
			cameraTranslation.z += -movementSpeed * normalizedViewDirection.y * delta;
			if (skybox != NULL) {
				skybox->TranslateVec3(cameraTranslation);
			}
		}
	}

	void Camera::StrafeLeft(float delta)
	{
		if (hasControls) {
			glm::vec3 strafeDirection = glm::cross(viewDirection, upDirection);
			glm::vec2 normalizedStrafeDirection = glm::normalize(glm::vec2(strafeDirection.x, strafeDirection.z));
			cameraTranslation.x += -movementSpeed * normalizedStrafeDirection.x * delta;
			cameraTranslation.z += -movementSpeed * normalizedStrafeDirection.y * delta;
			if (skybox != NULL) {
				skybox->TranslateVec3(cameraTranslation);
			}
		}
	}

	void Camera::StrafeRight(float delta)
	{
		if (hasControls) {
			glm::vec3 strafeDirection = glm::cross(viewDirection, upDirection);
			glm::vec2 normalizedStrafeDirection = glm::normalize(glm::vec2(strafeDirection.x, strafeDirection.z));
			cameraTranslation.x += movementSpeed * normalizedStrafeDirection.x * delta;
			cameraTranslation.z += movementSpeed * normalizedStrafeDirection.y * delta;
			if (skybox != NULL) {
				skybox->TranslateVec3(cameraTranslation);
			}
		}
	}

	void Camera::MoveUp(float delta)
	{
		if (hasControls) {
			cameraTranslation += movementSpeed * upDirection * delta;
			if (skybox != NULL) {
				skybox->TranslateVec3(cameraTranslation);
			}
		}
	}

	void Camera::MoveDown(float delta)
	{
		if (hasControls) {
			cameraTranslation += -movementSpeed * upDirection * delta;
			if (skybox != NULL) {
				skybox->TranslateVec3(cameraTranslation);
			}
		}
	}

	void Camera::Follow(Mesh* obj)
	{
		cameraTranslation = obj->GetTranslation();
		if (skybox != NULL) {
			skybox->TranslateVec3(cameraTranslation);
		}
	}

	void Camera::ChangeMovementSpeed(float newSpeed)
	{
		movementSpeed = newSpeed;
	}

	void Camera::BringWith(Mesh* obj)
	{
		obj->TranslateVec3(cameraTranslation);
	}

	glm::vec3 Camera::GetTranslation()
	{
		return cameraTranslation;
	}

	glm::vec2 Camera::GetOldMousePos()
	{
		return glm::vec2(oldMouseX, oldMouseY);
	}

	void Camera::SetSkybox(Object* newSkybox)
	{
		skybox = newSkybox;
	}

	Object* Camera::GetSkybox()
	{
		return skybox;
	}

	void Camera::SetHasLookControls(bool newValue)
	{
		hasLookControls = newValue;
	}

	void Camera::SetFocus(Camera* cam)
	{
		Object* tempSkybox = Global::Variables.activeCamera->GetSkybox();
		cam->SetSkybox(tempSkybox);
		Global::Variables.activeCamera->SetSkybox(NULL);
		Global::Variables.activeCamera = cam;
		cam->SetSkybox(tempSkybox);
		glm::vec2 temp = Global::Variables.activeCamera->GetOldMousePos();
		glfwSetCursorPos(Global::Variables.window, temp.x, temp.y);
	}
	bool Camera::GetHasControls()
	{
		return hasControls;
	}
	bool Camera::GetHasLookControls()
	{
		return hasLookControls;
	}
	float Camera::GetMovementSpeed()
	{
		return movementSpeed;
	}
	glm::vec3 Camera::GetViewDirection()
	{
		return viewDirection;
	}
	glm::vec3 Camera::GetUpDirection()
	{
		return upDirection;
	}
	float Camera::GetMouseSensitivity()
	{
		return mouseSensitivity;
	}
}
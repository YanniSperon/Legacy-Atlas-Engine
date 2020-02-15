#include "Player.h"
#include "Convert.h"
#include "PhysicsEngine.h"
#include "System.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Atlas {

	Player::Player()
		: hasControls(false), movementSpeed(0.1f), viewDirection(0.0f, 0.0f, -1.0f), upDirection(0.0f, 1.0f, 0.0f), cameraTranslation(0.0f, 0.0f, 0.0f), oldMouseX(36000000.0), oldMouseY(0.0), mouseSensitivity(0.0f), skybox(NULL)
	{

	}

	Player::Player(Camera* camera)
		: hasControls(camera->GetHasControls()), movementSpeed(camera->GetMovementSpeed()), viewDirection(camera->GetViewDirection()), upDirection(camera->GetUpDirection()), skybox(camera->GetSkybox()), cameraTranslation(camera->GetTranslation()), oldMouseX(camera->GetOldMousePos().x), oldMouseY(camera->GetOldMousePos().y), mouseSensitivity(camera->GetMouseSensitivity())
	{
		playerModel = new PhysicsObject(new Object(type::cubeModel, "", "", "res/images/textures/", "newcow.png", "res/shaders/", "Lighting.shader", true, true, System::GenerateUniqueID(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 2.0f, 1.0f)), 100.0f);
	}

	Player::~Player()
	{
		delete playerModel;
	}

	void Player::EnableMovementControls()
	{
		hasControls = true;
	}

	void Player::DisableMovementControls()
	{
		hasControls = false;
	}

	glm::mat4 Player::GetViewTransformMatrix()
	{
		return glm::lookAt(cameraTranslation, cameraTranslation + viewDirection, upDirection);
	}

	void Player::LookAt(double xpos, double ypos)
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

	void Player::MoveForward(float delta)
	{
		if (hasControls) {
			glm::vec2 normalizedViewDirection = glm::normalize(glm::vec2(viewDirection.x, viewDirection.z));
			cameraTranslation.x += movementSpeed * normalizedViewDirection.x * delta;
			cameraTranslation.z += movementSpeed * normalizedViewDirection.y * delta;
			if (skybox != NULL) {
				skybox->TranslateVec3(cameraTranslation);
			}
			if (playerModel != NULL) {
				BringWith(playerModel);
			}
		}
	}

	void Player::MoveBackward(float delta)
	{
		if (hasControls) {
			glm::vec2 normalizedViewDirection = glm::normalize(glm::vec2(viewDirection.x, viewDirection.z));
			cameraTranslation.x += -movementSpeed * normalizedViewDirection.x * delta;
			cameraTranslation.z += -movementSpeed * normalizedViewDirection.y * delta;
			if (skybox != NULL) {
				skybox->TranslateVec3(cameraTranslation);
			}
			if (playerModel != NULL) {
				BringWith(playerModel);
			}
		}
	}

	void Player::StrafeLeft(float delta)
	{
		if (hasControls) {
			glm::vec3 strafeDirection = glm::cross(viewDirection, upDirection);
			glm::vec2 normalizedStrafeDirection = glm::normalize(glm::vec2(strafeDirection.x, strafeDirection.z));
			cameraTranslation.x += -movementSpeed * normalizedStrafeDirection.x * delta;
			cameraTranslation.z += -movementSpeed * normalizedStrafeDirection.y * delta;
			if (skybox != NULL) {
				skybox->TranslateVec3(cameraTranslation);
			}
			if (playerModel != NULL) {
				BringWith(playerModel);
			}
		}
	}

	void Player::StrafeRight(float delta)
	{
		if (hasControls) {
			glm::vec3 strafeDirection = glm::cross(viewDirection, upDirection);
			glm::vec2 normalizedStrafeDirection = glm::normalize(glm::vec2(strafeDirection.x, strafeDirection.z));
			cameraTranslation.x += movementSpeed * normalizedStrafeDirection.x * delta;
			cameraTranslation.z += movementSpeed * normalizedStrafeDirection.y * delta;
			if (skybox != NULL) {
				skybox->TranslateVec3(cameraTranslation);
			}
			if (playerModel != NULL) {
				BringWith(playerModel);
			}
		}
	}

	void Player::MoveUp(float delta)
	{
		if (hasControls) {
			cameraTranslation += movementSpeed * upDirection * delta;
			if (skybox != NULL) {
				skybox->TranslateVec3(cameraTranslation);
			}
			if (playerModel != NULL) {
				BringWith(playerModel);
			}
		}
	}

	void Player::MoveDown(float delta)
	{
		if (hasControls) {
			cameraTranslation += -movementSpeed * upDirection * delta;
			if (skybox != NULL) {
				skybox->TranslateVec3(cameraTranslation);
			}
			if (playerModel != NULL) {
				BringWith(playerModel);
			}
		}
	}

	void Player::Follow(PhysicsObject* obj)
	{
		cameraTranslation = obj->GetTranslation();
		if (skybox != NULL) {
			skybox->TranslateVec3(cameraTranslation);
		}
		if (playerModel != NULL) {
			BringWith(playerModel);
		}
	}
	
	void Player::FollowMesh(Mesh* obj)
	{
		cameraTranslation = obj->GetTranslation();
		if (skybox != NULL) {
			skybox->TranslateVec3(cameraTranslation);
		}
	}

	void Player::ChangeMovementSpeed(float newSpeed)
	{
		movementSpeed = newSpeed;
	}

	void Player::BringWith(PhysicsObject* obj)
	{
		obj->TranslateVec3(cameraTranslation);
		btRigidBody* body = btRigidBody::upcast(obj->GetPhysicsObject());
		if (body != NULL) {
			body->setLinearVelocity(btVector3(0.0, 0.0, 0.0));
		}
		obj->InverseUpdate();
	}

	void Player::BringWithMesh(Mesh* obj)
	{
		obj->TranslateVec3(cameraTranslation);
	}

	void Player::SetYModelOffset(float value)
	{
		//YModelOffset = value;
	}

	glm::vec3 Player::GetTranslation()
	{
		return cameraTranslation;
	}

	glm::vec2 Player::GetOldMousePos()
	{
		return glm::vec2(oldMouseX, oldMouseY);
	}

	glm::vec3 Player::GetViewDirection()
	{
		return viewDirection;
	}

	void Player::SetSkybox(Object* newSkybox)
	{
		skybox = newSkybox;
	}

	Object* Player::GetSkybox()
	{
		return skybox;
	}

	void Player::SetPlayerModel(PhysicsObject* newModel)
	{
		playerModel = newModel;
	}

	PhysicsObject* Player::GetPlayerModel()
	{
		return playerModel;
	}
}
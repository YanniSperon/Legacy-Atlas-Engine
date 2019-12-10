#include "Player.h"
#include "Convert.h"
#include "PhysicsEngine.h"

namespace Atlas {

	Player::Player()
		: Camera(), Object()
	{

	}

	Player::Player(bool canControl, float movementSpeed, glm::vec3 startingLookDirection, glm::vec3 startingUpDirection, float camYOffset, float mouseSensitivity, type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderFileName, bool glInit, bool lighting, bool hasPhysics, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, float mass, Material mat)
		: Camera(canControl, movementSpeed, startingLookDirection, startingUpDirection, trans + camYOffset, mouseSensitivity), Object(type, meshDir, meshName, texDir, texName, shaderDir, shaderFileName, glInit, lighting, hasPhysics, rot, trans, s, mass, mat), cameraYOffset(cameraYOffset)
	{

	}

	Player::~Player()
	{

	}

	void Player::Update()
	{
		printf("UPDATING PLAYER\n");
		if (GetPhysicsObject() != NULL) {
			glm::vec3 tempTrans = Convert::Vector3(GetPhysicsObject()->getWorldTransform().getOrigin());
			TranslateVec3(tempTrans);
			glm::vec3 tempRot = glm::vec3(0.0f, 0.0f, 0.0f);
			GetPhysicsObject()->getWorldTransform().getRotation().getEulerZYX(tempRot.z, tempRot.y, tempRot.x);
			RotateVec3(tempRot);
			printf("UPDATED TO (%f, %f, %f), LOOKING AT (%f, %f, %f)\n", tempTrans.x, tempTrans.y, tempTrans.z, tempRot.x, tempRot.y, tempRot.z);
			cameraTranslation = tempTrans;
			cameraTranslation.y -= cameraYOffset;
		}
	}

	void Player::MoveForward(float delta)
	{
		if (hasControls) {
			glm::vec2 normalizedViewDirection = glm::normalize(glm::vec2(viewDirection.x, viewDirection.z));
			glm::vec3 moveAmt;
			moveAmt.x += movementSpeed * normalizedViewDirection.x * delta;
			moveAmt.z += movementSpeed * normalizedViewDirection.y * delta;
			cameraTranslation += moveAmt;
			BringWith(this);
			//cameraTranslation.x += movementSpeed * normalizedViewDirection.x * delta;
			//cameraTranslation.z += movementSpeed * normalizedViewDirection.y * delta;
			//TranslateAddVec3(moveAmt);
			//Follow(this);
			//BringWith(this);
			//btRigidBody* body = btRigidBody::upcast(GetPhysicsObject());
			//body->clearForces();
			//body->setLinearVelocity(btVector3(movementSpeed * normalizedViewDirection.x * delta, 0.0f, movementSpeed * normalizedViewDirection.y * delta));
			//Follow(this);
		}
	}
	
	void Player::MoveBackward(float delta)
	{
		if (hasControls) {
			glm::vec2 normalizedViewDirection = glm::normalize(glm::vec2(viewDirection.x, viewDirection.z));
			cameraTranslation.x += -movementSpeed * normalizedViewDirection.x * delta;
			cameraTranslation.z += -movementSpeed * normalizedViewDirection.y * delta;
			BringWith(this);
			Update();
		}
	}
	
	void Player::StrafeLeft(float delta)
	{
		if (hasControls) {
			glm::vec3 strafeDirection = glm::cross(viewDirection, upDirection);
			glm::vec2 normalizedStrafeDirection = glm::normalize(glm::vec2(strafeDirection.x, strafeDirection.z));
			cameraTranslation.x += -movementSpeed * normalizedStrafeDirection.x * delta;
			cameraTranslation.z += -movementSpeed * normalizedStrafeDirection.y * delta;
			BringWith(this);
			Update();
		}
	}
	
	void Player::StrafeRight(float delta)
	{
		if (hasControls) {
			glm::vec3 strafeDirection = glm::cross(viewDirection, upDirection);
			glm::vec2 normalizedStrafeDirection = glm::normalize(glm::vec2(strafeDirection.x, strafeDirection.z));
			cameraTranslation.x += movementSpeed * normalizedStrafeDirection.x * delta;
			cameraTranslation.z += movementSpeed * normalizedStrafeDirection.y * delta;
			BringWith(this);
			Update();
		}
	}
	
	void Player::MoveUp(float delta)
	{
		if (hasControls) {
			cameraTranslation += movementSpeed * upDirection * delta;
			BringWith(this);
			Update();
		}
	}
	
	void Player::MoveDown(float delta)
	{
		if (hasControls) {
			cameraTranslation += -movementSpeed * upDirection * delta;
			BringWith(this);
			Update();
		}
	}

	void Player::Follow(Mesh* obj)
	{
		cameraTranslation = obj->GetTranslation();
		cameraTranslation.y += cameraYOffset;
	}

	void Player::BringWith(Mesh* obj)
	{
		glm::vec3 temp = cameraTranslation;
		temp.y -= cameraYOffset;
		obj->TranslateVec3(temp);
	}
}
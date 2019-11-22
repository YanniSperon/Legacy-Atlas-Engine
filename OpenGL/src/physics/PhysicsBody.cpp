#include "PhysicsBody.h"

namespace Engine {
	PhysicsBody::PhysicsBody()
		: Object(), mass(0.0f), linearVelocity(0.0f, 0.0f, 0.0f), force(0.0f, 0.0f, 0.0f), angularVelocity(0.0f, 0.0f, 0.0f), torque(0.0f, 0.0f, 0.0f), momentOfInertia(0.0f), gravitationalForce(0.0f)
	{

	}

	PhysicsBody::PhysicsBody(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, glm::vec3 rotation, glm::vec3 translation, glm::vec3 s, GLuint tex, GLuint shader, Material mat, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity, bool glInit, bool lighting)
		: Object(minCorner, maxCorner, type, dir, name, rotation, translation, s, tex, shader, mat, glInit, lighting), mass(m), linearVelocity(linearVel), force(f), angularVelocity(angularVel), torque(t), momentOfInertia(MOI), gravitationalForce(gravity)
	{

	}

	void PhysicsBody::Update(float delta)
	{
		linearVelocity += (gravitationalForce * delta) + ((force / mass) * delta);
		angularVelocity += (torque / momentOfInertia) * delta;
		TranslateAddVec3(linearVelocity * delta);
		RotateAddVec3(angularVelocity * delta);

		glm::vec3 tempLin = ((force + gravitationalForce) * delta) / (mass * 2.0f);
		TranslateVec3((tempLin + linearVelocity) * delta);
		linearVelocity += tempLin * 2.0f;

		glm::vec3 tempAng = (torque * delta) / (momentOfInertia * 2.0f);
		RotateVec3((tempAng + angularVelocity) * delta);
		angularVelocity += tempLin * 2.0f;
	}

	Position PhysicsBody::UpdateValues(float deltaT, Position oldPosition)
	{
		Position newPosition = oldPosition;
		glm::vec3 tempLin = ((newPosition.force + newPosition.gravitationalForce) * deltaT) / (mass * 2.0f);
		newPosition.translation = (tempLin + newPosition.linearVel) * deltaT;
		newPosition.linearVel += tempLin * 2.0f;

		glm::vec3 tempAng = (newPosition.torque * deltaT) / (newPosition.momentOfInertia * 2.0f);
		newPosition.rotation = (tempAng + newPosition.angularVel) * deltaT;
		newPosition.angularVel += tempLin * 2.0f;

		return newPosition;
	}

	void PhysicsBody::Stop()
	{
		linearVelocity = angularVelocity = force = torque = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	glm::vec3 PhysicsBody::GetLinearAccelerationWithoutGravity()
	{
		return glm::vec3(force / mass);
	}

	float PhysicsBody::GetMass()
	{
		return mass;
	}

	glm::vec3 PhysicsBody::GetGravitationalForce()
	{
		return gravitationalForce;
	}

	glm::vec3 PhysicsBody::GetLinearVelocity()
	{
		return linearVelocity;
	}

	glm::vec3 PhysicsBody::GetAngularVelocity()
	{
		return angularVelocity;
	}

	glm::vec3 PhysicsBody::GetForce()
	{
		return force;
	}

	glm::vec3 PhysicsBody::GetTorque()
	{
		return torque;
	}

	float PhysicsBody::GetMomentOfInertia()
	{
		return momentOfInertia;
	}

	std::string PhysicsBody::GetType()
	{
		return "PhysicsBody";
	}

	glm::vec3 PhysicsBody::GetLinearAcceleration()
	{
		return glm::vec3((force + gravitationalForce) / mass);
	}
}
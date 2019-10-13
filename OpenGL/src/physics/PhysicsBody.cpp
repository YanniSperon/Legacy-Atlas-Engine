#include "PhysicsBody.h"

PhysicsBody::PhysicsBody()
	: Object(), mass(0.0f), linearVelocity(0.0f, 0.0f, 0.0f), force(0.0f, 0.0f, 0.0f), angularVelocity(0.0f, 0.0f, 0.0f), torque(0.0f, 0.0f, 0.0f), momentOfInertia(0.0f), gravitationalAcceleration(0.0f)
{

}

PhysicsBody::PhysicsBody(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, glm::vec3 rotation, glm::vec3 translation, glm::vec3 s,GLuint tex, GLuint shader, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity)
	: Object(minCorner, maxCorner, type, dir, name, rotation, translation, s, tex, shader), mass(m), linearVelocity(linearVel), force(f), angularVelocity(angularVel), torque(t), momentOfInertia(MOI), gravitationalAcceleration(gravity)
{

}

void PhysicsBody::Update(float delta)
{
	glm::vec3 translation = GetTranslation();
	if (translation.y < -50.0f) {
		TranslateVec3(glm::vec3(translation.x, 50.0f, translation.z));
	}
	if (translation.x > 50.0f) {
		TranslateVec3(glm::vec3(-50.0f, translation.y, translation.z));
	}
	linearVelocity += (gravitationalAcceleration * delta) + ((force/mass) * delta);
	angularVelocity += (torque / momentOfInertia) * delta;
	TranslateAddVec3(linearVelocity * delta);
	RotateAddVec3(angularVelocity * delta);
}

void PhysicsBody::Stop()
{
	linearVelocity = angularVelocity = force = torque = glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::vec3 PhysicsBody::GetLinearAccelerationWithoutGravity()
{
	return glm::vec3(force / mass);
}

glm::vec3 PhysicsBody::GetLinearVelocity()
{
	return linearVelocity;
}

glm::vec3 PhysicsBody::GetLinearAcceleration()
{
	return glm::vec3(force / mass) + gravitationalAcceleration;
}

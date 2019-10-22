#pragma once
#include "Object.h"
#include "glm/glm.hpp"

struct Position {
	glm::vec3 translation, rotation, scale, linearVel, force, angularVel, torque, gravitationalForce;
	float mass, momentOfInertia;
};

class PhysicsBody : public Object {
private:
	float mass;
	glm::vec3 gravitationalForce;
	glm::vec3 linearVelocity;
	glm::vec3 angularVelocity;
	glm::vec3 force;
	glm::vec3 torque;
	float momentOfInertia;
public:
	PhysicsBody();
	PhysicsBody(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, glm::vec3 rotation, glm::vec3 translation, glm::vec3 s, GLuint tex, GLuint shader, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity);

	void Update(float delta);
	Position UpdateValues(float deltaT, Position oldPosition);

	void Stop();

	glm::vec3 GetLinearAcceleration();
	glm::vec3 GetLinearAccelerationWithoutGravity();
	glm::vec3 GetLinearVelocity();

	inline const glm::vec3& GetVelocity() const { return linearVelocity; }
};
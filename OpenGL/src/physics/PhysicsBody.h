#pragma once
#include "Object.h"
#include "glm/glm.hpp"

namespace Atlas {
	struct Position {
		glm::vec3 translation, rotation, scale, linearVel, force, angularVel, torque, gravitationalForce;
		float mass, momentOfInertia;
	};

	class PhysicsBody : public Atlas::Object {
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
		PhysicsBody(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderName, bool glInit, bool hasLighting, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, Material mat, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity);

		void Update(float delta);
		Position UpdateValues(float deltaT, Position oldPosition);

		void Stop();

		glm::vec3 GetLinearAcceleration();
		glm::vec3 GetLinearAccelerationWithoutGravity();
		float GetMass();
		glm::vec3 GetGravitationalForce();
		glm::vec3 GetLinearVelocity();
		glm::vec3 GetAngularVelocity();
		glm::vec3 GetForce();
		glm::vec3 GetTorque();
		float GetMomentOfInertia();

		inline const glm::vec3& GetVelocity() const { return linearVelocity; }

		virtual std::string GetType() override;
	};
}
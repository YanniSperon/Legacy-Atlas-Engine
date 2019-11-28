#pragma once

#include "AxisAlignedBoundingBox.h"
#include "PhysicsBody.h"

namespace Atlas {

	class AABBCollidable : public AxisAlignedBoundingBox, public PhysicsBody {
	private:

	public:
		AABBCollidable();
		AABBCollidable(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderName, bool glInit, bool hasLighting, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, Material mat, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity);

		virtual std::string GetType() override;
	};
}
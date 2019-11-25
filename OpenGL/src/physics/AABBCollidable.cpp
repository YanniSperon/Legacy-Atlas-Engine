#include "AABBCollidable.h"

namespace Atlas {
	AABBCollidable::AABBCollidable()
		: AxisAlignedBoundingBox(), PhysicsBody()
	{

	}

	AABBCollidable::AABBCollidable(const glm::vec3& minCorner, const glm::vec3& maxCorner, type type, std::string dir, std::string name, glm::vec3 rotation, glm::vec3 translation, glm::vec3 s, GLuint tex, GLuint shader, Material mat, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity, bool glInit, bool lighting)
		: AxisAlignedBoundingBox(minCorner, maxCorner), PhysicsBody(minCorner, maxCorner, type, dir, name, rotation, translation, s, tex, shader, mat, m, linearVel, angularVel, f, t, MOI, gravity, glInit, lighting)
	{

	}

	std::string AABBCollidable::GetType()
	{
		return "AABBCollidable";
	}
}
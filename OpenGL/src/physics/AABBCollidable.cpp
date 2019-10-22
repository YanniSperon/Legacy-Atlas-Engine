#include "AABBCollidable.h"

AABBCollidable::AABBCollidable()
	: AxisAlignedBoundingBox(), PhysicsBody()
{

}

AABBCollidable::AABBCollidable(const glm::vec3& minCorner, const glm::vec3& maxCorner, type type, std::string dir, std::string name, glm::vec3 rotation, glm::vec3 translation, glm::vec3 s, GLuint tex, GLuint shader, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity)
	: AxisAlignedBoundingBox(minCorner, maxCorner), PhysicsBody(minCorner, maxCorner, type, dir, name, rotation, translation, s, tex, shader, m, linearVel, angularVel, f, t, MOI, gravity)
{

}
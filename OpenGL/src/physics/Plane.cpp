#include "Plane.h"

Plane::Plane()
	: normal(0.0f, 0.0f, 0.0f), distance(0.0f)
{

}

Plane::Plane(const glm::vec3& norm, float dist)
	: normal(norm), distance(dist)
{

}

Plane::~Plane()
{

}

Plane Plane::Normalized() const
{
	float magnitude = sqrtf((normal.x * normal.x) + (normal.y * normal.y) + (normal.z * normal.z));

	return Plane(normal / magnitude, distance / magnitude);
}

IntersectData Plane::IntersectSphere(const BoundingSphere& other) const
{
	float distanceFromSphereCenter = fabs(glm::dot(normal, other.GetCenter()) + distance);
	float distanceFromSphere = distanceFromSphereCenter - other.GetRadius();

	return IntersectData(distanceFromSphere < 0, distanceFromSphere);
}
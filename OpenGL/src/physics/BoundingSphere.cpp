#include "BoundingSphere.h"

BoundingSphere::BoundingSphere()
	: center(0.0f, 0.0f, 0.0f), radius(1.0f)
{

}

BoundingSphere::BoundingSphere(const glm::vec3 center, float radius)
	: center(center), radius(radius)
{

}

BoundingSphere::~BoundingSphere()
{

}

IntersectData BoundingSphere::IntersectBoundingSphere(const BoundingSphere& other)
{
	float radiusDistance = radius + other.radius;
	float centerToCenterDistance = sqrtf(((other.center.x - center.x) * (other.center.x - center.x)) + ((other.center.y - center.y) * (other.center.y - center.y)) + ((other.center.z - center.z) * (other.center.z - center.z)));
	float distance = centerToCenterDistance - radiusDistance;
	return IntersectData(centerToCenterDistance < radiusDistance, distance);
}

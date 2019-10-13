#include "AxisAlignedBoundingBox.h"

glm::vec3 Max(const glm::vec3 first, const glm::vec3 second) {
	glm::vec3 answer;
	if (first.x > second.x) {
		answer.x = first.x;
	}
	else {
		answer.x = second.x;
	}

	if (first.y > second.y) {
		answer.y = first.y;
	}
	else {
		answer.y = second.y;
	}

	if (first.z > second.z) {
		answer.z = first.z;
	}
	else {
		answer.z = second.z;
	}
	return answer;
}

float MaxValue(const glm::vec3 vec) {
	float maxVal = vec[0];
	for (unsigned int i = 0; i < 3; i++) {
		if (vec[i] > maxVal) {
			maxVal = vec[i];
		}
	}
	return maxVal;
}

AxisAlignedBoundingBox::AxisAlignedBoundingBox()
	: minExtents(0.0f, 0.0f, 0.0f), maxExtents(0.0f, 0.0f, 0.0f)
{
}

AxisAlignedBoundingBox::AxisAlignedBoundingBox(const glm::vec3& minCorner, const glm::vec3& maxCorner)
	: minExtents(minCorner), maxExtents(maxCorner)
{

}

AxisAlignedBoundingBox::~AxisAlignedBoundingBox()
{
}

IntersectData AxisAlignedBoundingBox::IntersectAxisAlignedBoundingBox(const AxisAlignedBoundingBox& other) const
{
	glm::vec3 distances1 = other.GetMinExtents() - maxExtents;
	glm::vec3 distances2 = minExtents - other.GetMaxExtents();
	glm::vec3 distances = Max(distances1, distances2);

	float maxDist = MaxValue(distances);

	return IntersectData(maxDist < 0, maxDist);
}

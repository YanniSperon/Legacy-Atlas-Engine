#pragma once

#include "glm/glm.hpp"
#include "BoundingSphere.h"

class Plane {
private:
	const glm::vec3 normal;
	const float distance;
public:
	Plane();
	Plane(const glm::vec3& norm, float dist);
	~Plane();

	Plane Normalized() const;
	IntersectData IntersectSphere(const BoundingSphere& other) const;

	inline const glm::vec3& GetNormal() const { return normal; }
	inline float GetDistance() const { return distance; }
};
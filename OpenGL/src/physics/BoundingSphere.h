#pragma once
#include "glm/glm.hpp"
#include "IntersectData.h"

class BoundingSphere {
private:
	const glm::vec3 center;
	const float radius;
public:
	BoundingSphere();
	BoundingSphere(const glm::vec3 center, float radius);
	~BoundingSphere();

	IntersectData IntersectBoundingSphere(const BoundingSphere& other);

	inline const glm::vec3& GetCenter() const { return center; }
	inline float GetRadius() const { return radius; }
};
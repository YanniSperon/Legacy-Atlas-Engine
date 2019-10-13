#pragma once

#include "glm/glm.hpp"
#include "IntersectData.h"

class AxisAlignedBoundingBox {
private:
	const glm::vec3 minExtents;
	const glm::vec3 maxExtents;
public:
	AxisAlignedBoundingBox();
	AxisAlignedBoundingBox(const glm::vec3& minCorner, const glm::vec3& maxCorner);
	~AxisAlignedBoundingBox();

	IntersectData IntersectAxisAlignedBoundingBox(const AxisAlignedBoundingBox& other) const;

	inline const glm::vec3& GetMinExtents() const { return minExtents; }
	inline const glm::vec3& GetMaxExtents() const { return maxExtents; }
};
#include "IntersectData.h"

namespace Atlas {
	IntersectData::IntersectData()
		: doesIntersect(false), distance(0.0f)
	{
	}

	IntersectData::IntersectData(const bool intersects, const float dist)
		: doesIntersect(intersects), distance(dist)
	{

	}
}
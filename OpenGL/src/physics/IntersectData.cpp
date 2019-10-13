#include "IntersectData.h"

IntersectData::IntersectData()
	: doesIntersect(false), distance(0.0f)
{
}

IntersectData::IntersectData(const bool intersects, const float dist)
	: doesIntersect(intersects), distance(dist)
{

}

IntersectData::~IntersectData()
{
}

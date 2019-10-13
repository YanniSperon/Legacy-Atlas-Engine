#pragma once

class IntersectData {
private:
	const bool doesIntersect;
	const float distance;
public:
	IntersectData();
	IntersectData(const bool intersects, const float dist);
	~IntersectData();

	inline bool GetDoesIntersect() const { return doesIntersect; }
	inline float GetDistance() const { return distance; }
};
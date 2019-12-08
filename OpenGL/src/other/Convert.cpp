#include "Convert.h"

namespace Atlas {

	glm::vec3 Convert::Vector3(const btVector3& vec)
	{
		return glm::vec3(vec[0], vec[1], vec[2]);
	}

	btVector3 Convert::Vector3(const glm::vec3& vec)
	{
		return btVector3(vec[0], vec[1], vec[2]);
	}
}
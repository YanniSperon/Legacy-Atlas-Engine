#pragma once

#include "btBulletDynamicsCommon.h"
#include "glm/glm.hpp"

namespace Atlas {
	class Convert {
	public:
		static glm::vec3 Vector3(const btVector3& vec);
		static btVector3 Vector3(const glm::vec3& vec);
	};
}
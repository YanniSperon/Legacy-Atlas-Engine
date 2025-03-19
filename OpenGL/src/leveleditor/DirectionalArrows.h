#pragma once

#include "Object.h"
#include "Renderer.h"
#include "Camera.h"

namespace Atlas {
	class DirectionalArrows {
	private:
		Object* positiveX;
		Object* positiveY;
		Object* positiveZ;
		Object* joiner;
	public:
		DirectionalArrows();
		~DirectionalArrows();

		void Submit(Renderer* renderer);
	};
}
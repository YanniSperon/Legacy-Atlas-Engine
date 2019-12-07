#pragma once
#include "Renderer.h"

namespace Atlas {

	class PostProcessor {
	public:
		static void Initialize(std::string postProcessingShaderAddress);
		static void Prepare();
		static void Render(Renderer* renderer);

		static void ChangeEffect(std::string newShaderShortenedName);
		static void Cleanup();
	};
}
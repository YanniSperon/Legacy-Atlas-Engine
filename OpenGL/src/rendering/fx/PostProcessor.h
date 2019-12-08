#pragma once
#include "Renderer.h"

namespace Atlas {

	struct MSAA {
		bool enabled;
		unsigned int value;

		MSAA() {
			enabled = false;
			value = 0;
		}
		MSAA(bool enableMSAA, int valueOfMSAA) {
			enabled = enableMSAA;
			value = valueOfMSAA;
		}
	};

	class PostProcessor {
	public:
		static void PrepareForInitialization(MSAA multisampling);
		static void Initialize(std::string postProcessingShaderAddress);
		static void PrepareForRendering();
		static void Render(Renderer* renderer);

		static void ChangeEffect(std::string newShaderShortenedName);
		static void Cleanup();
	};
}
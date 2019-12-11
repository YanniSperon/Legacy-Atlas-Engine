#pragma once
#include "Renderer.h"
#include "PhysicsRenderer.h"
#include "PhysicsScene.h"

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
		static void PrepareForRenderingPhysicsSimulation();
		static void Render(Renderer* renderer);
		static void RenderPhysicsRenderer(PhysicsRenderer* renderer, PhysicsScene* scene);

		static void ChangeEffect(std::string newShaderShortenedName);
		static void Cleanup();
	};
}
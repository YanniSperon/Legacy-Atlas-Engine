#include "DirectionalArrows.h"

#include "Global.h"

namespace Atlas {
	DirectionalArrows::DirectionalArrows()
		: positiveX(nullptr), positiveY(nullptr), positiveZ(nullptr), joiner(nullptr)
	{
		positiveX = new Object(type::normalModel, "res/models/", "positivex.obj", "res/images/colors/", "red.png", "res/shaders/", "Basic.shader", true, false, UUID(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), Material(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 32));
		positiveY = new Object(type::normalModel, "res/models/", "positivey.obj", "res/images/colors/", "green.png", "res/shaders/", "Basic.shader", true, false, UUID(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), Material(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 32));
		positiveZ = new Object(type::normalModel, "res/models/", "positivez.obj", "res/images/colors/", "blue.png", "res/shaders/", "Basic.shader", true, false, UUID(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), Material(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 32));
		joiner = new Object(type::normalModel, "res/models/", "joiner.obj", "res/images/colors/", "white.png", "res/shaders/", "Basic.shader", true, false, UUID(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), Material(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 32));
	}

	DirectionalArrows::~DirectionalArrows()
	{
		delete positiveX;
		delete positiveY;
		delete positiveZ;
		delete joiner;
	}

	void DirectionalArrows::Submit(Renderer* renderer)
	{
		if (Global::Variables.selectedObjects.size() > 0) {
			glm::vec3 total(0.0f, 0.0f, 0.0f);
			for (std::size_t i = 0; i < Global::Variables.selectedObjects.size(); ++i) {
				total += Global::Variables.selectedObjects[i]->GetTranslation();
			}
			total /= static_cast<float>(Global::Variables.selectedObjects.size());

			positiveX->TranslateVec3(total);
			positiveY->TranslateVec3(total);
			positiveZ->TranslateVec3(total);
			joiner->TranslateVec3(total);

			renderer->SubmitForceRender3D(positiveX);
			renderer->SubmitForceRender3D(positiveY);
			renderer->SubmitForceRender3D(positiveZ);
			renderer->SubmitForceRender3D(joiner);
		}
	}

}
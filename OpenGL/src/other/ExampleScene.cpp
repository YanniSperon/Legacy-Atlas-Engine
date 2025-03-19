#include "ExampleScene.h"
#include "Object.h"
#include "UUID.h"
#include "Global.h"

namespace Atlas {
	static Object* animatedLeftF22;
	static Object* animatedRightF22;
	static Object* animatedFlyingPlane;

	void ExampleScene::Create()
	{
		glm::vec3 pos(0.0f, 0.0f, 0.0f);
		glm::vec3 rot(0.0f, 0.0f, 0.0f);
		glm::vec3 sca(1.0f, 1.0f, 1.0f);

		glm::vec3 amb(0.5f, 0.5f, 0.5f);
		glm::vec3 dif(0.5f, 0.5f, 0.5f);
		glm::vec3 spe(0.5f, 0.5f, 0.5f);

		int shin = 32;



		Global::Variables.currentScene.objectsOnScene.push_back(new Object(type::normalModel, "res/models/ExampleScene/", "tankbottom.obj", "res/images/textures/ExampleScene/", "tankbottom.png", "res/shaders/", "Lighting.shader", true, true, UUID(), rot, pos, sca, Material(amb, dif, spe, shin)));
		Global::Variables.currentScene.objectsOnScene.at(Global::Variables.currentScene.objectsOnScene.size() - 1)->SetDisplayName("tank bottom");


		Global::Variables.currentScene.objectsOnScene.push_back(new Object(type::normalModel, "res/models/ExampleScene/", "tankbags.obj", "res/images/textures/ExampleScene/", "tankbags.png", "res/shaders/", "Lighting.shader", true, true, UUID(), rot, pos, sca, Material(amb, dif, spe, shin)));
		Global::Variables.currentScene.objectsOnScene.at(Global::Variables.currentScene.objectsOnScene.size() - 1)->SetDisplayName("tank bags");


		Global::Variables.currentScene.objectsOnScene.push_back(new Object(type::normalModel, "res/models/ExampleScene/", "tanktop.obj", "res/images/textures/ExampleScene/", "tanktop.png", "res/shaders/", "Lighting.shader", true, true, UUID(), rot, pos, sca, Material(amb, dif, spe, shin)));
		Global::Variables.currentScene.objectsOnScene.at(Global::Variables.currentScene.objectsOnScene.size() - 1)->SetDisplayName("tank top");


		Global::Variables.currentScene.objectsOnScene.push_back(new Object(type::normalModel, "res/models/ExampleScene/", "tanktrack.obj", "res/images/textures/ExampleScene/", "tanktrack.png", "res/shaders/", "Lighting.shader", true, true, UUID(), rot, pos, sca, Material(amb, dif, spe, shin)));
		Global::Variables.currentScene.objectsOnScene.at(Global::Variables.currentScene.objectsOnScene.size() - 1)->SetDisplayName("tank track");

		animatedLeftF22 = new Object(type::normalModel, "res/models/ExampleScene/", "rightf22.obj", "res/images/textures/ExampleScene/", "grey.png", "res/shaders/", "Lighting.shader", true, true, UUID(), rot, pos, sca, Material(amb, dif, spe, shin));
		animatedLeftF22->SetDisplayName("rightf22");
		Global::Variables.currentScene.objectsOnScene.push_back(animatedLeftF22);

		animatedRightF22 = new Object(type::normalModel, "res/models/ExampleScene/", "leftf22.obj", "res/images/textures/ExampleScene/", "grey.png", "res/shaders/", "Lighting.shader", true, true, UUID(), rot, pos, sca, Material(amb, dif, spe, shin));
		animatedRightF22->SetDisplayName("leftf22");
		Global::Variables.currentScene.objectsOnScene.push_back(animatedRightF22);
		
		animatedFlyingPlane = new Object(type::normalModel, "res/models/ExampleScene/", "flyingplane.obj", "res/images/textures/ExampleScene/", "grey.png", "res/shaders/", "Lighting.shader", true, true, UUID(), rot, pos, sca, Material(amb, dif, spe, shin));
		animatedFlyingPlane->SetDisplayName("distant flying plane");
		Global::Variables.currentScene.objectsOnScene.push_back(animatedFlyingPlane);


		Global::Variables.currentScene.objectsOnScene.push_back(new Object(type::normalModel, "res/models/ExampleScene/", "land.obj", "res/images/textures/ExampleScene/", "land.png", "res/shaders/", "Lighting.shader", true, true, UUID(), rot, pos, sca, Material(amb, dif, spe, shin)));
		Global::Variables.currentScene.objectsOnScene.at(Global::Variables.currentScene.objectsOnScene.size() - 1)->SetDisplayName("land");
	}

	void ExampleScene::Animate(float deltaTime)
	{
		glm::vec3 leftF22Velocity = glm::vec3(0.0f, 0.0f, -40.0f);
		animatedLeftF22->TranslateAddVec3(leftF22Velocity * deltaTime);

		glm::vec3 rightF22Velocity = glm::vec3(0.0f, 15.0f, 30.0f);
		animatedRightF22->TranslateAddVec3(rightF22Velocity * deltaTime);

		glm::vec3 flyingPlaneVelocity = glm::vec3(0.0f, 0.0f, -40.0f);
		animatedFlyingPlane->TranslateAddVec3(flyingPlaneVelocity * deltaTime);
	}

	void ExampleScene::Reset()
	{
		animatedLeftF22->Translate3f(0.0f, 0.0f, 0.0f);
		animatedRightF22->Translate3f(0.0f, 0.0f, 0.0f);
		animatedFlyingPlane->Translate3f(0.0f, 0.0f, 0.0f);
	}
}
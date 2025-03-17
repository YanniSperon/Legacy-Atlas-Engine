#include "LevelEditorControl.h"
#include "Global.h"
#include "System.h"
#include "PhysicsEngine.h"
#include "Object.h"

static void ScaleAddToAll(float x, float y, float z) {
	for (size_t i = 0; i < Atlas::Global::Variables.selectedObjects.size(); ++i) {
		Atlas::Global::Variables.selectedObjects[i]->ScaleAdd3f(x, y, z);
	}
}

static void TranslateAddToAll(float x, float y, float z) {
	for (size_t i = 0; i < Atlas::Global::Variables.selectedObjects.size(); ++i) {
		Atlas::Global::Variables.selectedObjects[i]->TranslateAdd3f(x, y, z);
	}
}

static void RotateAddToAll(float x, float y, float z) {
	for (size_t i = 0; i < Atlas::Global::Variables.selectedObjects.size(); ++i) {
		Atlas::Global::Variables.selectedObjects[i]->RotateAdd3f(x, y, z);
	}
}

static void DeleteObjectFromScene(Atlas::Object* obj) {
	if (Atlas::Global::Variables.currentScene.objectsOnScene.size() > 0 && (obj != nullptr)) {
		std::size_t i;
		for (i = 0; i < Atlas::Global::Variables.currentScene.objectsOnScene.size(); ++i) {
			if (Atlas::Global::Variables.currentScene.objectsOnScene[i] == obj) {
				break;
			}
		}
		if (i == Atlas::Global::Variables.currentScene.objectsOnScene.size()) {
			for (i = 0; i < Atlas::Global::Variables.currentScene.lightsOnScene.size(); ++i) {
				if (Atlas::Global::Variables.currentScene.lightsOnScene[i] == obj) {
					break;
				}
			}
			Atlas::System::Log("Light \"" + obj->GetDisplayName() + "\" deleted!");
			Atlas::Global::Variables.currentScene.lightsOnScene.erase(Atlas::Global::Variables.currentScene.lightsOnScene.begin() + i);
			delete obj;
		}
		else {
			Atlas::System::Log("Object \"" + obj->GetDisplayName() + "\" deleted!");
			Atlas::Global::Variables.currentScene.objectsOnScene.erase(Atlas::Global::Variables.currentScene.objectsOnScene.begin() + i);
			delete obj;
		}
	}
}

void DeleteObjectsFromScene() {
	for (std::size_t i = 0; i < Atlas::Global::Variables.selectedObjects.size(); ++i) {
		DeleteObjectFromScene(Atlas::Global::Variables.selectedObjects[i]);
	}
}

void Scale(double deltaTime) {
	if (Atlas::Global::Variables.keyIn.wHeld) {
		ScaleAddToAll(0.0f, 0.0f, -Atlas::Global::Variables.movementSpeed * deltaTime);
	}
	if (Atlas::Global::Variables.keyIn.sHeld) {
		ScaleAddToAll(0.0f, 0.0f, Atlas::Global::Variables.movementSpeed * deltaTime);
	}
	if (Atlas::Global::Variables.keyIn.aHeld) {
		ScaleAddToAll(-Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
	}
	if (Atlas::Global::Variables.keyIn.dHeld) {
		ScaleAddToAll(Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
	}
	if (Atlas::Global::Variables.keyIn.eHeld) {
		ScaleAddToAll(0.0f, Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f);
	}
	if (Atlas::Global::Variables.keyIn.qHeld) {
		ScaleAddToAll(0.0f, -Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f);
	}
}

void Translate(double deltaTime) {
	if (Atlas::Global::Variables.keyIn.wHeld) {
		TranslateAddToAll(0.0f, 0.0f, -Atlas::Global::Variables.movementSpeed * deltaTime);
	}
	if (Atlas::Global::Variables.keyIn.sHeld) {
		TranslateAddToAll(0.0f, 0.0f, Atlas::Global::Variables.movementSpeed * deltaTime);
	}
	if (Atlas::Global::Variables.keyIn.aHeld) {
		TranslateAddToAll(-Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
	}
	if (Atlas::Global::Variables.keyIn.dHeld) {
		TranslateAddToAll(Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
	}
	if (Atlas::Global::Variables.keyIn.eHeld) {
		TranslateAddToAll(0.0f, Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f);
	}
	if (Atlas::Global::Variables.keyIn.qHeld) {
		TranslateAddToAll(0.0f, -Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f);
	}
}

void Rotate(double deltaTime) {
	if (Atlas::Global::Variables.keyIn.wHeld) {
		RotateAddToAll(0.0f, 0.0f, -Atlas::Global::Variables.movementSpeed * deltaTime);
	}
	if (Atlas::Global::Variables.keyIn.sHeld) {
		RotateAddToAll(0.0f, 0.0f, Atlas::Global::Variables.movementSpeed * deltaTime);
	}
	if (Atlas::Global::Variables.keyIn.aHeld) {
		RotateAddToAll(-Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
	}
	if (Atlas::Global::Variables.keyIn.dHeld) {
		RotateAddToAll(Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
	}
	if (Atlas::Global::Variables.keyIn.eHeld) {
		RotateAddToAll(0.0f, Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f);
	}
	if (Atlas::Global::Variables.keyIn.qHeld) {
		RotateAddToAll(0.0f, -Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f);
	}
}

void ControlCamera(double deltaTime) {
	if (Atlas::Global::Variables.keyIn.wHeld) {
		Atlas::Global::Variables.activeCamera->MoveForward(deltaTime);
	}
	if (Atlas::Global::Variables.keyIn.sHeld) {
		Atlas::Global::Variables.activeCamera->MoveBackward(deltaTime);
	}
	if (Atlas::Global::Variables.keyIn.aHeld) {
		Atlas::Global::Variables.activeCamera->StrafeLeft(deltaTime);
	}
	if (Atlas::Global::Variables.keyIn.dHeld) {
		Atlas::Global::Variables.activeCamera->StrafeRight(deltaTime);
	}
	if (Atlas::Global::Variables.keyIn.eHeld) {
		Atlas::Global::Variables.activeCamera->MoveUp(deltaTime);
	}
	if (Atlas::Global::Variables.keyIn.qHeld) {
		Atlas::Global::Variables.activeCamera->MoveDown(deltaTime);
	}
}

void LevelEditor::LevelEditorControl::Control(double deltaTime)
{
	if (Atlas::Global::Variables.keyIn.leftShiftHeld) {
		Atlas::Global::Variables.movementSpeed = 2.0f * Atlas::Global::Variables.originalMovementSpeed;
	}
	if (Atlas::Global::Variables.keyIn.leftShiftReleased) {
		Atlas::Global::Variables.movementSpeed = Atlas::Global::Variables.originalMovementSpeed;
	}
	if (Atlas::Global::Variables.keyIn.capsLockHeld) {
		Atlas::Global::Variables.movementSpeed = 0.5f * Atlas::Global::Variables.originalMovementSpeed;
	}
	if (Atlas::Global::Variables.keyIn.capsLockReleased) {
		Atlas::Global::Variables.movementSpeed = Atlas::Global::Variables.originalMovementSpeed;
	}

	if (Atlas::Global::Variables.selectedObjects.size() == 0) {
		ControlCamera(deltaTime);
	}
	else {
		Translate(deltaTime);
	}

	if (Atlas::Global::Variables.keyIn.deletePressed) {
		DeleteObjectsFromScene();
	}
}

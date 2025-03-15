#include "LevelEditorControl.h"
#include "Global.h"
#include "System.h"
#include "PhysicsEngine.h"

void LevelEditor::LevelEditorControl::Control(LevelEditor::EditorType& currentEditorType, LevelEditor::Mode& currentMode, Atlas::Object** selectedObject, float deltaTime)
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

	if (Atlas::Global::Variables.keyIn.onePressed) {
		currentEditorType = LevelEditor::EditorType::scene;
	}
	if (Atlas::Global::Variables.keyIn.twoPressed) {
		currentEditorType = LevelEditor::EditorType::light;
	}

	if ((Atlas::Global::Variables.currentScene.objectsOnScene.size() > 0 && currentEditorType == LevelEditor::EditorType::scene) || (currentEditorType == LevelEditor::EditorType::light)) {
		if (Atlas::Global::Variables.keyIn.cPressed) {
			currentMode = LevelEditor::Mode::cam;
		}
		else if (Atlas::Global::Variables.keyIn.ePressed) {
			currentMode = LevelEditor::Mode::scale;
		}
		else if (Atlas::Global::Variables.keyIn.rPressed) {
			currentMode = LevelEditor::Mode::rotate;
		}
		else if (Atlas::Global::Variables.keyIn.vPressed) {
			currentMode = LevelEditor::Mode::translate;
		}
		else if (Atlas::Global::Variables.keyIn.tPressed) {
			currentMode = LevelEditor::Mode::texture;
		}
	}
	else {
		currentMode = LevelEditor::Mode::cam;
	}
	///////////////////////////////////////////////////////////////////////////
	if (currentEditorType == LevelEditor::EditorType::scene) {
		if (currentMode == LevelEditor::Mode::scale) {
			if (Atlas::Global::Variables.keyIn.wHeld) {
				(*selectedObject)->ScaleAdd3f(0.0f, 0.0f, -Atlas::Global::Variables.movementSpeed * deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.sHeld) {
				(*selectedObject)->ScaleAdd3f(0.0f, 0.0f, Atlas::Global::Variables.movementSpeed * deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.aHeld) {
				(*selectedObject)->ScaleAdd3f(-Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.dHeld) {
				(*selectedObject)->ScaleAdd3f(Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.spaceHeld) {
				(*selectedObject)->ScaleAdd3f(0.0f, Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.leftControlHeld) {
				(*selectedObject)->ScaleAdd3f(0.0f, -Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f);
			}
		}
		else if (currentMode == LevelEditor::Mode::translate) {
			if (Atlas::Global::Variables.keyIn.wHeld) {
				(*selectedObject)->TranslateAdd3f(0.0f, 0.0f, -Atlas::Global::Variables.movementSpeed * deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.sHeld) {
				(*selectedObject)->TranslateAdd3f(0.0f, 0.0f, Atlas::Global::Variables.movementSpeed * deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.aHeld) {
				(*selectedObject)->TranslateAdd3f(-Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.dHeld) {
				(*selectedObject)->TranslateAdd3f(Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.spaceHeld) {
				(*selectedObject)->TranslateAdd3f(0.0f, Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.leftControlHeld) {
				(*selectedObject)->TranslateAdd3f(0.0f, -Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f);
			}
		}
		else if (currentMode == LevelEditor::Mode::cam) {
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
			if (Atlas::Global::Variables.keyIn.spaceHeld) {
				Atlas::Global::Variables.activeCamera->MoveUp(deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.leftControlHeld) {
				Atlas::Global::Variables.activeCamera->MoveDown(deltaTime);
			}
		}
		else if (currentMode == LevelEditor::Mode::rotate) {
			if (Atlas::Global::Variables.keyIn.wHeld) {
				(*selectedObject)->RotateAdd3f(0.0f, 0.0f, glm::degrees(-Atlas::Global::Variables.movementSpeed * deltaTime));
			}
			if (Atlas::Global::Variables.keyIn.sHeld) {
				(*selectedObject)->RotateAdd3f(0.0f, 0.0f, glm::degrees(Atlas::Global::Variables.movementSpeed * deltaTime));
			}
			if (Atlas::Global::Variables.keyIn.aHeld) {
				(*selectedObject)->RotateAdd3f(glm::degrees(-Atlas::Global::Variables.movementSpeed * deltaTime), 0.0f, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.dHeld) {
				(*selectedObject)->RotateAdd3f(glm::degrees(Atlas::Global::Variables.movementSpeed * deltaTime), 0.0f, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.spaceHeld) {
				(*selectedObject)->RotateAdd3f(0.0f, glm::degrees(Atlas::Global::Variables.movementSpeed * deltaTime), 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.leftControlHeld) {
				(*selectedObject)->RotateAdd3f(0.0f, glm::degrees(-Atlas::Global::Variables.movementSpeed * deltaTime), 0.0f);
			}
		}
		if (Atlas::Global::Variables.keyIn.backspacePressed) {
			if (Atlas::Global::Variables.currentScene.objectsOnScene.size() > 0 && ((*selectedObject) != nullptr)) {
				std::size_t i = 0;
				for (i = 0; i < Atlas::Global::Variables.currentScene.objectsOnScene.size(); ++i) {
					if (Atlas::Global::Variables.currentScene.objectsOnScene[i] == (*selectedObject)) {
						break;
					}
				}
				Atlas::Global::Variables.currentScene.objectsOnScene.erase(Atlas::Global::Variables.currentScene.objectsOnScene.begin() + i);
				delete (*selectedObject);
				(*selectedObject) = nullptr;
				Atlas::System::Log("Object deleted!");
			}
		}
	}
	else if (currentEditorType == LevelEditor::EditorType::light) {
		if (currentMode == LevelEditor::Mode::scale) {
			if (Atlas::Global::Variables.keyIn.wHeld) {
				Atlas::Global::Variables.currentScene.lightsOnScene.at(0)->ScaleAdd3f(0.0f, 0.0f, -Atlas::Global::Variables.movementSpeed * deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.sHeld) {
				Atlas::Global::Variables.currentScene.lightsOnScene.at(0)->ScaleAdd3f(0.0f, 0.0f, Atlas::Global::Variables.movementSpeed * deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.aHeld) {
				Atlas::Global::Variables.currentScene.lightsOnScene.at(0)->ScaleAdd3f(-Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.dHeld) {
				Atlas::Global::Variables.currentScene.lightsOnScene.at(0)->ScaleAdd3f(Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.spaceHeld) {
				Atlas::Global::Variables.currentScene.lightsOnScene.at(0)->ScaleAdd3f(0.0f, Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.leftControlHeld) {
				Atlas::Global::Variables.currentScene.lightsOnScene.at(0)->ScaleAdd3f(0.0f, -Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f);
			}
		}
		else if (currentMode == LevelEditor::Mode::translate) {
			if (Atlas::Global::Variables.keyIn.wHeld) {
				Atlas::Global::Variables.currentScene.lightsOnScene.at(0)->TranslateAdd3f(0.0f, 0.0f, -Atlas::Global::Variables.movementSpeed * deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.sHeld) {
				Atlas::Global::Variables.currentScene.lightsOnScene.at(0)->TranslateAdd3f(0.0f, 0.0f, Atlas::Global::Variables.movementSpeed * deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.aHeld) {
				Atlas::Global::Variables.currentScene.lightsOnScene.at(0)->TranslateAdd3f(-Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.dHeld) {
				Atlas::Global::Variables.currentScene.lightsOnScene.at(0)->TranslateAdd3f(Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.spaceHeld) {
				Atlas::Global::Variables.currentScene.lightsOnScene.at(0)->TranslateAdd3f(0.0f, Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.leftControlHeld) {
				Atlas::Global::Variables.currentScene.lightsOnScene.at(0)->TranslateAdd3f(0.0f, -Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f);
			}
		}
		else if (currentMode == LevelEditor::Mode::cam) {
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
			if (Atlas::Global::Variables.keyIn.spaceHeld) {
				Atlas::Global::Variables.activeCamera->MoveUp(deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.leftControlHeld) {
				Atlas::Global::Variables.activeCamera->MoveDown(deltaTime);
			}
		}
		else if (currentMode == LevelEditor::Mode::rotate) {
			if (Atlas::Global::Variables.keyIn.wHeld) {
				Atlas::Global::Variables.currentScene.lightsOnScene.at(0)->RotateAdd3f(0.0f, 0.0f, glm::degrees(-Atlas::Global::Variables.movementSpeed * deltaTime));
			}
			if (Atlas::Global::Variables.keyIn.sHeld) {
				Atlas::Global::Variables.currentScene.lightsOnScene.at(0)->RotateAdd3f(0.0f, 0.0f, glm::degrees(Atlas::Global::Variables.movementSpeed * deltaTime));
			}
			if (Atlas::Global::Variables.keyIn.aHeld) {
				Atlas::Global::Variables.currentScene.lightsOnScene.at(0)->RotateAdd3f(glm::degrees(-Atlas::Global::Variables.movementSpeed * deltaTime), 0.0f, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.dHeld) {
				Atlas::Global::Variables.currentScene.lightsOnScene.at(0)->RotateAdd3f(glm::degrees(Atlas::Global::Variables.movementSpeed * deltaTime), 0.0f, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.spaceHeld) {
				Atlas::Global::Variables.currentScene.lightsOnScene.at(0)->RotateAdd3f(0.0f, glm::degrees(Atlas::Global::Variables.movementSpeed * deltaTime), 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.leftControlHeld) {
				Atlas::Global::Variables.currentScene.lightsOnScene.at(0)->RotateAdd3f(0.0f, glm::degrees(-Atlas::Global::Variables.movementSpeed * deltaTime), 0.0f);
			}
		}
	}
}

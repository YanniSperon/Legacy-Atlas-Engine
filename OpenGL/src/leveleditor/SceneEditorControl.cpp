#include "SceneEditorControl.h"
#include "Global.h"
#include "System.h"

void LevelEditor::SceneEditorControl::Control(LevelEditor::EditorType& currentEditorType, LevelEditor::Mode& currentMode, unsigned int& selectedObject, float deltaTime)
{

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
				Atlas::Global::Variables.currentScene.objectsOnScene[selectedObject]->ScaleAdd3f(0.0f, 0.0f, -Atlas::Global::Variables.movementSpeed * deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.sHeld) {
				Atlas::Global::Variables.currentScene.objectsOnScene[selectedObject]->ScaleAdd3f(0.0f, 0.0f, Atlas::Global::Variables.movementSpeed * deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.aHeld) {
				Atlas::Global::Variables.currentScene.objectsOnScene[selectedObject]->ScaleAdd3f(-Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.dHeld) {
				Atlas::Global::Variables.currentScene.objectsOnScene[selectedObject]->ScaleAdd3f(Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.spaceHeld) {
				Atlas::Global::Variables.currentScene.objectsOnScene[selectedObject]->ScaleAdd3f(0.0f, Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.leftControlHeld) {
				Atlas::Global::Variables.currentScene.objectsOnScene[selectedObject]->ScaleAdd3f(0.0f, -Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f);
			}
		}
		else if (currentMode == LevelEditor::Mode::translate) {
			if (Atlas::Global::Variables.keyIn.wHeld) {
				Atlas::Global::Variables.currentScene.objectsOnScene[selectedObject]->TranslateAdd3f(0.0f, 0.0f, -Atlas::Global::Variables.movementSpeed * deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.sHeld) {
				Atlas::Global::Variables.currentScene.objectsOnScene[selectedObject]->TranslateAdd3f(0.0f, 0.0f, Atlas::Global::Variables.movementSpeed * deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.aHeld) {
				Atlas::Global::Variables.currentScene.objectsOnScene[selectedObject]->TranslateAdd3f(-Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.dHeld) {
				Atlas::Global::Variables.currentScene.objectsOnScene[selectedObject]->TranslateAdd3f(Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.spaceHeld) {
				Atlas::Global::Variables.currentScene.objectsOnScene[selectedObject]->TranslateAdd3f(0.0f, Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.leftControlHeld) {
				Atlas::Global::Variables.currentScene.objectsOnScene[selectedObject]->TranslateAdd3f(0.0f, -Atlas::Global::Variables.movementSpeed * deltaTime, 0.0f);
			}
		}
		else if (currentMode == LevelEditor::Mode::cam) {
			if (Atlas::Global::Variables.keyIn.wHeld) {
				Atlas::Global::Variables.camera.MoveForward(deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.sHeld) {
				Atlas::Global::Variables.camera.MoveBackward(deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.aHeld) {
				Atlas::Global::Variables.camera.StrafeLeft(deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.dHeld) {
				Atlas::Global::Variables.camera.StrafeRight(deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.spaceHeld) {
				Atlas::Global::Variables.camera.MoveUp(deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.leftControlHeld) {
				Atlas::Global::Variables.camera.MoveDown(deltaTime);
			}
		}
		else if (currentMode == LevelEditor::Mode::rotate) {
			if (Atlas::Global::Variables.keyIn.wHeld) {
				Atlas::Global::Variables.currentScene.objectsOnScene[selectedObject]->RotateAdd3f(0.0f, 0.0f, glm::degrees(-Atlas::Global::Variables.movementSpeed * deltaTime));
			}
			if (Atlas::Global::Variables.keyIn.sHeld) {
				Atlas::Global::Variables.currentScene.objectsOnScene[selectedObject]->RotateAdd3f(0.0f, 0.0f, glm::degrees(Atlas::Global::Variables.movementSpeed * deltaTime));
			}
			if (Atlas::Global::Variables.keyIn.aHeld) {
				Atlas::Global::Variables.currentScene.objectsOnScene[selectedObject]->RotateAdd3f(glm::degrees(-Atlas::Global::Variables.movementSpeed * deltaTime), 0.0f, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.dHeld) {
				Atlas::Global::Variables.currentScene.objectsOnScene[selectedObject]->RotateAdd3f(glm::degrees(Atlas::Global::Variables.movementSpeed * deltaTime), 0.0f, 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.spaceHeld) {
				Atlas::Global::Variables.currentScene.objectsOnScene[selectedObject]->RotateAdd3f(0.0f, glm::degrees(Atlas::Global::Variables.movementSpeed * deltaTime), 0.0f);
			}
			if (Atlas::Global::Variables.keyIn.leftControlHeld) {
				Atlas::Global::Variables.currentScene.objectsOnScene[selectedObject]->RotateAdd3f(0.0f, glm::degrees(-Atlas::Global::Variables.movementSpeed * deltaTime), 0.0f);
			}
		}

		if (Atlas::Global::Variables.keyIn.leftBracketPressed) {
			if (selectedObject > 0) {
				selectedObject--;
			}
		}
		if (Atlas::Global::Variables.keyIn.rightBracketPressed) {
			if (selectedObject < Atlas::Global::Variables.currentScene.objectsOnScene.size() - 1) {
				selectedObject++;
			}
		}
		if (Atlas::Global::Variables.keyIn.nPressed) {
			Atlas::System::Log("Cube created!");
			Atlas::Global::Variables.currentScene.objectsOnScene.push_back(new Atlas::Object(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), Atlas::type::cubeModel, "", "", "res/images/textures/", "newcow.png", "res/shaders/", "Lighting.shader", true, true, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), Atlas::Material(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f)));
			selectedObject = Atlas::Global::Variables.currentScene.objectsOnScene.size() - 1;
		}
		if (Atlas::Global::Variables.keyIn.backspacePressed) {
			if (Atlas::Global::Variables.currentScene.objectsOnScene.size() > 0) {
				Atlas::System::Log("Object deleted!");
				delete Atlas::Global::Variables.currentScene.objectsOnScene.at(selectedObject);
				Atlas::Global::Variables.currentScene.objectsOnScene.erase(Atlas::Global::Variables.currentScene.objectsOnScene.begin() + selectedObject);

				if (selectedObject > 0) {
					selectedObject--;
				}
				else {
					selectedObject = 0;
				}
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
				Atlas::Global::Variables.camera.MoveForward(deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.sHeld) {
				Atlas::Global::Variables.camera.MoveBackward(deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.aHeld) {
				Atlas::Global::Variables.camera.StrafeLeft(deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.dHeld) {
				Atlas::Global::Variables.camera.StrafeRight(deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.spaceHeld) {
				Atlas::Global::Variables.camera.MoveUp(deltaTime);
			}
			if (Atlas::Global::Variables.keyIn.leftControlHeld) {
				Atlas::Global::Variables.camera.MoveDown(deltaTime);
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

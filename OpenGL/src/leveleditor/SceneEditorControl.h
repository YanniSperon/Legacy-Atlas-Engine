#pragma once

#include "LevelEditor.h"

namespace LevelEditor {
	class SceneEditorControl {
	public:
		static void Control(LevelEditor::EditorType& currentEditorType, LevelEditor::Mode& currentMode, unsigned int& selectedObject, float deltaTime);
	};
}
#pragma once

#include "LevelEditor.h"
#include "Object.h"

namespace LevelEditor {
	class LevelEditorControl {
	public:
		static void Control(LevelEditor::EditorType& currentEditorType, LevelEditor::Mode& currentMode, Atlas::Object** selectedObject, float deltaTime);
	};
}
#pragma once

#include "LevelEditor.h"

namespace Atlas {
	class RenderingEngine {
	public:
		static void Initialize();
		static void Begin();
		static void Render(bool& EnableWireframe, bool& EnableGUI, LevelEditor::EditorType& currentEditorType, LevelEditor::Mode& currentMode, unsigned int& selectedObject);
		static void End();
		static void Cleanup();
	};
}
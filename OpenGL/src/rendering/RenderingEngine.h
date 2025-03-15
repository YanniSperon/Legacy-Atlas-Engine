#pragma once

#include "LevelEditor.h"
#include "Object.h"


namespace Atlas {
	class RenderingEngine {
	public:
		static void Initialize();
		static void Begin();
		static void BeginPhysicsSimulator();
		static void Render(bool& EnableWireframe, bool& EnableGUI, LevelEditor::EditorType& currentEditorType, LevelEditor::Mode& currentMode, Object** selectedObject);
		static void End();
		static void Cleanup();
	};
}
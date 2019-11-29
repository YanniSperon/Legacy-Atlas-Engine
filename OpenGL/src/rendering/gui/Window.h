#pragma once
#include "Object.h"
#include "LevelEditor.h"
#include <vector>

namespace Atlas {
	class Window {
	public:
		static void DrawObjectSettingsWindow(Object* object);
		static void DrawInfoWindow(LevelEditor::EditorType& currentEditorType, LevelEditor::Mode& currentMode);
		static void DrawSpawnWindow(std::vector<Object*>& objectsOnScene, unsigned int& selectedObject);
		static void DrawDebug(bool& EnableConsole);
	};
}
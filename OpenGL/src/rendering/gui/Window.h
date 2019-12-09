#pragma once
#include "Object.h"
#include "LevelEditor.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <vector>

namespace Atlas {

	class Window {
	public:
		static void DrawInfoWindow(LevelEditor::EditorType& currentEditorType, LevelEditor::Mode& currentMode);
		static void DrawDebug(bool& EnableConsole, bool& EnableWireframe);
		static void DrawFileManager(GLFWwindow* window);
		static void DrawPostProcessingManager(GLFWwindow* window);
		static void DrawSpawnWindow(std::vector<Object*>& objectsOnScene, unsigned int& selectedObject);
		static void DrawObjectSettingsWindow(Object* object);
		static void DrawPhysicsManager();
	};
}
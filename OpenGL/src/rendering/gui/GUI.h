#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "LevelEditor.h"
#include "Object.h"

namespace Atlas {

	class GUI {
	public:
		static void Initialize(GLFWwindow* window);
		static void LoadLevelEditorGUI(GLFWwindow* window, LevelEditor::EditorType currentEditorType, LevelEditor::Mode currentMode, Object** selectedObject, bool& EnableWireframe);
		static void LoadPhysicsSimulatorGUI();
		static void Draw();
		static void Terminate();
	};
}
#include "RenderingEngine.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Callbacks.h"
#include "SimpleRenderer.h"
#include "Global.h"
#include "PostProcessor.h"
#include "System.h"
#include "InputHandler.h"
#include "GUI.h"

namespace Atlas {

	void RenderingEngine::Initialize()
	{
		PostProcessor::PrepareForInitialization(MSAA(false, 0));

		System::Log("Vendor: " + std::string((char*)glGetString(GL_VENDOR)));
		System::Log("Model: " + std::string((char*)glGetString(GL_RENDERER)));
		System::Log("Version: " + std::string((char*)glGetString(GL_VERSION)));

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(Callbacks::openglCallbackFunction, NULL);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glFrontFace(GL_CW);

		Global::Variables.currentRenderer = new SimpleRenderer();

		PostProcessor::Initialize("res/shaders/NoPostFX.shader");
		PostProcessor::ChangeEffect("res/shaders/BlurPostFX.shader");
		PostProcessor::ChangeEffect("res/shaders/FXAAPostFX.shader");
		PostProcessor::ChangeEffect("res/shaders/GreyscalePostFX.shader");
		PostProcessor::ChangeEffect("res/shaders/InvertPostFX.shader");
		PostProcessor::ChangeEffect("res/shaders/SharpenPostFX.shader");
		PostProcessor::ChangeEffect("res/shaders/NoPostFX.shader");

		GUI::Initialize(Global::Variables.window);

		//Font arial24pt = Font("res/fonts/arial/", "arial.ttf", 24);
		//Font timesnewroman32pt = Font("res/fonts/times new roman/", "times.ttf", 32);
		//GLuint leftEyeFrameBuffer;
		//glGenFramebuffers(1, &leftEyeFrameBuffer);
		//GLuint rightEyeFrameBuffer;
		//glGenFramebuffers(1, &rightEyeFrameBuffer);
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//GLuint leftEyeFrameBuffer;
		//glGenFramebuffers(1, &leftEyeFrameBuffer);
		//GLuint rightEyeFrameBuffer;
		//glGenFramebuffers(1, &rightEyeFrameBuffer);
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void RenderingEngine::Begin()
	{
		PostProcessor::PrepareForRendering();
	}

	void RenderingEngine::BeginPhysicsSimulator()
	{
		PostProcessor::PrepareForRenderingPhysicsSimulation();
	}

	void RenderingEngine::Render(bool& EnableWireframe, bool& EnableGUI, LevelEditor::EditorType& currentEditorType, LevelEditor::Mode& currentMode, unsigned int& selectedObject)
	{
		if (EnableWireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			//PhysicsEngine::DrawDebug();
			PostProcessor::Render(Global::Variables.currentRenderer);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			//PhysicsEngine::DrawDebug();
			PostProcessor::Render(Global::Variables.currentRenderer);
		}
		if (EnableGUI) {
			GUI::LoadLevelEditorGUI(Global::Variables.window, currentEditorType, currentMode, selectedObject, EnableWireframe);
			GUI::Draw();
		}
	}

	void RenderingEngine::End()
	{
		glfwSwapBuffers(Global::Variables.window);
	}

	void RenderingEngine::Cleanup()
	{
		Mesh::FlushCache();
		Object::FlushCache();
		PostProcessor::Cleanup();
	}
}
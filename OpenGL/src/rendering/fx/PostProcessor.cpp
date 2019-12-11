#include "PostProcessor.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "System.h"
#include "Player.h"
#include "Global.h"
#include <algorithm>

namespace Atlas {

	static Object2D* quadForRenderingFX;
	static unsigned int postProcessingFramebuffer;
	static unsigned int textureColorbuffer;
	static unsigned int rbo;
	static unsigned int intermediateFramebuffer;
	static unsigned int screenTexture;
	static MSAA multisampling;

	void PostProcessor::PrepareForInitialization(MSAA multiSampleAntiAliasing)
	{
		multisampling = multiSampleAntiAliasing;
		if (multisampling.enabled && multisampling.value == 0) {
			multisampling.enabled = false;
		}
		if (multisampling.enabled) {
			glfwWindowHint(GLFW_SAMPLES, multisampling.value);
		}
	}

	void PostProcessor::Initialize(std::string postProcessingShaderAddress)
	{
		if (multisampling.enabled) {
			glEnable(GL_MULTISAMPLE);

			glGenFramebuffers(1, &postProcessingFramebuffer);
			glGenTextures(1, &textureColorbuffer);
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureColorbuffer);
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, multisampling.value , GL_RGB, Global::Variables.currentWidth, Global::Variables.currentHeight, GL_TRUE);
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

			glGenRenderbuffers(1, &rbo);
			glBindRenderbuffer(GL_RENDERBUFFER, rbo);
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, multisampling.value, GL_DEPTH24_STENCIL8, Global::Variables.currentWidth, Global::Variables.currentHeight);

			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, postProcessingFramebuffer);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, textureColorbuffer, 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
				System::Err("Framebuffer incomplete!");
			}

			glGenFramebuffers(1, &intermediateFramebuffer);

			glGenTextures(1, &screenTexture);
			glBindTexture(GL_TEXTURE_2D, screenTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Global::Variables.currentWidth, Global::Variables.currentHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, intermediateFramebuffer);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
				System::Err("Framebuffer incomplete!");
			}
		}
		else {
			glGenFramebuffers(1, &postProcessingFramebuffer);
			glGenTextures(1, &textureColorbuffer);
			glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Global::Variables.currentWidth, Global::Variables.currentHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glGenRenderbuffers(1, &rbo);
			glBindRenderbuffer(GL_RENDERBUFFER, rbo);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Global::Variables.currentWidth, Global::Variables.currentHeight);

			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, postProcessingFramebuffer);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
				System::Err("Framebuffer incomplete!");
			}
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		unsigned int shaderID = 0;

		if (Global::Variables.shaderCache.find(postProcessingShaderAddress) != Global::Variables.shaderCache.end()) {
			shaderID = Global::Variables.shaderCache[postProcessingShaderAddress]->GetShaderID();
		}
		else {
			std::string file = postProcessingShaderAddress;
			std::replace(file.begin(), file.end(), '\\', '/');
			std::string physicalLocation = "";

			file = System::ConvertFilePathToLocal(file);
			Filepath pathtemp = System::SeperateFilepath(file);
			std::string shadrDirectory = pathtemp.directory;
			std::string shadrName = pathtemp.filename;
			physicalLocation = pathtemp.directory + pathtemp.filename;

			Global::Variables.loadedPostProcessingShaderCache[shadrName] = physicalLocation;

			Global::Variables.shaderCache[shadrDirectory + shadrName] = new Shader(shadrDirectory + shadrName);
			shaderID = Global::Variables.shaderCache[shadrDirectory + shadrName]->GetShaderID();
		}
		if (multisampling.enabled) {
			quadForRenderingFX = new Object2D(glm::vec2(0.0f, 0.0f), glm::vec2(Global::Variables.currentWidth, Global::Variables.currentHeight), 0.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), intermediateFramebuffer, shaderID, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
		}
		else {
			quadForRenderingFX = new Object2D(glm::vec2(0.0f, 0.0f), glm::vec2(Global::Variables.currentWidth, Global::Variables.currentHeight), 0.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), textureColorbuffer, shaderID, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
		}
	}

	void PostProcessor::PrepareForRendering()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, postProcessingFramebuffer);
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void PostProcessor::PrepareForRenderingPhysicsSimulation()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, postProcessingFramebuffer);
		glEnable(GL_DEPTH_TEST);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void PostProcessor::Render(Renderer* renderer)
	{
		if (multisampling.enabled) {
			glBindFramebuffer(GL_READ_FRAMEBUFFER, postProcessingFramebuffer);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, intermediateFramebuffer);
			glBlitFramebuffer(0, 0, Global::Variables.currentWidth, Global::Variables.currentHeight, 0, 0, Global::Variables.currentWidth, Global::Variables.currentHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
			glDisable(GL_DEPTH_TEST);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			renderer->Submit2D(quadForRenderingFX);
			renderer->SimpleFlush(Global::Variables.activeCamera, Global::Variables.currentWidth, Global::Variables.currentHeight, Global::Variables.FOV, Global::Variables.currentScene.lightsOnScene.at(0));
		}
		else {
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			glDisable(GL_DEPTH_TEST);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			renderer->Submit2D(quadForRenderingFX);
			renderer->SimpleFlush(Global::Variables.activeCamera, Global::Variables.currentWidth, Global::Variables.currentHeight, Global::Variables.FOV, Global::Variables.currentScene.lightsOnScene.at(0));
		}
	}

	void PostProcessor::RenderPhysicsRenderer(PhysicsRenderer* renderer, PhysicsScene* scene)
	{
		if (multisampling.enabled) {
			glBindFramebuffer(GL_READ_FRAMEBUFFER, postProcessingFramebuffer);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, intermediateFramebuffer);
			glBlitFramebuffer(0, 0, Global::Variables.currentWidth, Global::Variables.currentHeight, 0, 0, Global::Variables.currentWidth, Global::Variables.currentHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
			glDisable(GL_DEPTH_TEST);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			renderer->Submit2D(quadForRenderingFX);
			renderer->SimpleFlush(scene->playersOnScene.at(0), Global::Variables.currentWidth, Global::Variables.currentHeight, Global::Variables.FOV, scene->physicsLightsOnScene.at(0));
		}
		else {
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			glDisable(GL_DEPTH_TEST);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			renderer->Submit2D(quadForRenderingFX);
			renderer->SimpleFlush(scene->playersOnScene.at(0), Global::Variables.currentWidth, Global::Variables.currentHeight, Global::Variables.FOV, scene->physicsLightsOnScene.at(0));
		}
	}

	void PostProcessor::ChangeEffect(std::string newShaderShortenedName)
	{
		unsigned int shaderID = 0;

		if (Global::Variables.shaderCache.find(newShaderShortenedName) != Global::Variables.shaderCache.end()) {
			shaderID = Global::Variables.shaderCache[newShaderShortenedName]->GetShaderID();
		}
		else {
			std::string file = newShaderShortenedName;
			std::replace(file.begin(), file.end(), '\\', '/');
			std::string physicalLocation = "";

			file = System::ConvertFilePathToLocal(file);
			Filepath pathtemp = System::SeperateFilepath(file);
			std::string shadrDirectory = pathtemp.directory;
			std::string shadrName = pathtemp.filename;
			physicalLocation = pathtemp.directory + pathtemp.filename;

			Global::Variables.loadedPostProcessingShaderCache[shadrName] = physicalLocation;

			Global::Variables.shaderCache[shadrDirectory + shadrName] = new Shader(shadrDirectory + shadrName);
			shaderID = Global::Variables.shaderCache[shadrDirectory + shadrName]->GetShaderID();
		}

		quadForRenderingFX->SetShader(shaderID);
	}

	void PostProcessor::Cleanup()
	{
		delete quadForRenderingFX;
		glDeleteFramebuffers(1, &postProcessingFramebuffer);
		glDeleteTextures(1, &textureColorbuffer);
		glDeleteRenderbuffers(1, &rbo);
		glDeleteFramebuffers(1, &intermediateFramebuffer);
		glDeleteTextures(1, &screenTexture);
	}
}
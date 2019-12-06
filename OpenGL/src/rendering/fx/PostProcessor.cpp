#include "PostProcessor.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "System.h"
#include "Global.h"
#include <algorithm>

namespace Atlas {

	static Object2D* quadForRenderingFX;
	static unsigned int postProcessingFramebuffer;
	static unsigned int textureColorbuffer;
	static unsigned int rbo;
	static unsigned int intermediateFramebuffer;
	static unsigned int screenTexture;

	void PostProcessor::Initialize(std::string postProcessingShaderAddress)
	{
		glGenFramebuffers(1, &postProcessingFramebuffer);
		glGenTextures(1, &textureColorbuffer);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureColorbuffer);
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, Global::Variables.currentWidth, Global::Variables.currentHeight, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, Global::Variables.currentWidth, Global::Variables.currentHeight);

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

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		std::string file2 = postProcessingShaderAddress;
		std::replace(file2.begin(), file2.end(), '\\', '/');
		std::string physicalLocation2 = "";

		file2 = System::ConvertFilePathToLocal(file2);
		Filepath pathtemp2 = System::SeperateFilepath(file2);
		std::string shadrDirectory2 = pathtemp2.directory;
		std::string shadrName2 = pathtemp2.filename;

		unsigned int shaderID = 0;

		if (Global::Variables.shaderCache.find(shadrDirectory2 + shadrName2) != Global::Variables.shaderCache.end()) {
			shaderID = Global::Variables.shaderCache[shadrDirectory2 + shadrName2]->GetShaderID();
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

		quadForRenderingFX = new Object2D(glm::vec2(0.0f, 0.0f), glm::vec2(Global::Variables.currentWidth, Global::Variables.currentHeight), 0.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), intermediateFramebuffer, shaderID, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
	}

	void PostProcessor::Prepare()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, postProcessingFramebuffer);
		glEnable(GL_DEPTH_TEST);
	}

	void PostProcessor::Render(Renderer* renderer)
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, postProcessingFramebuffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, intermediateFramebuffer);
		glBlitFramebuffer(0, 0, Global::Variables.currentWidth, Global::Variables.currentHeight, 0, 0, Global::Variables.currentWidth, Global::Variables.currentHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
		glDisable(GL_DEPTH_TEST);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		renderer->Submit2D(quadForRenderingFX);
		renderer->SimpleFlush(&Global::Variables.camera, Global::Variables.currentWidth, Global::Variables.currentHeight, Global::Variables.FOV, Global::Variables.currentScene.lightsOnScene.at(0));
	}

	void PostProcessor::ChangeEffect(std::string newShader)
	{
		std::string file2 = newShader;
		std::replace(file2.begin(), file2.end(), '\\', '/');
		std::string physicalLocation2 = "";

		file2 = System::ConvertFilePathToLocal(file2);
		Filepath pathtemp2 = System::SeperateFilepath(file2);
		std::string shadrDirectory2 = pathtemp2.directory;
		std::string shadrName2 = pathtemp2.filename;

		unsigned int shaderID = 0;

		if (Global::Variables.shaderCache.find(shadrDirectory2 + shadrName2) != Global::Variables.shaderCache.end()) {
			shaderID = Global::Variables.shaderCache[shadrDirectory2 + shadrName2]->GetShaderID();
		}
		else {
			std::string file = newShader;
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
}
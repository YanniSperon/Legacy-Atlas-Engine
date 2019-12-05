#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <openvr.h>
#include "System.h"

namespace Atlas {
	struct RenderTarget
	{
		GLuint fbo;

		unsigned int frameWidth; ///< one half the allocated render target width, since we are using side by side stereo
		unsigned int frameHeight;
		unsigned int multisamples;

		RenderTarget() :
			frameWidth(0), frameHeight(0), multisamples(0), fbo(0)
		{

		}

		RenderTarget(unsigned int width, unsigned int height, unsigned int samples) :
			frameWidth(width), frameHeight(height), multisamples(samples)
		{
			glGenFramebuffers(1, &fbo);
		}
	};

	struct BasicRenderTarget : public RenderTarget
	{
		GLuint depthTex;

		void prime(GLuint tex)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);

			if (multisamples > 1)
			{
				glFramebufferTexture2DMultisampleEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0, multisamples);
			}
			else
			{
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
			}

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		BasicRenderTarget() :
			RenderTarget(), depthTex(0)
		{
			
		}

		BasicRenderTarget(int multisamples, unsigned int width, unsigned int height) :
			RenderTarget(width, height, multisamples)
		{
			glGenBuffers(1, &depthTex);
			const GLenum depthFormat = GL_DEPTH_COMPONENT24;

			if (multisamples > 1)
			{
				System::Log("Side by side with multisamples : " + multisamples);
				glBindFramebuffer(GL_DEPTH_COMPONENT24, fbo);
				glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER, multisamples, depthFormat, width, height);
			}
			else
			{
				System::Log("Side by side without multisampling");
				glRenderbufferStorageEXT(GL_RENDERBUFFER, depthFormat, width, height);
			}

			glFramebufferTexture2D(GL_DEPTH_ATTACHMENT, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, depthTex, 0);

			static const GLenum draw_buffers[] = { GL_COLOR_ATTACHMENT0 };

			glViewport(0, 0, frameWidth, frameHeight);
		}
	};
}
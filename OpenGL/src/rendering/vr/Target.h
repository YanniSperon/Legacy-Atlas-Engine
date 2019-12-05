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
			System::Log("Initializing basicrendertarget");
		}

		RenderTarget(unsigned int width, unsigned int height, unsigned int samples) :
			frameWidth(width), frameHeight(height), multisamples(samples)
		{
			System::Log("Initializing rendertarget with arguments");
			glGenFramebuffers(1, &fbo);
			System::Log("Finished initializing rendertarget with arguments");
		}
	};

	struct BasicRenderTarget : public RenderTarget
	{
		GLuint depthTex;

		void prime(GLuint tex)
		{
			System::Log("Binding framebuffer");
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			System::Log("framebuffer bound");

			if (multisamples > 1)
			{
				glFramebufferTexture2DMultisampleEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0, multisamples);
			}
			else
			{
				System::Log("GLframebuffertexture2d");
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
				System::Log("finished GLframebuffertexture2d");
			}
			//System::Log("Attempting glclear");
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//System::Log("finished glclear");
		}

		BasicRenderTarget() :
			RenderTarget(), depthTex(0)
		{
			System::Log("Initializing basicrendertarget");
		}

		BasicRenderTarget(int multisamples, unsigned int width, unsigned int height) :
			RenderTarget(width, height, multisamples)
		{
			System::Log("Initializing basicrendertarget with arguments");
			glGenRenderbuffers(1, &depthTex);
			const GLenum depthFormat = GL_DEPTH_COMPONENT24;
			glBindRenderbuffer(GL_RENDERBUFFER, depthTex);

			if (multisamples > 1)
			{
				System::Log("Side by side with multisamples : " + multisamples);
				//glBindFramebuffer(GL_DEPTH_COMPONENT24, fbo);
				glRenderbufferStorageMultisample(GL_RENDERBUFFER, multisamples, depthFormat, width, height);
			}
			else
			{
				System::Log("Side by side without multisampling");
				glRenderbufferStorage(GL_RENDERBUFFER, depthFormat, width, height);
				System::Log("Done setting renderbuffer storage format");
			}

			System::Log("binding framebuffer object");
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			System::Log("setting the depth attachment");
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTex, 0);
			System::Log("done setting the depth attachment");

			static const GLenum draw_buffers[] = { GL_COLOR_ATTACHMENT0 };

			glViewport(0, 0, frameWidth, frameHeight);
			System::Log("Finished init basicrendertarget with arguments");
		}
	};
}
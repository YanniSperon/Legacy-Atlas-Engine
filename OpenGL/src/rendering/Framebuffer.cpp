#include "Framebuffer.h"
#include "Global.h"

namespace Atlas {

	void Framebuffer::InitializeFramebuffer(int type)
	{
		CreateFramebuffer();
		CreateTextureAttachment();
		if (type == DEPTH_RENDER_BUFFER) {
			CreateDepthBufferAttachment();
		}
		else if (type == DEPTH_TEXTURE) {
			CreateDepthTextureAttachment();
		}
		Unbind();
	}

	void Framebuffer::CreateFramebuffer()
	{
		glGenFramebuffers(1, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
	}

	void Framebuffer::CreateTextureAttachment()
	{
		glGenTextures(1, &colorTexture);
		glBindTexture(GL_TEXTURE_2D, colorTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
	}

	void Framebuffer::CreateDepthTextureAttachment()
	{
		glGenTextures(1, &depthTexture);
		glBindTexture(GL_TEXTURE_2D, depthTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
	}

	void Framebuffer::CreateDepthBufferAttachment()
	{
		glGenRenderbuffers(1, &depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	}

	Framebuffer::Framebuffer()
		: framebuffer(0), colorTexture(0), depthTexture(0), depthBuffer(0), colorBuffer(0), width(0), height(0)
	{
	}

	Framebuffer::Framebuffer(int desiredWidth, int desiredHeight, int depthBufferType)
		: width(desiredWidth), height(desiredHeight)
	{
		InitializeFramebuffer(depthBufferType);
	}

	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &framebuffer);
		glDeleteTextures(1, &colorTexture);
		glDeleteTextures(1, &depthTexture);
		glDeleteRenderbuffers(1, &depthBuffer);
		glDeleteRenderbuffers(1, &colorBuffer);
	}

	void Framebuffer::BindDraw()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
		glViewport(0, 0, width, height);
	}

	void Framebuffer::BindRead()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
		glReadBuffer(GL_COLOR_ATTACHMENT0);
	}

	void Framebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, Global::Variables.currentWidth, Global::Variables.currentHeight);
	}

	int Framebuffer::GetColorTexture()
	{
		return colorTexture;
	}

	int Framebuffer::GetDepthTexture()
	{
		return depthTexture;
	}
}

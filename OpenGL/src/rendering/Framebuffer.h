#pragma once

namespace Atlas {
	class Framebuffer {
	private:
		int NONE = 0;
		int DEPTH_TEXTURE = 1;
		int DEPTH_RENDER_BUFFER = 2;

		int width;
		int height;
		
		unsigned int framebuffer;

		unsigned int colorTexture;
		unsigned int depthTexture;

		unsigned int depthBuffer;
		unsigned int colorBuffer;

		void InitializeFramebuffer(int type);
		void CreateFramebuffer();
		void CreateTextureAttachment();
		void CreateDepthTextureAttachment();
		void CreateDepthBufferAttachment();
	public:
		Framebuffer();
		Framebuffer(int desiredWidth, int desiredHeight, int depthBufferType);
		~Framebuffer();

		void BindDraw();
		void BindRead();
		void Unbind();

		int GetColorTexture();
		int GetDepthTexture();
	};
}
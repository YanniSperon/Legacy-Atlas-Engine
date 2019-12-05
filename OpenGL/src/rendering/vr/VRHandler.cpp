#include "VRHandler.h"

namespace Atlas {

	static VRHandler::OpenVRApplication app;
	static BasicRenderTarget leftRT;
	static BasicRenderTarget rightRT;
	static GLuint leftEyeTexture;
	static GLuint rightEyeTexture;

	void VRHandler::Setup()
	{
		if (Global::Variables.hasVR) {
			if (vr::VR_IsHmdPresent()) {
				//vr::EVRInitError eError = vr::VRInitError_None;
				//vr_pointer = VR_Init(&eError, vr::VRApplication_Scene); // VRApplication_Background OR VRApplication_Scene OR VRApplication_Overlay OR VRApplication_Utility
				//if (eError != vr::VRInitError_None)
				//{
				//	vr_pointer = NULL;
				//	std::string error = VR_GetVRInitErrorAsEnglishDescription(eError);
				//	System::Err("Unable to init VR runtime: \"" + error + "\"");
				//}
				try {
					glGenTextures(1, &leftEyeTexture);
					glTextureStorage2D(leftEyeTexture, 1, GL_RGBA8, app.rtWidth, app.rtHeight);

					glGenTextures(1, &rightEyeTexture);
					glTextureStorage2D(rightEyeTexture, 1, GL_RGBA8, app.rtWidth, app.rtHeight);

					leftRT = BasicRenderTarget(1, app.rtWidth, app.rtHeight);
					rightRT = BasicRenderTarget(1, app.rtWidth, app.rtHeight);

					leftRT.prime(leftEyeTexture);
					rightRT.prime(rightEyeTexture);

					glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
					glBindFramebuffer(GL_FRAMEBUFFER, leftRT.fbo);
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

					if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
					{
						System::Err("left rt incomplete");
					}

					glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
					glBindFramebuffer(GL_FRAMEBUFFER, rightRT.fbo);
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

					if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
					{
						System::Err("right rt incomplete");
					}

					glBindFramebuffer(GL_FRAMEBUFFER, 0);
				}
				catch (const std::exception & e) {
					System::Err("Fatal error, cannot initialize VR display");
				}
			}
			else {
				System::Err("Cannot initialize VR runtime, no headset detected!");
			}
		}
	}

	std::string VRHandler::GetTrackedDeviceString(vr::IVRSystem* pHmd, vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop, vr::TrackedPropertyError* peError)
	{
		//vr::IVRSystem* vr_pointer = NULL;
		//if (Global::Variables.hasVR) {
		//	vr::EVRInitError eError = vr::VRInitError_None;
		//	vr_pointer = VR_Init(&eError, vr::VRApplication_Scene); // VRApplication_Background OR VRApplication_Scene OR VRApplication_Overlay OR VRApplication_Utility
		//	if (eError != vr::VRInitError_None)
		//	{
		//		vr_pointer = NULL;
		//		std::string error = VR_GetVRInitErrorAsEnglishDescription(eError);
		//		System::Err("Unable to init VR runtime: \"" + error + "\"");
		//	}
		//}
		if (Global::Variables.hasVR) {
			uint32_t unRequiredBufferLen = pHmd->GetStringTrackedDeviceProperty(unDevice, prop, NULL, 0, peError);
			if (unRequiredBufferLen == 0)
				return "";

			char* pchBuffer = new char[unRequiredBufferLen];
			unRequiredBufferLen = pHmd->GetStringTrackedDeviceProperty(unDevice, prop, pchBuffer, unRequiredBufferLen, peError);
			std::string sResult = pchBuffer;
			delete[] pchBuffer;
			return sResult;
		}
		else {
			return "INVALID";
		}
	}

	void VRHandler::Submit()
	{
		if (Global::Variables.hasVR) {
			app.submitFramesOpenGL(leftEyeTexture, rightEyeTexture);
		}
	}

	void VRHandler::Cleanup()
	{
		if (Global::Variables.hasVR) {
			vr::VR_Shutdown();
		}
	}
}
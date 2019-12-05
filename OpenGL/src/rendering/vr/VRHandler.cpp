#include "VRHandler.h"

namespace Atlas {

	static VRHandler::OpenVRApplication* app = NULL;
	static BasicRenderTarget* leftRT = NULL;
	static BasicRenderTarget* rightRT = NULL;
	static GLuint leftEyeTexture;
	static GLuint rightEyeTexture;

	void VRHandler::Setup()
	{
		if (Global::Variables.hasVR) {
			System::Log("Attempting to initialize OpenVRApplication");
			app = new OpenVRApplication();
			System::Log("Initialized OpenVRApplication");
			if (app->initialized) {
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
						System::Log("Generating left eye textures");
						glGenTextures(1, &leftEyeTexture);
						System::Log("Setting left eye texture storage type");
						glBindTexture(GL_TEXTURE_2D, leftEyeTexture);
						glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, app->rtWidth, app->rtHeight);
						//glTextureStorage2D(leftEyeTexture, 1, GL_RGBA8, app->rtWidth, app->rtHeight);

						System::Log("Generating right eye textures");
						glGenTextures(1, &rightEyeTexture);
						System::Log("Setting right eye texture storage type");
						glBindTexture(GL_TEXTURE_2D, rightEyeTexture);
						glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, app->rtWidth, app->rtHeight);
						//glTextureStorage2D(rightEyeTexture, 1, GL_RGBA8, app->rtWidth, app->rtHeight);

						leftRT = new BasicRenderTarget(1, app->rtWidth, app->rtHeight);
						rightRT = new BasicRenderTarget(1, app->rtWidth, app->rtHeight);

						System::Log("Completed initialization of both framebuffers and attached depth buffers!");

						System::Log("Attempting priming");
						leftRT->prime(leftEyeTexture);
						rightRT->prime(rightEyeTexture);
						System::Log("Finished priming");

						glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
						glBindFramebuffer(GL_FRAMEBUFFER, leftRT->fbo);
						//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

						GLenum temp = glCheckFramebufferStatus(GL_FRAMEBUFFER);
						switch (temp) {
						case GL_FRAMEBUFFER_COMPLETE:
							System::Log("Complete!");
							break;
						case GL_FRAMEBUFFER_UNDEFINED:
							System::Err("FRAMEBUFFER IS DEFAULT DRAW BUFFER AT INDEX 0!");
							break;
						case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
							System::Err("INCOMPLETE ATTACHMENT!");
							break;
						case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
							System::Err("INCOMPLETE MISSING ATTACHMENT!");
							break;
						case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
							System::Err("INCOMPLETE DRAW BUFFER!");
							break;
						case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
							System::Err("INCOMPLETE READ BUFFER!");
							break;
						case GL_FRAMEBUFFER_UNSUPPORTED:
							System::Err("UNSUPPORTED FRAMEBUFFER FORMAT!");
							break;
						case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
							System::Err("INCOMPLETE MULTISAMPLE");
							break;
						case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
							System::Err("INCOMPLETE LAYER TARGETS!");
							break;
						default:
							break;
						}
						//if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
						//{
						//	System::Err("Left RT Incomplete");
						//}

						glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
						glBindFramebuffer(GL_FRAMEBUFFER, rightRT->fbo);
						//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

						if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
						{
							System::Err("Right RT Incomplete");
						}

						glBindFramebuffer(GL_FRAMEBUFFER, 0);
					}
					catch (const std::exception & e) {
						System::Err("Fatal error, cannot initialize OpenVR display");
					}
				}
				else {
					System::Err("Cannot initialize OpenVR runtime, no headset detected!");
				}
			}
			else {
				System::Err("Error initializing OpenVR application");
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
			app->submitFramesOpenGL(leftEyeTexture, rightEyeTexture);
		}
	}

	void VRHandler::Cleanup()
	{
		if (Global::Variables.hasVR) {
			vr::VR_Shutdown();
		}
	}
}
#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <openvr.h>
#include <string>
#include "Target.h"
#include "Global.h"
#include "System.h"

namespace Atlas {
	class VRHandler {
	public:
		struct OpenVRApplication
		{
			vr::IVRSystem* hmd;
			uint32_t rtWidth;
			uint32_t rtHeight;

			OpenVRApplication() :
				hmd(NULL),
				rtWidth(0), rtHeight(0)
			{
				if (Global::Variables.hasVR) {
					if (!hmdIsPresent())
					{
						System::Err("Error : HMD not detected on the system");
					}

					if (!vr::VR_IsRuntimeInstalled())
					{
						System::Err("Error : OpenVR Runtime not detected on the system");
					}

					initVR();

					if (!vr::VRCompositor())
					{
						System::Err("Unable to initialize VR compositor!\n ");
					}

					hmd->GetRecommendedRenderTargetSize(&rtWidth, &rtHeight);

					System::Warn("Initialized HMD with suggested render target size: " + std::to_string(rtWidth) + "x" + std::to_string(rtHeight));
				}
			}

			inline static bool hmdIsPresent()
			{
				return vr::VR_IsHmdPresent();
			}

			virtual ~OpenVRApplication()
			{
				if (hmd)
				{
					vr::VR_Shutdown();
					hmd = NULL;
				}
			}

			void submitFramesOpenGL(GLint leftEyeTex, GLint rightEyeTex, bool linear = false)
			{
				if (!hmd)
				{
					System::Err("Error : presenting frames when VR system handle is NULL");
				}
				else {
					vr::TrackedDevicePose_t trackedDevicePose[vr::k_unMaxTrackedDeviceCount];
					vr::VRCompositor()->WaitGetPoses(trackedDevicePose, vr::k_unMaxTrackedDeviceCount, nullptr, 0);

					///\todo the documentation on this is completely unclear.  I have no idea which one is correct...
					/// seems to imply that we always want Gamma in opengl because linear is for framebuffers that have been
					/// processed by DXGI...
					vr::EColorSpace colorSpace = linear ? vr::ColorSpace_Linear : vr::ColorSpace_Gamma;

					vr::Texture_t leftEyeTexture = { (void*)leftEyeTex, vr::TextureType_OpenGL, colorSpace };
					vr::Texture_t rightEyeTexture = { (void*)rightEyeTex, vr::TextureType_OpenGL, colorSpace };

					vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture);
					vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture);

					vr::VRCompositor()->PostPresentHandoff();
				}
			}

			void handleVRError(vr::EVRInitError err)
			{
				System::Err(vr::VR_GetVRInitErrorAsEnglishDescription(err));
			}

			void initVR()
			{
				if (Global::Variables.hasVR) {
					vr::EVRInitError err = vr::VRInitError_None;
					hmd = vr::VR_Init(&err, vr::VRApplication_Scene);

					if (err != vr::VRInitError_None)
					{
						handleVRError(err);
					}

					System::Warn(GetTrackedDeviceString(hmd, vr::k_unTrackedDeviceIndex_Hmd, vr::Prop_TrackingSystemName_String));
					System::Warn(GetTrackedDeviceString(hmd, vr::k_unTrackedDeviceIndex_Hmd, vr::Prop_SerialNumber_String));
				}
			}
		};

		static void Setup();
		static std::string GetTrackedDeviceString(vr::IVRSystem* pHmd, vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop, vr::TrackedPropertyError* peError = NULL);
		static void Submit();
		static void Cleanup();
	};
}
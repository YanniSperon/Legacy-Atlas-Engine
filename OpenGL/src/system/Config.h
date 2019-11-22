#pragma once
#include <string>

namespace Engine {

	enum MouseMode {
		raw = 0, default = 1
	};

	class Config {
	private:
		bool fullscreen;
		bool forceFullscreen;
		bool vr;
		int initialWidth;
		int initialHeight;
		float mouseSensitivity;
		float FOV;
		bool vsync;
		MouseMode mouseMode;
	public:
		Config(std::string name);
		Config(std::string dir, std::string name);
		~Config();
		void ReadConfig(std::string dir, std::string name);
		void WriteConfig(std::string dir, std::string name);

		bool GetFullscreenPreference();
		void SetFullscreenPreference(bool newValue);

		bool GetVSyncPreference();
		void SetVSyncPreference(bool newValue);

		bool GetVRPreference();
		void SetVRPreference(bool newValue);

		bool GetForceFullscreen();
		void SetForceFullscreen(bool newValue);

		int GetInitialWidthPreference();
		void SetInitialWidthPreference(int newValue);

		int GetInitialHeightPreference();
		void SetInitialHeightPreference(int newValue);

		float GetMouseSensitivityPreference();
		void SetMouseSensitivityPreference(float newValue);

		float GetFOVPreference();
		void SetFOVPreference(float newValue);

		MouseMode GetMouseMode();
		void SetMouseMode(MouseMode newValue);
	};
}
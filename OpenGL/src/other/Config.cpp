#include "Config.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

Config::Config(std::string name)
{
	ReadConfig("", name);
}

Config::Config(std::string dir, std::string name)
{
	ReadConfig(dir, name);
}

Config::~Config()
{
	
}

void Config::ReadConfig(std::string dir, std::string name)
{
	fullscreen = false;
	vr = false;
	initialWidth = 1920;
	initialHeight = 1080;
	mouseSensitivity = 0.005f;
	FOV = 90.0f;
	vsync = 1;
	mouseMode = MouseMode::default;
	
	std::ifstream f(dir + name);

	if (!f.is_open()) {
		std::cout << "Config file: \"" << dir << name << "\" does not exist or could not be loaded.\n";
	}

	while (!f.eof())
	{
		std::string line;
		std::getline(f, line);

		if (line.find("#") != std::string::npos || line.size() == 0) {

		}
		else if (line.find("fullscreen=") != std::string::npos) {
			std::string value = line.substr(11);
			fullscreen = (bool)std::stoi(value);
		}
		else if (line.find("vsync=") != std::string::npos) {
			std::string value = line.substr(6);
			vsync = (bool)std::stoi(value);
		}
		else if (line.find("vr=") != std::string::npos) {
			std::string value = line.substr(3);
			vr = (bool)std::stoi(value);
		}
		else if (line.find("initialWidth=") != std::string::npos) {
			std::string value = line.substr(13);
			initialWidth = std::stoi(value);
		}
		else if (line.find("initialHeight=") != std::string::npos) {
			std::string value = line.substr(14);
			initialHeight = std::stoi(value);
		}
		else if (line.find("mouseSensitivity=") != std::string::npos) {
			std::string value = line.substr(17);
			mouseSensitivity = std::stof(value);
		}
		else if (line.find("FOV=") != std::string::npos) {
			std::string value = line.substr(4);
			FOV = std::stof(value);
		}
		else if (line.find("mouseMode=") != std::string::npos) {
			std::string value = line.substr(10);
			mouseMode = MouseMode(std::stoi(value));
		}
	}
}

void Config::WriteConfig(std::string dir, std::string name)
{
	printf("Saving to file: %s%s", dir.c_str(), name.c_str());
	std::ofstream outfile(dir + name);
	outfile << "#choose whether the application will launch in fullscreen or not\n";
	outfile << "fullscreen="<< std::to_string(fullscreen) << "\n";
	outfile << "\n";
	outfile << "#enable vsync\n";
	outfile << "vsync=" << std::to_string(vsync) << "\n";
	outfile << "\n";
	outfile << "#choose whether the application will attempt to connect to any available vr headset or not\n";
	outfile << "vr=" << std::to_string(vr) << "\n";
	outfile << "\n";
	outfile << "#choose the starting width of the window in pixels\n";
	outfile << "initialWidth=" << std::to_string(initialWidth) << "\n";
	outfile << "\n";
	outfile << "#choose the starting height of the window in pixels\n";
	outfile << "initialHeight=" << std::to_string(initialHeight) << "\n";
	outfile << "\n";
	outfile << "#choose the sensitivity, it is calculated by multiplying mouse position\n";
	outfile << "#and sensitivity to get the answer in degrees so 0.1-0.5 is recommended\n";
	outfile << "mouseSensitivity=" << std::to_string(mouseSensitivity) << "f\n";
	outfile << "\n";
	outfile << "#choose the starting fov\n";
	outfile << "FOV=" << std::to_string(FOV) << "f\n";
	outfile << "\n";
	outfile << "#set the mouse mode (raw = 0, default = 1) RAW NOT SUPPORTED BY EVERY SYSTEM\n";
	outfile << "mouseMode=" << std::to_string(mouseMode);
	outfile.close();
}

bool Config::GetFullscreenPreference()
{
	return fullscreen;
}

void Config::SetFullscreenPreference(bool newValue)
{
	fullscreen = newValue;
}

bool Config::GetVSyncPreference()
{
	return vsync;
}

void Config::SetVSyncPreference(bool newValue)
{
	vsync = newValue;
}

bool Config::GetVRPreference()
{
	return vr;
}

void Config::SetVRPreference(bool newValue)
{
	vr = newValue;
}

int Config::GetInitialWidthPreference()
{
	return initialWidth;
}

void Config::SetInitialWidthPreference(int newValue)
{
	initialWidth = newValue;
}

int Config::GetInitialHeightPreference()
{
	return initialHeight;
}

void Config::SetInitialHeightPreference(int newValue)
{
	initialHeight = newValue;
}

float Config::GetMouseSensitivityPreference()
{
	return mouseSensitivity;
}

void Config::SetMouseSensitivityPreference(float newValue)
{
	mouseSensitivity = newValue;
}

float Config::GetFOVPreference()
{
	return FOV;
}

void Config::SetFOVPreference(float newValue)
{
	FOV = newValue;
}

MouseMode Config::GetMouseMode()
{
	return mouseMode;
}

void Config::SetMouseMode(MouseMode newValue)
{
	mouseMode = newValue;
}
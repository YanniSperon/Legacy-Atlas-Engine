#include "System.h"
#include "Global.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include <iostream>
#include <chrono>
#include <Windows.h>
#include <fstream>

namespace Atlas {

	bool System::DoesFileExist(const std::string& filePath)
	{
		std::ifstream file(filePath);
		if (file.is_open() == true)
		{
			return true;
		}
		return false;
	}

	bool System::HasValidFileAttributes(const std::string& filePath)
	{
		DWORD attr = GetFileAttributes(filePath.c_str());
		if (attr == INVALID_FILE_ATTRIBUTES || (attr & FILE_ATTRIBUTE_DIRECTORY)) {
			return false;
		}
		else {
			return true;
		}
	}

	bool System::CopyFileAtlas(const std::string& originalFilePathAndName, const std::string& finalFilePath)
	{
		if (HasValidFileAttributes(originalFilePathAndName) && HasValidFileAttributes(finalFilePath)) {
			std::ifstream  src(originalFilePathAndName, std::ios::binary);
			std::ofstream  dst(finalFilePath, std::ios::binary);

			if (src.is_open() && dst.is_open()) {
				dst << src.rdbuf();
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}

	void System::Log(std::string text)
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - Global::Variables.systemStartTime);
		auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
		auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration - hours);
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration - hours - minutes);
		auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration - hours - minutes - seconds);
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration - hours - minutes - seconds - milliseconds);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		std::string outString = "";
		if (text.find("\n") != std::string::npos) {
			outString = std::to_string(hours.count()) + ":" + std::to_string(minutes.count()) + ":" + std::to_string(seconds.count()) + "." + std::to_string(milliseconds.count()) + std::to_string(microseconds.count()) + " -- LOG:  " + text;
		}
		else {
			outString = std::to_string(hours.count()) + ":" + std::to_string(minutes.count()) + ":" + std::to_string(seconds.count()) + "." + std::to_string(milliseconds.count()) + std::to_string(microseconds.count()) + " -- LOG:  " + text + "\n";
		}
		printf("%s", outString.c_str());
		if (Global::Variables.consoleLog.size() > 50) {
			Global::Variables.consoleLog.erase(Global::Variables.consoleLog.begin());
			Global::Variables.consoleLog.push_back(outString);
		}
		else {
			Global::Variables.consoleLog.push_back(outString);
		}
	}

	void System::Warn(std::string text)
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - Global::Variables.systemStartTime);
		auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
		auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration - hours);
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration - hours - minutes);
		auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration - hours - minutes - seconds);
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration - hours - minutes - seconds - milliseconds);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		std::string outString = "";
		if (text.find("\n") != std::string::npos) {
			outString = std::to_string(hours.count()) + ":" + std::to_string(minutes.count()) + ":" + std::to_string(seconds.count()) + "." + std::to_string(milliseconds.count()) + std::to_string(microseconds.count()) + " -- WARN: " + text;
		}
		else {
			outString = std::to_string(hours.count()) + ":" + std::to_string(minutes.count()) + ":" + std::to_string(seconds.count()) + "." + std::to_string(milliseconds.count()) + std::to_string(microseconds.count()) + " -- WARN: " + text + "\n";
		}
		printf("%s", outString.c_str());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		if (Global::Variables.consoleLog.size() > 50) {
			Global::Variables.consoleLog.erase(Global::Variables.consoleLog.begin());
			Global::Variables.consoleLog.push_back(outString);
		}
		else {
			Global::Variables.consoleLog.push_back(outString);
		}
	}

	void System::Err(std::string text)
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - Global::Variables.systemStartTime);
		auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
		auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration - hours);
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration - hours - minutes);
		auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration - hours - minutes - seconds);
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration - hours - minutes - seconds - milliseconds);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		std::string outString = "";
		if (text.find("\n") != std::string::npos) {
			outString = std::to_string(hours.count()) + ":" + std::to_string(minutes.count()) + ":" + std::to_string(seconds.count()) + "." + std::to_string(milliseconds.count()) + std::to_string(microseconds.count()) + " -- ERR:  " + text;
		}
		else {
			outString = std::to_string(hours.count()) + ":" + std::to_string(minutes.count()) + ":" + std::to_string(seconds.count()) + "." + std::to_string(milliseconds.count()) + std::to_string(microseconds.count()) + " -- ERR:  " + text + "\n";
		}
		printf("%s", outString.c_str());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		if (Global::Variables.consoleLog.size() > 50) {
			Global::Variables.consoleLog.erase(Global::Variables.consoleLog.begin());
			Global::Variables.consoleLog.push_back(outString);
		}
		else {
			Global::Variables.consoleLog.push_back(outString);
		}
	}

	void System::SendConsoleCommand(std::string command)
	{
		size_t slashPos;
		if ((slashPos = command.find("/")) != std::string::npos) {
			if (slashPos == 0 && command.size() > 1) {
				if (command.find(" ") != std::string::npos) {
					std::string firstWord = command.substr(1, command.find(" "));
					if (firstWord != " " && firstWord != "") {
						System::Log(firstWord);
					}
				}
				else {
					System::Log(command.substr(1));
				}
			}
		}

		// ACTUALLY PARSE COMMAND HERE
	}

	void System::DrawConsole()
	{
		static char InputConsoleString[128] = "";
		ImGui::Begin("Console", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::BeginChild("Log");
		for (int i = 0; i < Global::Variables.consoleLog.size(); i++) {
			std::string temp = Global::Variables.consoleLog[i];
			if (temp.find("WARN") != std::string::npos) {
				ImGui::TextColored(ImVec4(1, 1, 0, 1), "%s", temp.c_str());
			}
			else if (temp.find("ERR") != std::string::npos) {
				ImGui::TextColored(ImVec4(1, 0, 0, 1), "%s", temp.c_str());
			}
			else {
				ImGui::Text("%s", temp.c_str());
			}
		}
		ImGui::Text("");
		if (ImGui::InputText("", InputConsoleString, IM_ARRAYSIZE(InputConsoleString), ImGuiInputTextFlags_EnterReturnsTrue)) {
			if (InputConsoleString[0] != '\0') {
				SendConsoleCommand(std::string(InputConsoleString));
				InputConsoleString[0] = '\0';
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("Submit")) {
			if (InputConsoleString[0] != '\0') {
				SendConsoleCommand(std::string(InputConsoleString));
				InputConsoleString[0] = '\0';
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("Clear")) {
			Global::Variables.consoleLog.clear();
			for (int i = 0; i < 10; i++) {
				Global::Variables.consoleLog.push_back("");
			}
			System::Log("Console cleared!");
		}
		ImGui::SetScrollHere(1.0f);
		ImGui::EndChild();
		ImGui::End();
	}

	std::string System::FileOpenDialog(std::string label, LPCSTR filter, GLFWwindow* window)
	{
		char filename[MAX_PATH];

		OPENFILENAME ofn;
		ZeroMemory(&filename, sizeof(filename));
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = glfwGetWin32Window(window); // glfwGetWindowHandle();  // If you have a window to center over, put its HANDLE here
		ofn.lpstrFilter = filter; // "Any File\0*.*\0"
		ofn.lpstrFile = filename;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrTitle = const_cast<char*>(label.c_str());
		ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

		filename[0] = '\0';

		if (GetOpenFileNameA(&ofn))
		{
			return filename;
		}
		else
		{
			// All this stuff below is to tell you exactly how you messed up above. 
			// Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
			switch (CommDlgExtendedError())
			{
			case CDERR_DIALOGFAILURE: std::cout << "CDERR_DIALOGFAILURE\n";   break;
			case CDERR_FINDRESFAILURE: std::cout << "CDERR_FINDRESFAILURE\n";  break;
			case CDERR_INITIALIZATION: std::cout << "CDERR_INITIALIZATION\n";  break;
			case CDERR_LOADRESFAILURE: std::cout << "CDERR_LOADRESFAILURE\n";  break;
			case CDERR_LOADSTRFAILURE: std::cout << "CDERR_LOADSTRFAILURE\n";  break;
			case CDERR_LOCKRESFAILURE: std::cout << "CDERR_LOCKRESFAILURE\n";  break;
			case CDERR_MEMALLOCFAILURE: std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
			case CDERR_MEMLOCKFAILURE: std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
			case CDERR_NOHINSTANCE: std::cout << "CDERR_NOHINSTANCE\n";     break;
			case CDERR_NOHOOK: std::cout << "CDERR_NOHOOK\n";          break;
			case CDERR_NOTEMPLATE: std::cout << "CDERR_NOTEMPLATE\n";      break;
			case CDERR_STRUCTSIZE: std::cout << "CDERR_STRUCTSIZE\n";      break;
			case FNERR_BUFFERTOOSMALL: std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
			case FNERR_INVALIDFILENAME: std::cout << "FNERR_INVALIDFILENAME\n"; break;
			case FNERR_SUBCLASSFAILURE: std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
			default: std::cout << "You cancelled.\n";
			}
		}
		return "INVALID";
	}
}
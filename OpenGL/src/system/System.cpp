#include "System.h"
#include "Global.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "Convert.h"
#include <iostream>
#include <chrono>
#include <Windows.h>
#include <fstream>
#include <algorithm>
#include <sstream>

namespace Atlas {

	static std::string workingDir;

	std::vector<std::string> System::GetFilesInDirectory(const std::string& directory)
	{
		std::string correctDirectory = directory;
		if (directory.at(directory.size() - 1) != '*') {
			if (directory.at(directory.size() - 1) == '/') {
				correctDirectory = directory + "*";
			}
			else {
				correctDirectory = directory + "/*";
			}
		}
		std::vector<std::string> returnValue;

		WIN32_FIND_DATA data;
		LPCSTR dir = const_cast<char*>(correctDirectory.c_str());
		HANDLE hFind = FindFirstFile(dir, &data);      // DIRECTORY

		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					returnValue.push_back(data.cFileName);
				}
			} while (FindNextFile(hFind, &data) != 0);
			FindClose(hFind);
		}

		return returnValue;
	}

	std::string System::GetEXEDirectory()
	{
		char ownPth[MAX_PATH];
		HMODULE hModule = GetModuleHandle(NULL);
		ownPth[0] = '\0';
		if (hModule != NULL) {
			GetModuleFileName(hModule, ownPth, sizeof(ownPth));
		};
		
		std::string file(ownPth);
		std::replace(file.begin(), file.end(), '\\', '/');
		std::size_t lastSlashPos = file.find_last_of("/");
		std::string runningDir = "";
		std::string runningName = "";
		
		if (lastSlashPos != std::string::npos) {
			runningDir = file.substr(0, lastSlashPos + 1);
			runningName = file.substr(lastSlashPos + 1);
		}
		
		return runningDir;
	}

	std::string System::GetEXEName()
	{
		char ownPth[MAX_PATH];
		HMODULE hModule = GetModuleHandle(NULL);
		ownPth[0] = '\0';
		if (hModule != NULL) {
			GetModuleFileName(hModule, ownPth, sizeof(ownPth));
		};

		std::string file(ownPth);
		std::replace(file.begin(), file.end(), '\\', '/');
		std::size_t lastSlashPos = file.find_last_of("/");
		std::string runningDir = "";
		std::string runningName = "";

		if (lastSlashPos != std::string::npos) {
			runningDir = file.substr(0, lastSlashPos + 1);
			runningName = file.substr(lastSlashPos + 1);
		}
		else {
			runningName = file;
		}

		return runningName;
	}

	void System::SetWorkingDirectory()
	{
		std::string outString;
		{
			TCHAR path[MAX_PATH + 1] = "";
			DWORD len = GetCurrentDirectory(MAX_PATH, path);
			outString = std::string(&path[0]);
		}
		outString.append("\\");
		if (outString.find("\\") != std::string::npos) {
			std::replace(outString.begin(), outString.end(), '\\', '/');
		}
		workingDir = outString;
	}

	std::string System::GetWorkingDirectory()
	{
		return workingDir;
	}

	bool System::IsFilePathInWorkingDirectory(const std::string& filePath)
	{
		std::string correctFilePath = filePath;
		std::string currentWorkingDir = GetWorkingDirectory();
		if (correctFilePath.find("\\") != std::string::npos) {
			std::replace(correctFilePath.begin(), correctFilePath.end(), '\\', '/');
		}
		if (currentWorkingDir.find("\\") != std::string::npos) {
			std::replace(currentWorkingDir.begin(), currentWorkingDir.end(), '\\', '/');
		}
		if (correctFilePath.find(currentWorkingDir) != std::string::npos) {
			return true;
		}
		return false;
	}

	bool System::IsFilePathInEXEDirectory(const std::string& filePath)
	{
		std::string correctFilePath = filePath;
		std::string currentEXEDir = GetEXEDirectory();
		if (correctFilePath.find("\\") != std::string::npos) {
			std::replace(correctFilePath.begin(), correctFilePath.end(), '\\', '/');
		}
		if (currentEXEDir.find("\\") != std::string::npos) {
			std::replace(currentEXEDir.begin(), currentEXEDir.end(), '\\', '/');
		}
		if (correctFilePath.find(currentEXEDir) != std::string::npos) {
			return true;
		}
		return false;
	}

	std::string System::ConvertFilePathToAbsolute(const std::string& localFilePath)
	{
		std::string correctFilePath = localFilePath;
		if (correctFilePath.find("\\") != std::string::npos) {
			std::replace(correctFilePath.begin(), correctFilePath.end(), '\\', '/');
		}
		if (IsFilePathInWorkingDirectory(correctFilePath)) {
			return correctFilePath;
		}
		else {
			return GetWorkingDirectory() + correctFilePath;
		}
	}

	std::string System::ConvertFilePathToLocal(const std::string& absoluteFilePath)
	{
		std::string correctFilePath = absoluteFilePath;
		if (correctFilePath.find("\\") != std::string::npos) {
			std::replace(correctFilePath.begin(), correctFilePath.end(), '\\', '/');
		}
		if (IsFilePathInWorkingDirectory(correctFilePath)) {
			return correctFilePath.substr(GetWorkingDirectory().size());
		}
		else {
			return correctFilePath;
		}
	}

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
		if (DoesFileExist(originalFilePathAndName) && HasValidFileAttributes(originalFilePathAndName)) {
			if (!DoesFileExist(finalFilePath)) {
				std::ifstream src(originalFilePathAndName, std::ios::binary);
				std::ofstream dst(finalFilePath, std::ios::binary);

				if (src.is_open() && dst.is_open()) {
					dst << src.rdbuf();
					System::Log("Successfully copied \"" + originalFilePathAndName + "\" to \"" + finalFilePath + "\"");
					return true;
				}
				else {
					System::Err("Error opening streams while copying \"" + originalFilePathAndName + "\" to \"" + finalFilePath + "\"");
					return false;
				}
			}
			else {
				System::Err("This file already exists!");
				return false;
			}
		}
		else {
			System::Err("Cannot copy \"" + originalFilePathAndName + "\" to \"" + finalFilePath + "\" as it does not exist or the file attributes are invalid!");
			return false;
		}
	}

	void System::Log(const std::string& text)
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

	void System::Warn(const std::string& text)
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

	void System::Err(const std::string& text)
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

	void System::SendConsoleInput(const std::string& input)
	{
		std::vector<std::string> args;
		std::string command;
		if ((input.find("/") != std::string::npos) && (input.find("/") == 0 && input.size() > 1)) {
			std::string StringWithoutSlash = input.substr(1);
			std::vector<std::string> temp = Convert::SeperateByDelimiter(Convert::FormatSpaces(Convert::Trim(StringWithoutSlash)), ' ');
			if (temp.size() > 0) {
				command = temp.at(0);
				for (unsigned int i = 1; i < temp.size(); i++) {
					args.push_back(temp.at(i));
				}
			}
		}
		else {
			System::Log(input);
		}
		/*
		vector<string> internal;
		stringstream ss(str); // Turn the string into a stream.
		string tok;
		
		while(getline(ss, tok, delimiter)) {
		  internal.push_back(tok);
		}
		
		return internal;
		*/

		/*
		for (short i = 0; i<str.length(); i++){
			if (str[i] == ' ')
				counter++;
			else {
				strWords[counter] += str[i];
			}
		}
		*/
	}

	void System::DrawConsole()
	{
		static char InputConsoleString[128] = "";
		ImGui::SetNextWindowPos(ImVec2((20.0f / 1920.0f) * ((float)Global::Variables.currentWidth), (860.0f / 1080.0f) * ((float)Global::Variables.currentHeight)));
		ImGui::SetNextWindowSize(ImVec2((750.0f / 1920.0f) * ((float)Global::Variables.currentWidth), (200.0f / 1080.0f) * ((float)Global::Variables.currentHeight)));
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
				SendConsoleInput(std::string(InputConsoleString));
				InputConsoleString[0] = '\0';
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("Submit")) {
			if (InputConsoleString[0] != '\0') {
				SendConsoleInput(std::string(InputConsoleString));
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

	std::string System::FileOpenDialog(const std::string& label, LPCSTR filter, GLFWwindow* window)
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

	Filepath System::SeperateFilepath(const std::string& filePath)
	{
		std::size_t lastSlashPos = filePath.find_last_of("/");
		std::string dir = "";
		std::string name = "";
		if (lastSlashPos != std::string::npos) {
			dir = filePath.substr(0, lastSlashPos + 1);
			name = filePath.substr(lastSlashPos + 1);
		}
		else {
			name = filePath;
		}
		return Filepath(dir, name);
	}
}
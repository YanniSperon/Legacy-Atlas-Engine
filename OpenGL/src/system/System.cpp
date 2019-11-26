#include "System.h"
#include "Global.h"
#include <iostream>
#include <chrono>
#include <Windows.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

namespace Atlas {

	
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
		System::Log("Executing console command: \"" + command + "\"");

		// ACTUALLY PARSE COMMAND HERE
	}

	void System::DrawConsole()
	{
		static char InputConsoleString[128] = "";
		ImGui::Begin("Console", NULL, ImGuiWindowFlags_NoCollapse| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
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
			SendConsoleCommand(std::string(InputConsoleString));
			InputConsoleString[0] = '\0';
		}
		ImGui::SameLine();
		if (ImGui::Button("Submit")) {
			SendConsoleCommand(std::string(InputConsoleString));
			InputConsoleString[0] = '\0';
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
}
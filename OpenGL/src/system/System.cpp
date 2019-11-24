#include "System.h"
#include "Global.h"
#include <iostream>
#include <chrono>
#include <Windows.h>

namespace Engine {

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
		if (text.find("\n") != std::string::npos) {
			std::cout << hours.count() << ":" << minutes.count() << ":" << seconds.count() << "." << milliseconds.count() << microseconds.count() << " -- LOG:  " << text;
		}
		else {
			std::cout << hours.count() << ":" << minutes.count() << ":" << seconds.count() << "." << milliseconds.count() << microseconds.count() << " -- LOG:  " << text << "\n";
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
		if (text.find("\n") != std::string::npos) {
			std::cout << hours.count() << ":" << minutes.count() << ":" << seconds.count() << "." << milliseconds.count() << microseconds.count() << " -- WARN: " << text;
		}
		else {
			std::cout << hours.count() << ":" << minutes.count() << ":" << seconds.count() << "." << milliseconds.count() << microseconds.count() << " -- WARN: " << text << "\n";
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
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
		if (text.find("\n") != std::string::npos) {
			std::cout << hours.count() << ":" << minutes.count() << ":" << seconds.count() << "." << milliseconds.count() << microseconds.count() << " -- ERR:  " << text;
		}
		else {
			std::cout << hours.count() << ":" << minutes.count() << ":" << seconds.count() << "." << milliseconds.count() << microseconds.count() << " -- ERR:  " << text << "\n";
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
}
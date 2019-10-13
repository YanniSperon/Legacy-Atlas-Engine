#include "Timer.h"
#include <iostream>

Timer::Timer(float lengthInSeconds)
	: currentTime(0.0f), lengthTime(lengthInSeconds), isRunning(false)
{

}

void Timer::ElapseTime(float deltaT)
{
	if (isRunning) {
		currentTime += deltaT;
	}
}

bool Timer::HasFinished()
{
	if (isRunning && currentTime >= lengthTime) {
		return true;
	}
	else {
		return false;
	}
}

void Timer::Reset(float lengthInSeconds)
{
	currentTime = 0.0f;
	lengthTime = lengthInSeconds;
	isRunning = false;
}

bool Timer::IsRunning()
{
	return isRunning;
}

void Timer::Start()
{
	isRunning = true;
}

void Timer::Stop()
{
	isRunning = false;
}

Timer::~Timer()
{

}
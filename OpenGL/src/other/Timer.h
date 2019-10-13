#pragma once

class Timer {
private:
	float currentTime;
	float lengthTime;
	bool isRunning;
public:
	Timer(float lengthInSeconds);
	void ElapseTime(float deltaT);
	bool HasFinished();
	void Reset(float lengthInSeconds);
	bool IsRunning();
	void Start();
	void Stop();
	~Timer();
};
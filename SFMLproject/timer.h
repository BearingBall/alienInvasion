#pragma once
#include <chrono>

class Timer final
{
private:
	double secondsToWait;
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
public:
	Timer(double _secondsToWait = 0.2): secondsToWait(_secondsToWait) {}
	~Timer() = default;
	double& getTime();
	bool isTimerOut();
};
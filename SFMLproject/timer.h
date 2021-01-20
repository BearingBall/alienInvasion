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

	bool isTimerOut()
	{
		std::chrono::high_resolution_clock::time_point current = std::chrono::high_resolution_clock::now();
		auto differentTime = std::chrono::duration<double>(current - start).count();
		if (secondsToWait < static_cast<double>(differentTime))
		{
			start = current;
			return true;
		}
		return false;
	}
	
	
};
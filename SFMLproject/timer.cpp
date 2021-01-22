#include "timer.h"

double& Timer::getTime()
{
	return secondsToWait;
}

bool Timer::isTimerOut()
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

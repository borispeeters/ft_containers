#include "Timer.hpp"

Timer::Timer() {
	m_StartTime = std::chrono::system_clock::now();
}

Timer::~Timer() {
	m_EndTime = std::chrono::system_clock::now();
	std::cout << "Execution time: " << elapsedMilliseconds() << "ms" << std::endl;
}

double Timer::elapsedMilliseconds() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(m_EndTime - m_StartTime).count();
}

double Timer::elapsedSeconds() {
	return elapsedMilliseconds() / 1000.0;
}

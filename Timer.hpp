#ifndef TIMER_HPP
# define TIMER_HPP

# include <chrono>
# include <iostream>

class Timer
{
public:
	Timer();
	~Timer();

	double elapsedMilliseconds();
	double elapsedSeconds();

private:
	std::chrono::time_point<std::chrono::system_clock> m_StartTime;
	std::chrono::time_point<std::chrono::system_clock> m_EndTime;
};

#endif

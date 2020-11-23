#ifndef TIMER_HPP
# define TIMER_HPP

# include <ctime>
# include <iostream>

class Timer
{
	struct timeval	tv;
	std::size_t		start;
	std::size_t		end;

public:
	Timer();
	~Timer();
};

#endif

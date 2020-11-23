#include <sys/time.h>
#include "Timer.hpp"

Timer::Timer() {
	gettimeofday(&tv, NULL);
	start = tv.tv_usec / 1000;
}

Timer::~Timer() {
	gettimeofday(&tv, NULL);
	end = tv.tv_usec / 1000;

	std::cout << "start: " << start << std::endl;
	std::cout << "end: " << end << std::endl;

	std::cout << "Execution time: " << end - start << "ms" << std::endl;
}

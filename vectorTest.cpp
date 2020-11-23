#include <iostream>
#include <vector>
#include "vector.hpp"
#include "Timer.hpp"

int main()
{
	ft::vector<int>				ve;
	ft::vector<int>::iterator	it;
	for (int i = 0; i < 10000000; ++i)
		ve.push_back(i);

	// std::cout << "ve contains:";
	// for (it = ve.begin(); it != ve.end(); ++it)
	// 	std::cout << ' ' << *it;
	// std::cout << '$' << std::endl;

	return 0;
}

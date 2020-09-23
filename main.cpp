#include <iostream>
#include <vector>
#include "vector.hpp"

int main ()
{
	ft::vector<int>	vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);

	ft::vector<int>	fill(4, 42);

	ft::vector<int>	range(vec.begin(), vec.end());

	for (int value : fill)
		std::cout << "fill: " << value << std::endl;

	std::cout << std::endl;

	for (int value : range)
		std::cout << "range: " << value << std::endl;

	return 0;
}

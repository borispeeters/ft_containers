#include <exception>
#include <iostream>
#include <vector>
#include "vector.hpp"

int main ()
{
	std::vector<int>	vec1;
	for (int i = 1; i <= 6; ++i)
		vec1.push_back(i);

	std::vector<int>	vec2;
	for (int i = 1; i <= 6; ++i)
		vec2.push_back(i);

	if (vec1 == vec2)
		std::cout << "equal" << std::endl;

	return 0;
}

#include <exception>
#include <iostream>
#include <vector>
#include "vector.hpp"

int main ()
{
	ft::vector<int>	vec1(3, 88);
	ft::vector<int>	vec2(4, 42);

	std::cout << "before swap" << std::endl;

	std::cout << "vec1:";
	for (int value : vec1)
		std::cout << ' ' << value;
	std::cout << std::endl;

	std::cout << "vec2:";
	for (int value : vec2)
		std::cout << ' ' << value;
	std::cout << std::endl;

	ft::swap(vec1, vec2);

	std::cout << "after swap" << std::endl;

	std::cout << "vec1:";
	for (int value : vec1)
		std::cout << ' ' << value;
	std::cout << std::endl;

	std::cout << "vec2:";
	for (int value : vec2)
		std::cout << ' ' << value;
	std::cout << std::endl;

	return 0;
}

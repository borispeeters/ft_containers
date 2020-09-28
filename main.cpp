#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "vector.hpp"


int main ()
{
	int myInts[] = {1,2,3,4,5,6};

	ft::vector<int>	vc;
	for (int i = 1; i <= 6; ++i)
		vc.push_back(i);

	ft::vector<int>	fill(3, 88);
	ft::vector<int>	range(myInts, myInts + 5);


	for (int value : fill)
		std::cout << "fill: " << value << std::endl;

	std::cout << std::endl;

	for (int value : range)
		std::cout << "range: " << value << std::endl;

	return 0;
}

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "vector.hpp"

int main ()
{
	ft::vector<int>	k;

	for (int i = 0; i < 6; ++i)
		k.push_back(i);

	ft::vector<int>	vc(k.begin(), k.end());

	for (int value : vc)
		std::cout << value << std::endl;

	return 0;
}

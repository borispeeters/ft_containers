#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "vector.hpp"

int main ()
{
	ft::vector<int>	vc;
	vc.push_back(1);
	vc.push_back(2);
	vc.push_back(3);
	vc.push_back(4);
	vc.push_back(5);

	ft::vector<int>		fill(4, 42);
	ft::vector<int>		range(vc.begin(), vc.end());

	return 0;
}

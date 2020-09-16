#include <iostream>
#include <string>
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


	ft::vector<int>::iterator it = vec.begin();
	it += 3;
	vec.insert(it, 3, 42);

	for (int value : vec)
		std::cout << value << std::endl;

	std::cout << "size: " << vec.size() << std::endl;


	return 0;
}

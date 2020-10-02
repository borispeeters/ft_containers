#include <iostream>
#include <stack>
#include <vector>
#include "stack.hpp"

int main ()
{
	ft::stack<int, std::vector<int> >	first, second;

	for (int i = 1; i <= 6; ++i)
	{
		first.push(i);
		second.push(i);
	}

	second.pop();

	if (first == second)
		std::cout << "first is equal to second" << std::endl;
	if (first != second)
		std::cout << "first is NOT equal to second" << std::endl;
	if (first < second)
		std::cout << "first is smaller than second" << std::endl;
	if (first <= second)
		std::cout << "first is smaller than or equal to second" << std::endl;
	if (first > second)
		std::cout << "first is bigger than second" << std::endl;
	if (first >= second)
		std::cout << "first is bigger than or equal to second" << std::endl;


//	system("leaks ft_containers");

	return 0;
}

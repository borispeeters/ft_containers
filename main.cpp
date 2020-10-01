#include <iostream>
#include <list>
#include "list.hpp"

int main ()
{
	ft::list<int>	li;

	li.push_front(42);

	li.assign(7, 100);

	std::cout << "size: " << li.size() << std::endl;

	ft::list<int>::iterator it = li.begin();

	while (it != li.end())
	{
		std::cout << *it << std::endl;
		++it;
	}

	return 0;
}

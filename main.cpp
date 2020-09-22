//#include <iostream>
//#include <string>
//#include <vector>
//#include <deque>
//#include "vector.hpp"
//
//int main ()
//{
//	ft::vector<int>	x(4, 42);
//	ft::vector<int>	y(3, 108);
//
//	x.swap(y);
//
//	std::cout << "x containts:";
//
//	for (int value : x)
//		std::cout << ' ' << value;
//
//	std::cout << std::endl;
//
//	std::cout << "y contains:";
//
//	for (int value : y)
//		std::cout << ' ' << value;
//
//	std::cout << std::endl;
//
//	std::cout << "X - size: " << x.size() << ", capacity: " << x.capacity() << std::endl;
//	std::cout << "Y - size: " << y.size() << ", capacity: " << y.capacity() << std::endl;
//
//
//	return 0;
//}


// iterator_traits example
#include <iostream>     // std::cout
#include "iterator.hpp"     // ft::iterator_traits
#include <typeinfo>     // typeid

int main()
{
	if (typeid(ft::iterator_traits<int *>::iterator_category)==typeid(ft::random_access_iterator_tag))
		std::cout << "int* is a random-access iterator";
	return 0;
}

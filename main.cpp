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



#include <iostream>

long multiply(long i, long j) {
	std::cout << "long version" << std::endl;
	return i * j;
}

template <class T>
T multiply(T t1, T t2)
{
	std::cout << "templated version" << std::endl;
	return t1 * t2;
}
int main(void)
{
	std::cout << multiply(4,5) << std::endl;
}

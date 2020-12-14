#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "vector.hpp"

#define PRINT(x) print(x, #x)
#define PRINTR(x) printr(x, #x)

template <class T>
void	print(T const & t, char const * s)
{
	typename T::const_iterator	it;

	std::cout << std::setw(3) << s << " contains:";
	for (it = t.begin(); it != t.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;
}

template <class T>
void 	printr(T const & t, char const * s)
{
	typename T::const_reverse_iterator	itr;

	std::cout << std::setw(3) << s << " in reverse:";
	for (itr = t.rbegin(); itr != t.rend(); ++itr)
		std::cout << ' ' << *itr;
	std::cout << std::endl;
}

struct	Foo
{
	Foo() { std::cout << 'a'; }
	Foo(Foo const &) {std::cout << 'b'; }
};

int		main()
{
	{
		std::vector<int>	std;
		ft::vector<int>		ft;

		if (std.empty()) std::cout << "std is empty" << std::endl;
		if (ft.empty()) std::cout << " ft is empty" << std::endl;

		std::cout << "capacity of std is: " << std.capacity() << std::endl;
		std::cout << "capacity of ft  is: " << ft.capacity() << std::endl;

		std::cout << "max size of std(int) is: " << std.max_size() << std::endl;
		std::cout << "max size of ft(int)  is: " << ft.max_size() << std::endl;
	}

	std::cout << std::endl;

	{
		std::vector<char>	std(3, '*');
		ft::vector<char>	ft(3, '*');

		PRINT(std);
		PRINT(ft);
	}

	return 0;
}

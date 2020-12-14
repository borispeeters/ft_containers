#include <iomanip>
#include <iostream>
#include <string>
#include <map>
#include "map.hpp"

#define PRINT(x) print(x, #x)
#define PRINTR(x) printr(x, #x)

template <class T>
void	print(T const & t, char const * s)
{
	typename T::const_iterator	it;

	std::cout << std::setw(3) << s << " contains:";
	for (it = t.begin(); it != t.end(); ++it)
		std::cout << " (" << it->first << " => " << it->second << ')';
	std::cout << std::endl;
}

template <class T>
void 	printr(T const & t, char const * s)
{
	typename T::const_reverse_iterator	itr;

	std::cout << std::setw(3) << s << " in reverse:";
	for (itr = t.rbegin(); itr != t.rend(); ++itr)
		std::cout << " (" << itr->first << " => " << itr->second << ')';
	std::cout << std::endl;
}

int		main()
{
	{
		ft::map<int, int>	ft;

		ft.insert(ft::make_pair(2, 2));
		ft.insert(ft::make_pair(1, 1));
		ft.insert(ft::make_pair(3, 3));

		ft::map<int, int>	x;

		x.insert(ft::make_pair(25, 25));
		x.insert(ft::make_pair(50, 50));
		x.insert(ft::make_pair(75, 75));
		x.insert(ft::make_pair(100, 100));

		PRINT(ft);
		PRINT(x);
	}

	return 0;
}

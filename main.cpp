#include <iostream>
#include <map>
#include <string>
#include "map.hpp"

int main ()
{
	ft::map<char, std::string>	mp;


	mp['a'] = "first element";
	mp['b'] = "second element";
	mp['c'] = "third element";
	mp['d'] = "last element";

	std::cout << "sup bro" << std::endl;


	ft::map<char, std::string>::iterator it;

	it = mp.begin();

	while (it != mp.end())
	{
		std::cout << it->second << std::endl;
		++it;
	}

//	system("leaks ft_containers");

	return 0;
}

#include <iostream>
#include <map>
#include <string>
#include "map.hpp"

int main ()
{
	ft::map<char, std::string>	mp;

	mp['a'] = "an element";
	mp['b'] = "another element";
	mp['c'] = mp['b'];

	std::cout << "mp contains " << mp.size() << " elements." << std::endl;

	std::cout << "mp['a'] is " << mp['a'] << std::endl;
	std::cout << "mp['b'] is " << mp['b'] << std::endl;
	std::cout << "mp['c'] is " << mp['c'] << std::endl;
	std::cout << "mp['d'] is " << mp['d'] << std::endl;

	std::cout << "mp now contains " << mp.size() << " elements." << std::endl;

//	system("leaks ft_containers");

	return 0;
}

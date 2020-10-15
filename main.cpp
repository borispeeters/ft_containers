#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "list.hpp"
#include "map.hpp"

template <class T>
void check_insertion(T const & t)
{
	if (t.second)
		std::cout << "A new element was inserted in the map" << std::endl;
	else
		std::cout << "An existing element with the same key already existed in the map" << std::endl;
}

int main ()
{
	std::vector<int>	ve;
	ve.push_back(1);
	ve.push_back(2);
	ve.push_back(3);

	ft::list<int>	li(ve.begin(), ve.end());

	ft::list<int>::const_iterator it;

//	for (it = li.begin(); it != li.end(); ++it)
//		std::cout << *it << std::endl;


/*																		*\
**	------------------------------------------------------------------	**
\*																		*/


	std::map<char, std::string>	mp;
	std::pair<ft::map<char, std::string>::iterator, bool>	p;

	std::map<char, std::string>::iterator mit;

	mp.insert(std::make_pair('A', "test lol"));
	mp.insert(std::make_pair('B', "another test lol"));
	mp.insert(std::make_pair('C', "final test lol"));

	mit = mp.end();

	--mit;

	std::cout << "-first-" << std::endl;
	mp.insert(mit, std::make_pair('a', "first element"));
	std::cout << "-second-" << std::endl;
	mp.insert(mit, std::make_pair('b', "second element"));
	std::cout << "-third-" << std::endl;
	mp.insert(mit, std::make_pair('c', "third element"));
	std::cout << "-last-" << std::endl;
	mp.insert(mit, std::make_pair('d', "last element"));
	std::cout << "-done motherfuckers-" << std::endl;

//	mp['a'] = "first element";
//	mp['b'] = "second element";
//	mp['c'] = "third element";
//	mp['d'] = "last element";

//	p = mp.insert(std::make_pair('a', "first element")); check_insertion(p);
//	p = mp.insert(std::make_pair('b', "second element")); check_insertion(p);
//	p = mp.insert(std::make_pair('c', "third element")); check_insertion(p);
//	p = mp.insert(std::make_pair('d', "last element")); check_insertion(p);

//	p = mp.insert(std::make_pair('a', "lol this not good")); check_insertion(p);

	std::cout << std::endl << "this boi has a size of " << mp.size() << std::endl << std::endl;


	for (mit = mp.begin(); mit != mp.end(); ++mit)
		std::cout << mit->first << " => " << mit->second << std::endl;


/*																		*\
**	------------------------------------------------------------------	**
\*																		*/

//	system("leaks ft_containers");

	return 0;
}

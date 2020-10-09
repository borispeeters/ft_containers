#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "list.hpp"
#include "map.hpp"

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


	ft::map<char, std::string>	mp;

	mp.insert(std::make_pair('a', "first element"));
	mp.insert(std::make_pair('b', "second element"));
	mp.insert(std::make_pair('c', "third element"));
	mp.insert(std::make_pair('d', "last element"));

	ft::map<char, std::string>::iterator mit = mp.begin();
	for (mit = mp.begin(); mit != mp.end(); ++mit)
		std::cout << mit->first << " has a value of " << mit->second << std::endl;

//	system("leaks ft_containers");

	return 0;
}

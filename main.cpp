#include <iostream>
#include <deque>
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


	std::map<char, std::string>	mp;
	std::map<char, std::string>::iterator mit;

//	mp.insert(std::make_pair('A', "test lol"));
//	mp.insert(std::make_pair('B', "another test lol"));
//	mp.insert(std::make_pair('C', "final test lol"));


//	mp['a'] = "first element";
//	mp['b'] = "second element";
//	mp['c'] = "third element";
//	mp['d'] = "last element";

//	mp.insert(std::make_pair('a', "first element"));
//	mp.insert(std::make_pair('b', "second element"));
//	mp.insert(std::make_pair('c', "third element"));
//	mp.insert(std::make_pair('d', "last element"));

//	std::cout << std::endl << "this boi has a size of " << mp.size() << std::endl << std::endl;


//	for (mit = mp.begin(); mit != mp.end(); ++mit)
//		std::cout << mit->first << " => " << mit->second << std::endl;


/*																		*\
**	------------------------------------------------------------------	**
\*																		*/

std::deque<int>	de;
std::deque<int>::iterator itd;

de.push_back(42);
de.push_back(8);
de.push_back(19);
de.push_back(24);

de.resize(7);

for (int value : de)
	std::cout << value << std::endl;


/*																		*\
**	------------------------------------------------------------------	**
\*																		*/


//	system("leaks ft_containers");

	return 0;
}

#include <iostream>
#include <deque>
#include <map>
#include <string>
#include <vector>
#include <list>
#include "list.hpp"
#include "map.hpp"

#include <algorithm>

void	my_relational_operators() {
	ft::list<std::string> myList;
	ft::list<std::string> otherList(6, "");
	if (myList == otherList)
		std::cout << "mylist == otherlist" << std::endl;
	if (myList != otherList)
		std::cout << "mylist != otherlist" << std::endl;
	if (myList < otherList)
		std::cout << "mylist < otherlist" << std::endl;
	if (myList > otherList)
		std::cout << "mylist > otherlist" << std::endl;
	if (myList <= otherList)
		std::cout << "mylist <= otherlist" << std::endl;
	if (myList >= otherList)
		std::cout << "mylist >= otherlist" << std::endl;
}

void	relational_operators() {
	std::list<std::string> myList;
	std::list<std::string> otherList(6, "");
	if (myList == otherList)
		std::cout << "mylist == otherlist" << std::endl;
	if (myList != otherList)
		std::cout << "mylist != otherlist" << std::endl;
	if (myList < otherList)
		std::cout << "mylist < otherlist" << std::endl;
	if (myList > otherList)
		std::cout << "mylist > otherlist" << std::endl;
	if (myList <= otherList)
		std::cout << "mylist <= otherlist" << std::endl;
	if (myList >= otherList)
		std::cout << "mylist >= otherlist" << std::endl;
}

int main ()
{
	std::cout << "std: " << std::endl;
	relational_operators();
	std::cout << std::endl << "ft: " << std::endl;
	my_relational_operators();

	return 0;

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
	ft::map<char, std::string>::iterator mit;

//	mp.insert(std::make_pair('A', "test lol"));
//	mp.insert(std::make_pair('B', "another test lol"));
//	mp.insert(std::make_pair('C', "final test lol"));


//	mp['a'] = "first element";
//	mp['b'] = "second element";
//	mp['c'] = "third element";
//	mp['d'] = "last element";

	mp.insert(std::make_pair('c', "lol"));
	mp.insert(std::make_pair('b', "lol"));
	mp.insert(std::make_pair('d', "lol"));
	mp.insert(std::make_pair('a', "lol"));

	mp.erase(mp.find('a'));
	mp.erase(mp.find('d'));
	mp.erase(mp.find('b'));
	mp.erase(mp.find('c'));

	mp.printBT();

//	mp.insert(mit, std::make_pair('c', "second element"));
//	mp.insert(mit, std::make_pair('e', "third element"));
//	mp.insert(mit, std::make_pair('a', "first element"));
//	mp.insert(mit, std::make_pair('g', "last element"));

//	std::cout << std::endl << "After insertions the map has a size of " << mp.size();
//
//	mp.erase(mp.begin());
//	mit = mp.begin();
//	++mit;
//
//	std::cout << std::endl << "After erase the map has a size of " << mp.size();
//	std::cout << std::endl << std::endl;



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

//for (int value : de)
//	std::cout << value << std::endl;


/*																		*\
**	------------------------------------------------------------------	**
\*																		*/

//	system("leaks ft_containers");

	return 0;
}

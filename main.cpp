#include <iostream>
#include <deque>
#include <map>
#include <string>
#include <vector>
#include "vector.hpp"
#include <list>
#include "list.hpp"
#include "map.hpp"

#include <algorithm>
#include <iterator>

void lol()
{
	std::map<int, int>			mymap;
	std::map<int, int>::iterator it;

	mymap[8] = 8;
	mymap[3] = 3;
	mymap[10] = 10;
	mymap[1] = 1;
	mymap[6] = 6;
	mymap[14] = 14;
	mymap[7] = 7;
	mymap[13] = 13;

	it = mymap.find(13);
	--it;
	std::cout << "*it = " << it->first << " >= " << it->second << std::endl;
}

void list_splice()
{
	std::list<int>	l1;
	for (int i = 1; i <= 5; ++i)
		l1.push_back(i);

	std::list<int>	l2;
	for (int i = 8; i <= 10; ++i)
		l2.push_front(i);

	std::list<int>::iterator	i1 = l1.begin();
	++i1;

	std::list<int>::iterator	i2 = l2.begin();
	++i2;

	l1.splice(i1, l2, i2);

	std::cout << "l1 size: " << l1.size() << std::endl;
	std::cout << "l2 size: " << l2.size() << std::endl;

	std::cout << std::endl;

	std::cout << "l1 contains: " << std::endl;
	for (int value : l1)
		std::cout << value << std::endl;

	std::cout << std::endl;

	std::cout << "l2 contains: " << std::endl;
	for (int value : l2)
		std::cout << value << std::endl;

//	system("leaks ft_containers");
}

int main ()
{
	list_splice();
//	lol();
	return 0;

	ft::vector<int> first(3,100);   // three ints with a value of 100
	ft::vector<int> second(5,200);  // five ints with a value of 200

	first.swap(second);

	std::cout << "first contains:";
	for (ft::vector<int>::iterator it=first.begin(); it != first.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "second contains:";
	for (ft::vector<int>::iterator it=second.begin(); it!=second.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';


//	system("leaks ft_containers");

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

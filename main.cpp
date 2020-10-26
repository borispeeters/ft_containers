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

void list_splice_print(ft::list<int> & mylist1, ft::list<int> & mylist2)
{
	ft::list<int>::iterator it;

	std::cout << "mylist1 contains:";
	for (it = mylist1.begin(); it!=mylist1.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "mylist2 contains:";
	for (it = mylist2.begin(); it!=mylist2.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << std::endl;
}

void list_splice()
{
	ft::list<int> mylist1, mylist2;
	ft::list<int>::iterator it;

	// set some initial values:
	for (int i=1; i<=4; ++i)
		mylist1.push_back(i);      // mylist1: 1 2 3 4

	for (int i=1; i<=3; ++i)
		mylist2.push_back(i*10);   // mylist2: 10 20 30

	list_splice_print(mylist1, mylist2);

	it = mylist1.begin();
	++it;                         // points to 2

	mylist1.splice (it, mylist2); // mylist1: 1 10 20 30 2 3 4

	list_splice_print(mylist1, mylist2);

	// mylist2 (empty)
	// "it" still points to 2 (the 5th element)
	std::cout << "it points to: " << *it << '\n' << std::endl;

	mylist2.splice (mylist2.begin(),mylist1, it);

	list_splice_print(mylist1, mylist2);

	// mylist1: 1 10 20 30 3 4
	// mylist2: 2
	// "it" is now invalid.
	it = mylist1.begin();
	++it; ++it; ++it;
	std::cout << "it points to: " << *it << '\n' << std::endl;

//	std::advance(it,3);           // "it" points now to 30

	mylist1.splice ( mylist1.begin(), mylist1, it, mylist1.end());
	// mylist1: 30 3 4 1 10 20

	list_splice_print(mylist1, mylist2);

//	system("leaks ft_containers");
}

// compare only integral part:
bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }

void list_merge()
{
	ft::list<double> first, second;

	first.push_back (2.2);
	first.push_back (2.9);
	first.push_back (3.1);

	second.push_back (1.4);
	second.push_back (3.7);
	second.push_back (7.1);

//	first.sort();
//	second.sort();

	first.merge(second);

	// (second is now empty)

	second.push_back (2.1);

	first.merge(second,mycomparison);

	std::cout << "first contains:";
	for (ft::list<double>::iterator it=first.begin(); it!=first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "first contains: 1.4 2.2 2.9 2.1 3.1 3.7 7.1" << std::endl;
}

void list_reverse()
{
	ft::list<int> mylist;

	for (int i(1); i < 10; ++i) mylist.push_back(i);

	std::cout << "before reverse:";
	for (ft::list<int>::iterator it(mylist.begin()); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	mylist.reverse();

	std::cout << "after reverse: ";
	for (ft::list<int>::iterator it(mylist.begin()); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

bool compare_nocase(const std::string& first, const std::string& second)
{
	unsigned int i=0;
	while ( (i < first.length()) && (i < second.length()) )
	{
		if (tolower(first[i]) < tolower(second[i])) return true;
		else if (tolower(first[i])>tolower(second[i])) return false;
		++i;
	}
	return ( first.length() < second.length() );
}

void list_sort()
{
	ft::list<std::string> mylist;
	ft::list<std::string>::iterator it;
	mylist.push_back ("one");
	mylist.push_back ("two");
	mylist.push_back ("Three");

	mylist.sort();

	std::cout << "mylist contains:";
	for (it=mylist.begin(); it!=mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	mylist.sort(compare_nocase);

	std::cout << "mylist contains:";
	for (it=mylist.begin(); it!=mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

//mylist contains: Three one two
//mylist contains: one Three two

int main ()
{
//	list_sort();
//	list_reverse();
//	list_merge();
//	list_splice();
//	lol();

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

	mp.insert(std::make_pair('d', "lol"));
	mp.insert(std::make_pair('b', "lol"));
	mp.insert(std::make_pair('a', "lol"));
	mp.insert(std::make_pair('c', "lol"));
	mp.insert(std::make_pair('f', "lol"));
	mp.insert(std::make_pair('e', "lol"));
	mp.insert(std::make_pair('g', "lol"));

	mp.erase(mp.find('b'));

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

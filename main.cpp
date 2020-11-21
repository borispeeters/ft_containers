#include <iostream>
#include <string>
#include "Timer.hpp"

#include "utility.hpp" //for ft::pair

#include <deque>
#include "deque.hpp"

#include <list>
#include "list.hpp"

#include <map>
#include "map.hpp"

#include <queue>
#include "queue.hpp"

#include <set>
#include "set.hpp"

#include <stack>
#include "stack.hpp"

#include <vector>
#include "vector.hpp"



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

#include <iterator>

void printList(ft::list<int> li, std::string const & s)
{
	ft::list<int>::iterator it;
	std::cout << s << " contains:";
	for (it = li.begin(); it != li.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << " $" << std::endl;
}

void revPrintList(ft::list<int> li, std::string const & s)
{
	ft::list<int>::reverse_iterator itr;
	std::cout << s << " contains:";
	for (itr = li.rbegin(); itr != li.rend(); ++itr)
		std::cout << ' ' << *itr;
	std::cout << " $ in reverse!" << std::endl;
}

int main ()
{
	{
		std::cout << "STD" << std::endl;
		Timer t;

		std::vector<int>	v;
		v.reserve(99999999);

		for (int i = 0; i < 99999999; ++i)
			v.push_back(i);
	}
	{
		std::cout << "FT" << std::endl;
		Timer t;

		ft::vector<int>	v;
		v.reserve(99999999);

		for (int i = 0; i < 99999999; ++i)
			v.push_back(i);
	}
	
	return 0;

/*																		*\
**	------------------------------------------------------------------	**
\*																		*/

//	list_sort();
//	list_reverse();
//	list_merge();
//	list_splice();
//	lol();

//	ft::multiset<int>	myset;
//
//	for (int i = 1; i <= 5; ++i)
//		myset.insert(i);
//	myset.insert(3);
//
////	std::cout << "BEFORE ERASE" << std::endl;
////	system("leaks ft_containers");
//	myset.erase(3);
////	std::cout << "AFTER ERASE" << std::endl;
////	system("leaks ft_containers");
//
//	ft::multiset<int>::iterator	it;
//
//	std::cout << "myset contains:";
//	for (it = myset.begin(); it != myset.end(); ++it)
//		std::cout << ' ' << *it;
//	std::cout << " $" << std::endl;

//	system("leaks ft_containers");

//	return 0;

/*																		*\
**	------------------------------------------------------------------	**
\*																		*/


//	ft::map<char, std::string>	mp;
//	ft::map<char, std::string>::iterator mit;

//	mp.insert(ft::make_pair('a', "lol"));
//	mp.insert(ft::make_pair('b', "lol"));
//	mp.insert(ft::make_pair('c', "lol"));
//	mp.insert(ft::make_pair('d', "lol"));
//	mp.insert(ft::make_pair('e', "lol"));
//	mp.insert(ft::make_pair('f', "lol"));
//	mp.insert(ft::make_pair('g', "lol"));
//	mp.insert(ft::make_pair('h', "lol"));
//
//
//	mit = mp.begin();
//
//	std::cout << mit->first << std::endl;
//	return 0;
//	mp.erase('a');
//	mp.erase('b');
//	mp.erase('c');
//	mp.erase('d');
//	mp.erase('e');
//	mp.erase('f');
//	mp.erase('g');
//	mp.erase('b');
//	mp.erase('c');
//	mp.erase('h');

//	mp.printBT();
//
//	std::cout << "map has a size of: " << mp.size() << std::endl;
//
//	std::cout << "map contains:";
//	for (mit = mp.begin(); mit != mp.end(); ++mit)
//		std::cout << ' ' << mit->first;
//	std::cout << std::endl;


/*																		*\
**	------------------------------------------------------------------	**
\*																		*/

//	system("leaks ft_containers");

	return 0;
}

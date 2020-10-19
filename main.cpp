//#include <iostream>
//#include <deque>
//#include <map>
//#include <string>
//#include <vector>
//#include "list.hpp"
//#include "map.hpp"
//
//int main ()
//{
//	std::vector<int>	ve;
//	ve.push_back(1);
//	ve.push_back(2);
//	ve.push_back(3);
//
//	ft::list<int>	li(ve.begin(), ve.end());
//
//	ft::list<int>::const_iterator it;
//
////	for (it = li.begin(); it != li.end(); ++it)
////		std::cout << *it << std::endl;
//
//
///*																		*\
//**	------------------------------------------------------------------	**
//\*																		*/
//
//
//	ft::map<char, std::string>	mp;
//	ft::map<char, std::string>::iterator mit;
//
////	mp.insert(std::make_pair('A', "test lol"));
////	mp.insert(std::make_pair('B', "another test lol"));
////	mp.insert(std::make_pair('C', "final test lol"));
//
//
////	mp['a'] = "first element";
////	mp['b'] = "second element";
////	mp['c'] = "third element";
////	mp['d'] = "last element";
//
//	mit = mp.begin();
//
//	mp.insert(mit, std::make_pair('a', "first element"));
//	mp.insert(mit, std::make_pair('c', "second element"));
//	mp.insert(mit, std::make_pair('e', "third element"));
//	mp.insert(mit, std::make_pair('g', "last element"));
////
////	mp.erase('g');
//
////	std::cout << std::endl << "this boi has a size of " << mp.size() << std::endl << std::endl;
//
//
////	for (mit = mp.begin(); mit != mp.end(); ++mit)
////		std::cout << mit->first << " => " << mit->second << std::endl;
//
//
///*																		*\
//**	------------------------------------------------------------------	**
//\*																		*/
//
//	std::deque<int>	de;
//	std::deque<int>::iterator itd;
//
//	de.push_back(42);
//	de.push_back(8);
//	de.push_back(19);
//	de.push_back(24);
//
//	de.resize(7);
//
////for (int value : de)
////	std::cout << value << std::endl;
//
//
///*																		*\
//**	------------------------------------------------------------------	**
//\*																		*/
//
//	std::multimap<char, std::string> 			mmp;
//	std::multimap<char, std::string>::iterator	mmit;
//
//	mmp.insert(std::make_pair('a', "first element"));
//	mmp.insert(std::make_pair('b', "second element"));
//	mmp.insert(std::make_pair('c', "third element"));
//	mmp.insert(std::make_pair('c', "fourth element"));
//	mmp.insert(std::make_pair('d', "second to last element"));
//	mmp.insert(std::make_pair('e', "last element"));
//
//	for (mmit = mmp.begin(); mmit != mmp.end(); ++mmit)
//		std::cout << mmit->first << " => " << mmit->second << std::endl;
//
//	mmit = mmp.find('c');
//	mmp.erase(mmit);
//	std::cout << std::endl;
//
//	for (mmit = mmp.begin(); mmit != mmp.end(); ++mmit)
//		std::cout << mmit->first << " => " << mmit->second << std::endl;
//
///*																		*\
//**	------------------------------------------------------------------	**
//\*																		*/
//
////	system("leaks ft_containers");
//
//	return 0;
//}

#include <iostream>
#include "vector.hpp"


int main ()
{
	ft::vector<int>				ve;
	for (int i = 1; i <= 10; ++i)
		ve.push_back(i);

	ft::vector<int>::iterator	it;
	for (it = ve.begin(); it != ve.end(); ++it)
		std::cout << *it << std::endl;

	std::cout << std::endl;

	std::cout << "NOW THE REVERSE ITERATOR :D\n" << std::endl;

	ft::vector<int>::reverse_iterator itr;
	for (itr = ve.rbegin(); itr != ve.rend(); ++itr)
		std::cout << *itr << std::endl;


	return 0;
}
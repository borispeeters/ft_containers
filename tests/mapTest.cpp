#include <functional>
#include "functional.hpp"
#include <iomanip>
#include <iostream>
#include <list>
#include "list.hpp"
#include <map>
#include "map.hpp"
#include <set>
#include "set.hpp"
#include <string>
#include <utility>
#include "utility.hpp"
#include <vector>
#include "vector.hpp"

#define PRINT(x) print(x, #x)
#define PRINTR(x) printr(x, #x)
#define COMP(x, y) relational_operator(x, #x, y, #y)

template <class T>
void	print(T const & t, char const * s)
{
	typename T::const_iterator	it;

	std::cout << std::setw(3) << s << " contains:";
	for (it = t.begin(); it != t.end(); ++it)
		std::cout << " (" << it->first << " => " << it->second << ')';
	std::cout << std::endl;
}

template <class T>
void 	printr(T const & t, char const * s)
{
	typename T::const_reverse_iterator	itr;

	std::cout << std::setw(3) << s << " in reverse:";
	for (itr = t.rbegin(); itr != t.rend(); ++itr)
		std::cout << " (" << itr->first << " => " << itr->second << ')';
	std::cout << std::endl;
}

template <class T>
void 	relational_operator(T const & t1, char const * s1, T const & t2, char const * s2) {
	std::cout << s1 << " is..." << std::endl;

	if (t1 == t2) std::cout << "equal to" << std::endl;
	if (t1 != t2) std::cout << "not equal to" << std::endl;
	if (t1 < t2) std::cout << "smaller than" << std::endl;
	if (t1 <= t2) std::cout << "smaller than or equal to" << std::endl;
	if (t1 > t2) std::cout << "greater than" << std::endl;
	if (t1 >= t2) std::cout << "greater than or equal to" << std::endl;

	std::cout << s2 << "!\n" << std::endl;
}

template <class T>
void check_insertion(T const & t) {
	if (t.second) {
		std::cout << "successfully inserted (" << t.first->first << " => " << t.first->second << ')' << std::endl;
	} else {
		std::cout << "duplicate: (" << t.first->first << " => " << t.first->second << ')' << std::endl;
	}
}

int		main()
{
	{ // default constructor
		std::map<std::string, int>	std;
		ft::map<std::string, int>	ft;

		if (std.empty()) std::cout << "std is empty" << std::endl;
		if (ft.empty()) std::cout << " ft is empty" << std::endl;

		std::cout << "size of std is: " << std.size() << std::endl;
		std::cout << "size of ft  is: " << ft.size() << std::endl;

		std::cout << "max size of std(std::string, int) is: " << std.max_size() << std::endl;
		std::cout << "max size of ft(std::string, int)  is: " << ft.max_size() << std::endl;
	}

	std::cout << "---" << std::endl;

	{ // range constructor
		std::vector<std::pair<std::string, int> >	vs;
		ft::vector<ft::pair<std::string, int> >		vf;

		vs.push_back(std::make_pair("first", 1));
		vs.push_back(std::make_pair("second", 2));
		vs.push_back(std::make_pair("third", 3));
		vs.push_back(std::make_pair("last", 4));

		vf.push_back(ft::make_pair("first", 1));
		vf.push_back(ft::make_pair("second", 2));
		vf.push_back(ft::make_pair("third", 3));
		vf.push_back(ft::make_pair("last", 4));

		std::map<std::string, int>	std(vs.begin(), vs.end());
		ft::map<std::string, int>	ft(vf.begin(), vf.end());

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // copy constructor
		std::vector<std::pair<std::string, int> >	vs;
		ft::vector<ft::pair<std::string, int> >		vf;

		vs.push_back(std::make_pair("apple", 1));
		vs.push_back(std::make_pair("banana", 2));
		vs.push_back(std::make_pair("pineapple", 3));
		vs.push_back(std::make_pair("orange", 4));

		vf.push_back(ft::make_pair("apple", 1));
		vf.push_back(ft::make_pair("banana", 2));
		vf.push_back(ft::make_pair("pineapple", 3));
		vf.push_back(ft::make_pair("orange", 4));

		std::map<std::string, int>	stdCopy(vs.begin(), vs.end());
		ft::map<std::string, int>	ftCopy(vf.begin(), vf.end());

		std::map<std::string, int>	std(stdCopy);
		ft::map<std::string, int>	ft(ftCopy);

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // assignment operator
		std::vector<std::pair<std::string, int> >	vs;
		ft::vector<ft::pair<std::string, int> >		vf;

		vs.push_back(std::make_pair("pizza", 1));
		vs.push_back(std::make_pair("pancake", 2));
		vs.push_back(std::make_pair("hamburger", 3));
		vs.push_back(std::make_pair("steak", 4));

		vf.push_back(ft::make_pair("pizza", 1));
		vf.push_back(ft::make_pair("pancake", 2));
		vf.push_back(ft::make_pair("hamburger", 3));
		vf.push_back(ft::make_pair("steak", 4));

		std::map<std::string, int>	stdCopy(vs.begin(), vs.end());
		ft::map<std::string, int>	ftCopy(vf.begin(), vf.end());

		std::map<std::string, int>	std;
		ft::map<std::string, int>	ft;

		std = stdCopy;
		ft = ftCopy;

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // element access
		std::map<int, std::string>	std;
		ft::map<int, std::string>	ft;

		std[1] = "move";
		std[3] = "get";
		std[4] = "out";
		std[5] = "the";
		std[6] = "wey";
		std[6] = "way";

		ft[1] = "move";
		ft[3] = "get";
		ft[4] = "out";
		ft[5] = "the";
		ft[6] = "wey";
		ft[6] = "way";

		std::cout << "std:";
		for (int i = 1; i <= 6; ++i) {
			std::cout << " {" << std[i] << '}';
		} std::cout << std::endl;

		std::cout << " ft:";
		for (int i = 1; i <= 6; ++i) {
			std::cout << " {" << ft[i] << '}';
		} std::cout << std::endl;
	}

	std::cout << "---" << std::endl;

	{ // insert find and erase
		std::map<int, int>	std;
		ft::map<int, int>	ft;

		std::pair<std::map<int, int>::iterator, bool>	stdRet;
		ft::pair<ft::map<int, int>::iterator, bool>		ftRet;

		std::map<int, int>::iterator	its;
		ft::map<int, int>::iterator		itf;

		for (int i = 2; i <= 23; i += i + 1) {
			std::cout << "std: ";
			stdRet = std.insert(std::make_pair(i, i));
			check_insertion(stdRet);

			std::cout << " ft: ";
			ftRet = ft.insert(ft::make_pair(i, i));
			check_insertion(ftRet);
		} // 2 5 11 23

		for (int i = 6; i <= 30; i = i * 3 - 10) {
			std::cout << "std: ";
			stdRet = std.insert(std::make_pair(i, i));
			check_insertion(stdRet);

			std::cout << " ft: ";
			ftRet = ft.insert(ft::make_pair(i, i));
			check_insertion(ftRet);
		} // 2 5 6 8 11 14 23

		for (int i = 1; i <= 25; i *= 2) {
			std::cout << "std: ";
			stdRet = std.insert(std::make_pair(i, i));
			check_insertion(stdRet);

			std::cout << " ft: ";
			ftRet = ft.insert(ft::make_pair(i, i));
			check_insertion(ftRet);
		} // 1 2 4 5 6 8 11 14 16 23

		its = std.find(16);
		its = std.insert(its, std::make_pair(19, 19));

		std::cout << "its: " << its->first << std::endl;

		its = std.find(5);
		its = std.insert(its, std::make_pair(5, 5));

		std::cout << "its: " << its->first << std::endl;

		itf = ft.find(16);
		itf = ft.insert(itf, ft::make_pair(19, 19));

		std::cout << "itf: " << itf->first << std::endl;

		itf = ft.find(5);
		itf = ft.insert(itf, ft::make_pair(5, 5));

		std::cout << "itf: " << itf->first << std::endl;

		// 1 2 4 5 6 8 11 14 16 19 23

		std::list<std::pair<int, int> >	s;
		ft::list<ft::pair<int, int> >	f;

		for (int i = 2; i < 35; i += 6) {
			s.push_front(std::make_pair(i / 2, i / 2));
			s.push_back(std::make_pair(i * 3 / 2, i * 3 / 2));

			f.push_front(ft::make_pair(i / 2, i / 2));
			f.push_back(ft::make_pair(i * 3 / 2, i * 3 / 2));
		}

		std.insert(s.begin(), s.end());
		ft.insert(f.begin(), f.end());

		// 1 2 3 4 5 6 7 8 10 11 12 13 14 16 19 21 23 30 39 48

		PRINT(std);
		PRINT(ft);

		its = std.find(23);
		if (its != std.end()) {
			std::cout << "std: erasing " << its->first << std::endl;
			std.erase(its);
		}

		itf = ft.find(23);
		if (itf != ft.end()) {
			std::cout << " ft: erasing " << itf->first << std::endl;
			ft.erase(itf);
		}

		its = std.find(24);
		if (its != std.end()) {
			std::cout << "std: erasing " << its->first << std::endl;
			std.erase(its);
		}

		itf = ft.find(24);
		if (itf != ft.end()) {
			std::cout << " ft: erasing " << itf->first << std::endl;
			ft.erase(itf);
		}

		its = std.find(48);
		if (its != std.end()) {
			std::cout << "std: erasing " << its->first << std::endl;
			std.erase(its);
		}

		itf = ft.find(48);
		if (itf != ft.end()) {
			std::cout << " ft: erasing " << itf->first << std::endl;
			ft.erase(itf);
		}

		// 1 2 3 4 5 6 7 8 10 11 12 13 14 16 19 21 30 39

		if (std.erase(12)) {
			std::cout << "std: erased 12" << std::endl;
		}

		if (ft.erase(12)) {
			std::cout << " ft: erased 12" << std::endl;
		}

		if (std.erase(18)) {
			std::cout << "std: erased 18" << std::endl;
		}

		if (ft.erase(18)) {
			std::cout << " ft: erased 18" << std::endl;
		}

		// 1 2 3 4 5 6 7 8 10 11 13 14 16 19 21 30 39

		its = std.find(6);
		itf = ft.find(6);

		std.erase(std.find(3), std.find(14));
		ft.erase(ft.find(3), ft.find(14));

		// 1 2 14 16 19 21 30 39

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // swap and clear
		std::map<int, std::string>	stdFoo;
		std::map<int, std::string>	stdBar;

		ft::map<int, std::string>	ftFoo;
		ft::map<int, std::string>	ftBar;

		stdFoo[1] = "no";
		stdFoo[2] = "boys";
		stdFoo[3] = "allowed";

		stdBar[10] = "plip";
		stdBar[20] = "plop";

		ftFoo[1] = "no";
		ftFoo[2] = "boys";
		ftFoo[3] = "allowed";

		ftBar[10] = "plip";
		ftBar[20] = "plop";

		std::cout << "pre swap:" << std::endl;

		PRINT(stdFoo);
		PRINT(ftFoo);
		PRINT(stdBar);
		PRINT(ftBar);

		std::cout << std::endl;

		stdFoo.swap(stdBar);
		ftFoo.swap(ftBar);

		std::cout << "post swap:" << std::endl;

		PRINT(stdFoo);
		PRINT(ftFoo);
		PRINT(stdBar);
		PRINT(ftBar);

		std::cout << std::endl;

		// you can also call swap like this!

		stdFoo.clear();
		ftFoo.clear();

		std::swap(stdFoo, stdBar);
		ft::swap(ftFoo, ftBar);

		std::cout << "clearing foo then swapping it back with bar:" << std::endl;

		PRINT(stdFoo);
		PRINT(ftFoo);
		PRINT(stdBar);
		PRINT(ftBar);
	}

	std::cout << "---" << std::endl;

	{ // key_comp & value_comp
		std::map<int, std::string>	std;
		ft::map<int, std::string>	ft;

		std[1] = "pasta";
		std[2] = "lasagna";
		std[3] = "paella";

		ft[1] = "pasta";
		ft[2] = "lasagna";
		ft[3] = "paella";

		{
			std::map<int, std::string>::key_compare	stdcomp = std.key_comp();
			std::map<int, std::string>::iterator it = std.begin();
			int highest = std.rbegin()->first;

			std::cout << "std contains:";
			do {
				std::cout << " (" << it->first << " => " << it->second << ')';
			} while (stdcomp((it++)->first, highest));
			std::cout << std::endl;
		}

		{
			ft::map<int, std::string>::key_compare	ftcomp = ft.key_comp();
			ft::map<int, std::string>::iterator	it = ft.begin();
			int highest = ft.rbegin()->first;

			std::cout << " ft contains:";
			do {
				std::cout << " (" << it->first << " => " << it->second << ')';
			} while (ftcomp((it++)->first, highest));
			std::cout << std::endl;
		}

		std[4] = "sushi";
		ft[4] = "sushi";

		{
			std::map<int, std::string>::value_compare	stdcomp = std.value_comp();
			std::map<int, std::string>::iterator it = std.begin();
			std::pair<int, std::string>	highest = *std.rbegin();

			std::cout << "std contains:";
			do {
				std::cout << " (" << it->first << " => " << it->second << ')';
			} while (stdcomp(*it++, highest));
			std::cout << std::endl;
		}

		{
			ft::map<int, std::string>::value_compare	ftcomp = ft.value_comp();
			ft::map<int, std::string>::iterator	it = ft.begin();
			ft::pair<int, std::string>	highest = *ft.rbegin();

			std::cout << " ft contains:";
			do {
				std::cout << " (" << it->first << " => " << it->second << ')';
			} while (ftcomp(*it++, highest));
			std::cout << std::endl;
		}
	}

	std::cout << "---" << std::endl;

	{ // count
		std::map<int, int>	std;
		ft::map<int, int>	ft;

		std[1] = 1;
		std[4] = 4;
		std[9] = 9;
		std[16] = 16;

		ft[1] = 1;
		ft[4] = 4;
		ft[9] = 9;
		ft[16] = 16;

		std::cout << "std:";
		for (int i = 1; i <= 20; ++i) {
			if (std.count(i)) {
				std::cout << "\033[0;32m";
			} else {
				std::cout << "\033[0;31m";
			} std::cout << ' ' << i;
		} std::cout << "\033[0m" << std::endl;

		std::cout << " ft:";
		for (int i = 1; i <= 20; ++i) {
			if (ft.count(i)) {
				std::cout << "\033[0;32m";
			} else {
				std::cout << "\033[0;31m";
			} std::cout << ' ' << i;
		} std::cout << "\033[0m" << std::endl;
	}

	std::cout << "---" << std::endl;

	{ // lower and upper bound
		std::map<int, int>	std;
		ft::map<int, int>	ft;

		for (int i = 5; i >= 1; --i) {
			std[i] = i;
			ft[i] = i;
		}

		std::cout << "std.lower_bound(4): " << std.lower_bound(4)->first << std::endl;
		std::cout << "std.upper_bound(4): " << std.upper_bound(4)->first << std::endl;

		std::cout << "ft.lower_bound(4): " << ft.lower_bound(4)->first << std::endl;
		std::cout << "ft.upper_bound(4): " << ft.upper_bound(4)->first << std::endl;
	}

	std::cout << "---" << std::endl;

	{ // equal_range
		std::map<int, int>	std;
		ft::map<int, int>	ft;

		for (int i = 7; i <= 70; i += 7) {
			std[i] = i;
			ft[i] = i;
		}

		{
			std::pair<std::map<int, int>::iterator, std::map<int, int>::iterator>	ret;

			ret = std.equal_range(14);

			std::cout << "std lower_bound of 14: " << ret.first->first << std::endl;
			std::cout << "std upper_bound of 14: " << ret.second->second << std::endl;

			ret = std.equal_range(60);

			std::cout << "std lower_bound of 60: " << ret.first->first << std::endl;
			std::cout << "std upper_bound of 60: " << ret.second->second << std::endl;
		}

		{
			ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator>	ret;

			ret = ft.equal_range(14);

			std::cout << "std lower_bound of 14: " << ret.first->first << std::endl;
			std::cout << "std upper_bound of 14: " << ret.second->second << std::endl;

			ret = ft.equal_range(60);

			std::cout << "std lower_bound of 60: " << ret.first->first << std::endl;
			std::cout << "std upper_bound of 60: " << ret.second->second << std::endl;
		}
	}

	std::cout << "---" << std::endl;

	{ // relational operators
		std::map<int, int>	stdFoo;
		ft::map<int, int>	ftFoo;

		for (int i = 1; i <= 5; ++i) {
			stdFoo[i] = i;
			ftFoo[i] = i;
		}

		std::map<int, int>	stdBar(stdFoo);
		ft::map<int, int>	ftBar(ftFoo);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);

		stdBar[5] = 6;
		ftBar[5] = 6;

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);

		stdFoo[5] = 6;
		stdFoo[6] = 7;

		ftFoo[5] = 6;
		ftFoo[6] = 7;

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);
	}

	std::cout << "---" << std::endl;

	{ // different comparison object
		std::map<int, int, std::greater<int> >	std;
		ft::map<int, int, ft::greater<int> >	ft;

		std[5] = 5;
		std[3] = 3;
		std[11] = 11;
		std[7] = 7;
		std[9] = 9;

		ft[5] = 5;
		ft[3] = 3;
		ft[11] = 11;
		ft[7] = 7;
		ft[9] = 9;

		PRINT(std);
		PRINT(ft);
	}

	return 0;
}

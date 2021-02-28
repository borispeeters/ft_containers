#include <functional>
#include "functional.hpp"
#include <iomanip>
#include <iostream>
#include <set>
#include "set.hpp"
#include <string>
#include <utility>
#include "utility.hpp"
#include <vector>

#define PRINT(x) print(x, #x)
#define PRINTR(x) printr(x, #x)
#define COMP(x, y) relational_operator(x, #x, y, #y)

template <class T>
void	print(T const & t, char const * s)
{
	typename T::const_iterator	it;

	std::cout << std::setw(3) << s << " contains:";
	for (it = t.begin(); it != t.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;
}

template <class T>
void 	printr(T const & t, char const * s)
{
	typename T::const_reverse_iterator	itr;

	std::cout << std::setw(3) << s << " in reverse:";
	for (itr = t.rbegin(); itr != t.rend(); ++itr)
		std::cout << ' ' << *itr;
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
		std::cout << "successfully inserted " << *t.first << std::endl;
	} else {
		std::cout << "duplicate: " << *t.first << std::endl;
	}
}

int main() {
	{ // default constructor and basic functions
		std::set<char>	std;
		ft::set<char>	ft;

		if (std.empty()) std::cout << "std is empty" << std::endl;
		if (ft.empty()) std::cout << " ft is empty" << std::endl;

		std::cout << "size of std(int) is: " << std.size() << std::endl;
		std::cout << "size of ft(int)  is: " << ft.size() << std::endl;

		std::cout << "max size of std(int) is: " << std.max_size() << std::endl;
		std::cout << "max size of ft(int)  is: " << ft.max_size() << std::endl;
	}

	std::cout << "---" << std::endl;

	{ // range constructor
		std::vector<int>	v;

		v.push_back(3);
		v.push_back(14);
		v.push_back(9);
		v.push_back(28);
		v.push_back(17);
		v.push_back(6);
		v.push_back(54);
		v.push_back(9);

		std::set<int>	std(v.begin(), v.end());
		ft::set<int>	ft(v.begin(), v.end());

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // copy constructor
		std::vector<int>	v;

		v.push_back(3);
		v.push_back(14);
		v.push_back(9);
		v.push_back(28);
		v.push_back(17);
		v.push_back(6);
		v.push_back(54);

		std::set<int>	stdCopy(v.begin(), v.end());
		ft::set<int>	ftCopy(v.begin(), v.end());

		std::set<int>	std(stdCopy);
		ft::set<int>	ft(ftCopy);

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // assignment operator
		std::vector<int>	v;

		v.push_back(14);
		v.push_back(8);
		v.push_back(16);
		v.push_back(10);
		v.push_back(20);

		std::set<int>	stdCopy(v.begin(), v.end());
		ft::set<int>	ftCopy(v.begin(), v.end());

		std::set<int>	std;
		ft::set<int>	ft;

		std = stdCopy;
		ft = ftCopy;

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // inserting, finding and erasing elements
		int intArray[] = { 2, 4, 6, 8 };

		std::set<int>	std;
		ft::set<int>	ft;

		std::pair<std::set<int>::iterator, bool>	stdRet;
		ft::pair<ft::set<int>::iterator, bool>		ftRet;

		std::set<int>::iterator its;
		ft::set<int>::iterator	itf;

		for (int i = 3; i <= 20; i += 3) {
			std::cout << "std: ";
			stdRet = std.insert(i);
			check_insertion(stdRet);

			std::cout << " ft: ";
			ftRet = ft.insert(i);
			check_insertion(ftRet);
		} // 3 6 9 12 15 18

		for (int i = 4; i <= 20; i += 7) {
			std::cout << "std: ";
			stdRet = std.insert(i);
			check_insertion(stdRet);

			std::cout << " ft: ";
			ftRet = ft.insert(i);
			check_insertion(ftRet);
		} // 3 4 6 9 11 12 15 18

		for (int i = 1; i <= 20; i *= 3) {
			std::cout << "std: ";
			stdRet = std.insert(i);
			check_insertion(stdRet);

			std::cout << " ft: ";
			ftRet = ft.insert(i);
			check_insertion(ftRet);
		} // 1 3 4 6 9 11 12 15 18

		its = std.find(9);
		its = std.insert(its, 10);

		std::cout << "its: " << *its << std::endl;

		its = std.find(15);
		its = std.insert(its, 15);

		std::cout << "its: " << *its << std::endl;

		itf = ft.find(9);
		itf = ft.insert(itf, 10);

		std::cout << "itf: " << *itf << std::endl;

		itf = ft.find(15);
		itf = ft.insert(itf, 15);

		std::cout << "itf: " << *itf << std::endl;

		// 1 3 4 6 9 10 11 12 15 18

		std.insert(intArray, intArray + sizeof(intArray) / sizeof(int));
		ft.insert(intArray, intArray + sizeof(intArray) / sizeof(int));

		// 1 2 3 4 6 8 9 10 11 12 15 18

		PRINT(std);
		PRINT(ft);

		its = std.find(9);
		if (its != std.end()) {
			std::cout << "std: erasing " << *its << std::endl;
			std.erase(its);
		}

		itf = ft.find(9);
		if (itf != ft.end()) {
			std::cout << " ft: erasing " << *itf << std::endl;
			ft.erase(itf);
		}

		its = std.find(8);
		if (its != std.end()) {
			std::cout << "std: erasing " << *its << std::endl;
			std.erase(its);
		}

		itf = ft.find(8);
		if (itf != ft.end()) {
			std::cout << " ft: erasing " << *itf << std::endl;
			ft.erase(itf);
		}

		its = std.find(7);
		if (its != std.end()) {
			std::cout << "std: erasing " << *its << std::endl;
			std.erase(its);
		}

		itf = ft.find(7);
		if (itf != ft.end()) {
			std::cout << " ft: erasing " << *itf << std::endl;
			ft.erase(itf);
		}

		// 1 2 3 4 6 10 11 12 15 18

		if (std.erase(18)) {
			std::cout << "std: erased 18" << std::endl;
		}

		if (ft.erase(18)) {
			std::cout << " ft: erased 18" << std::endl;
		}

		if (std.erase(20)) {
			std::cout << "std: erased 20" << std::endl;
		}

		if (ft.erase(20)) {
			std::cout << " ft: erased 20" << std::endl;
		}

		// 1 2 3 4 6 10 11 12 15

		its = std.find(6);
		itf = ft.find(6);

		std.erase(std.begin(), its);
		ft.erase(ft.begin(), itf);

		// 6 10 11 12 15

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // swap & clear
		std::vector<int>	foo;
		std::vector<int>	bar;

		foo.push_back(1);
		foo.push_back(2);
		foo.push_back(3);
		foo.push_back(4);

		bar.push_back(10);
		bar.push_back(20);
		bar.push_back(30);

		std::set<int>	stdFoo(foo.begin(), foo.end());
		std::set<int>	stdBar(bar.begin(), bar.end());

		ft::set<int>	ftFoo(foo.begin(), foo.end());
		ft::set<int>	ftBar(bar.begin(), bar.end());

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
		std::set<int>	std;
		ft::set<int>	ft;

		for (int i = 0; i <= 5; ++i) {
			std.insert(i * 10);
			ft.insert(i * 10);
		}

		{
			std::set<int>::key_compare	stdcomp = std.key_comp();
			std::set<int>::iterator it = std.begin();
			int	highest = *std.rbegin();

			std::cout << "std contains:";
			do {
				std::cout << ' ' << *it;
			} while (stdcomp(*(it++), highest));
			std::cout << std::endl;
		}

		{
			ft::set<int>::key_compare	ftcomp = ft.key_comp();
			ft::set<int>::iterator it = ft.begin();
			int	highest = *ft.rbegin();

			std::cout << " ft contains:";
			do {
				std::cout << ' ' << *it;
			} while (ftcomp(*(it++), highest));
			std::cout << std::endl;
		}

		for (int i = 1; i <= 3; ++i) {
			std.insert(i * 15);
			ft.insert(i * 15);
		}

		{
			std::set<int>::value_compare	stdcomp = std.value_comp();
			std::set<int>::iterator 		it = std.begin();
			int	highest = *std.rbegin();

			std::cout << "std contains:";
			do {
				std::cout << ' ' << *it;
			} while (stdcomp(*(it++), highest));
			std::cout << std::endl;
		}

		{
			ft::set<int>::value_compare	ftcomp = ft.value_comp();
			ft::set<int>::iterator 		it = ft.begin();
			int	highest = *ft.rbegin();

			std::cout << " ft contains:";
			do {
				std::cout << ' ' << *it;
			} while (ftcomp(*(it++), highest));
			std::cout << std::endl;
		}
	}

	std::cout << "---" << std::endl;

	{ // count
		std::set<int>	std;
		ft::set<int>	ft;

		std.insert(2);
		std.insert(3);
		std.insert(5);
		std.insert(7);
		std.insert(11);
		std.insert(13);
		std.insert(17);
		std.insert(19);

		ft.insert(2);
		ft.insert(3);
		ft.insert(5);
		ft.insert(7);
		ft.insert(11);
		ft.insert(13);
		ft.insert(17);
		ft.insert(19);

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
			if (std.count(i)) {
				std::cout << "\033[0;32m";
			} else {
				std::cout << "\033[0;31m";
			} std::cout << ' ' << i;
		} std::cout << "\033[0m" << std::endl;
	}

	std::cout << "---" << std::endl;

	{ // lower and upper bound
		std::set<int>	std;
		ft::set<int>	ft;

		for (int i = 15; i > 0; --i) {
			std.insert(i);
			ft.insert(i);
		}

		std.erase(std.lower_bound(4), std.upper_bound(8));
		std.erase(std.lower_bound(11), std.upper_bound(13));

		ft.erase(ft.lower_bound(4), ft.upper_bound(8));
		ft.erase(ft.lower_bound(11), ft.upper_bound(13));

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // equal range
		std::set<int>	std;
		ft::set<int>	ft;

		for (int i = 1; i < 8; ++i) {
			std.insert(i * 15);
			ft.insert(i * 15);
		}

		{
			std::pair<std::set<int>::iterator, std::set<int>::iterator>	ret;

			ret = std.equal_range(45);

			std::cout << "std lower_bound of 45: " << *ret.first << std::endl;
			std::cout << "std upper_bound of 45: " << *ret.second << std::endl;

			ret = std.equal_range(80);

			std::cout << "std lower_bound of 80: " << *ret.first << std::endl;
			std::cout << "std upper_bound of 80: " << *ret.second << std::endl;
		}

		{
			ft::pair<ft::set<int>::iterator, ft::set<int>::iterator>	ret;

			ret = ft.equal_range(45);

			std::cout << " ft lower_bound of 45: " << *ret.first << std::endl;
			std::cout << " ft upper_bound of 45: " << *ret.second << std::endl;

			ret = ft.equal_range(80);

			std::cout << " ft lower_bound of 80: " << *ret.first << std::endl;
			std::cout << " ft upper_bound of 80: " << *ret.second << std::endl;
		}
	}

	std::cout << "---" << std::endl;

	{ // relational operators
		std::set<int>	stdFoo;
		ft::set<int>	ftFoo;

		for (int i = 1; i <= 5; ++i) {
			stdFoo.insert(i);
			ftFoo.insert(i);
		}

		std::set<int>	stdBar(stdFoo);
		ft::set<int>	ftBar(ftFoo);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);

		stdBar.erase(5);
		stdBar.insert(6);
		ftBar.erase(5);
		ftBar.insert(6);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);

		stdFoo.erase(5);
		stdFoo.insert(6);
		stdFoo.insert(7);
		ftFoo.erase(5);
		ftFoo.insert(6);
		ftFoo.insert(7);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);
	}

	std::cout << "---" << std::endl;

	{ // different comparison object
		std::set<int, std::greater<int> >	std;
		ft::set<int, ft::greater<int> >		ft;

		std.insert(5);
		std.insert(7);
		std.insert(3);
		std.insert(11);
		std.insert(9);

		ft.insert(5);
		ft.insert(7);
		ft.insert(3);
		ft.insert(11);
		ft.insert(9);

		PRINT(std);
		PRINT(ft);
	}

	return 0;
}

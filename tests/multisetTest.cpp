#include <functional>
#include "functional.hpp"
#include <iomanip>
#include <iostream>
#include <set>
#include "set.hpp"
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

int main() {
	{ // default constructor and basic functions
		std::multiset<int>	std;
		ft::multiset<int>	ft;

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

		v.push_back(7);
		v.push_back(18);
		v.push_back(9);
		v.push_back(10);
		v.push_back(4);
		v.push_back(7);
		v.push_back(6);

		std::multiset<int>	std(v.begin(), v.end());
		ft::multiset<int>	ft(v.begin(), v.end());

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // copy constructor
		int intArray[] = { 15, 14, 21, 108, 18, 14, 28 };

		std::multiset<int>	stdCopy(intArray, intArray + sizeof(intArray) / sizeof(int));
		ft::multiset<int>	ftCopy(intArray, intArray + sizeof(intArray) / sizeof(int));

		std::multiset<int>	std(stdCopy);
		ft::multiset<int>	ft(ftCopy);

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // assignment operator
		int intArray[] = { 1, 2, 3, 5, 4, 5, 1, 3 };

		std::multiset<int>	stdCopy(intArray, intArray + sizeof(intArray) / sizeof(int));
		ft::multiset<int>	ftCopy(intArray, intArray + sizeof(intArray) / sizeof(int));

		std::multiset<int>	std;
		ft::multiset<int>	ft;

		std = stdCopy;
		ft = ftCopy;

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // insert find and erase
		std::multiset<int>	std;
		ft::multiset<int>	ft;

		std::multiset<int>::iterator	its;
		ft::multiset<int>::iterator		itf;

		std::cout << "Inserted " << *std.insert(2) << " in std" << std::endl;
		std::cout << "Inserted " << *ft.insert(2) << " in ft" << std::endl;

		std::cout << "Inserted " << *std.insert(3) << " in std" << std::endl;
		std::cout << "Inserted " << *ft.insert(3) << " in ft" << std::endl;

		std::cout << "Inserted " << *std.insert(5) << " in std" << std::endl;
		std::cout << "Inserted " << *ft.insert(5) << " in ft" << std::endl;

		std::cout << "Inserted " << *std.insert(7) << " in std" << std::endl;
		std::cout << "Inserted " << *ft.insert(7) << " in ft" << std::endl;

		std::cout << "Inserted " << *std.insert(11) << " in std" << std::endl;
		std::cout << "Inserted " << *ft.insert(11) << " in ft" << std::endl;

		std::cout << "Inserted " << *std.insert(13) << " in std" << std::endl;
		std::cout << "Inserted " << *ft.insert(13) << " in ft" << std::endl;

		std::cout << "Inserted " << *std.insert(17) << " in std" << std::endl;
		std::cout << "Inserted " << *ft.insert(17) << " in ft" << std::endl;

		std::cout << "Inserted " << *std.insert(19) << " in std" << std::endl;
		std::cout << "Inserted " << *ft.insert(19) << " in ft" << std::endl;

		// 2 3 5 7 11 13 17 19

		its = std.find(7);
		std::cout << "Hint insertion of " << *std.insert(its, 8) << " in std" << std::endl;

		itf = ft.find(7);
		std::cout << "Hint insertion of " << *ft.insert(itf, 8) << " in ft" << std::endl;

		std::cout << "Hint insertion of " << *std.insert(std.begin(), 1) << " in std" << std::endl;
		std::cout << "Hint insertion of " << *ft.insert(ft.begin(), 1) << " in ft" << std::endl;

		// 1 2 3 5 7 8 11 13 17 19

		std::vector<int>	v;

		for (int i = 5; i <= 10; ++i) v.push_back(i);
		for (int i = 3; i <= 7; ++i) v.push_back(i);
		for (int i = 13; i <= 19; ++i) v.push_back(i);

		std.insert(v.begin(), v.end());
		ft.insert(v.begin(), v.end());

		// 1 2 3 3 4 5 5 5 6 6 7 7 7 8 8 9 10 11 13 13 14 15 16 17 17 18 19 19

		PRINT(std);
		PRINT(ft);

		its = std.find(1);
		if (its != std.end()) {
			std::cout << "std: erasing " << *its << std::endl;
			std.erase(its);
		}

		itf = ft.find(1);
		if (itf != ft.end()) {
			std::cout << " ft: erasing " << *itf << std::endl;
			ft.erase(itf);
		}

		its = std.find(12);
		if (its != std.end()) {
			std::cout << "std: erasing " << *its << std::endl;
			std.erase(its);
		}

		itf = ft.find(12);
		if (itf != ft.end()) {
			std::cout << " ft: erasing " << *itf << std::endl;
			ft.erase(itf);
		}

		its = std.find(14);
		if (its != std.end()) {
			std::cout << "std: erasing " << *its << std::endl;
			std.erase(its);
		}

		itf = ft.find(14);
		if (itf != ft.end()) {
			std::cout << " ft: erasing " << *itf << std::endl;
			ft.erase(itf);
		}

		// 2 3 3 4 5 5 5 6 6 7 7 7 8 8 9 10 11 13 13 15 16 17 17 18 19 19

		std::cout << "std: 5 was erased " << std.erase(5) << " times!" << std::endl;
		std::cout << " ft: 5 was erased " << ft.erase(5) << " times!" << std::endl;

		std::cout << "std: 8 was erased " << std.erase(8) << " times!" << std::endl;
		std::cout << " ft: 8 was erased " << ft.erase(8) << " times!" << std::endl;

		std::cout << "std: 20 was erased " << std.erase(20) << " times!" << std::endl;
		std::cout << " ft: 20 was erased " << ft.erase(20) << " times!" << std::endl;

		std::cout << "std: 2 was erased " << std.erase(2) << " times!" << std::endl;
		std::cout << " ft: 2 was erased " << ft.erase(2) << " times!" << std::endl;

		// 3 3 4 6 6 7 7 7 9 10 11 13 13 15 16 17 17 18 19 19

		std.erase(std.find(4), std.find(18));
		ft.erase(ft.find(4), ft.find(18));

		// 3 3 18 19 19

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // swap and clear
		std::vector<int>	foo;
		std::vector<int>	bar;

		foo.push_back(1);
		foo.push_back(2);
		foo.push_back(3);

		bar.push_back(10);
		bar.push_back(20);
		bar.push_back(10);
		bar.push_back(20);

		std::multiset<int>	stdFoo(foo.begin(), foo.end());
		std::multiset<int>	stdBar(bar.begin(), bar.end());

		ft::multiset<int>	ftFoo(foo.begin(), foo.end());
		ft::multiset<int>	ftBar(bar.begin(), bar.end());

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

	{ // key_comp and vaqlue_comp
		std::multiset<int>	std;
		ft::multiset<int>	ft;

		for (int i = 15; i >= 9; --i) {
			std.insert(i / 1.5);
			ft.insert(i / 1.5);
		}

		{
			std::multiset<int>::key_compare	stdcomp = std.key_comp();
			std::multiset<int>::iterator it = std.begin();
			int	highest = *std.rbegin();

			std::cout << "std contains:";
			do {
				std::cout << ' ' << *it;
			} while (stdcomp(*(it++), highest));
			std::cout << std::endl;
		}

		{
			ft::multiset<int>::key_compare	ftcomp = ft.key_comp();
			ft::multiset<int>::iterator it = ft.begin();
			int	highest = *ft.rbegin();

			std::cout << " ft contains:";
			do {
				std::cout << ' ' << *it;
			} while (ftcomp(*(it++), highest));
			std::cout << std::endl;
		}

		for (int i = 1; i <= 5; ++i) {
			std.insert(i * 2);
			ft.insert(i * 2);
		}

		{
			std::multiset<int>::value_compare	stdcomp = std.value_comp();
			std::multiset<int>::iterator 		it = std.begin();
			int	highest = *std.rbegin();

			std::cout << "std contains:";
			do {
				std::cout << ' ' << *it;
			} while (stdcomp(*(it++), highest));
			std::cout << std::endl;
		}

		{
			ft::multiset<int>::value_compare	ftcomp = ft.value_comp();
			ft::multiset<int>::iterator 		it = ft.begin();
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
		std::vector<int>	v;

		v.push_back(9);
		v.push_back(7);
		v.push_back(1);
		v.push_back(3);
		v.push_back(7);
		v.push_back(4);
		v.push_back(10);
		v.push_back(10);
		v.push_back(6);
		v.push_back(4);
		v.push_back(6);
		v.push_back(9);
		v.push_back(8);
		v.push_back(1);
		v.push_back(10);
		v.push_back(4);
		v.push_back(3);
		v.push_back(7);
		v.push_back(8);
		v.push_back(8);

		std::multiset<int>	std;
		ft::multiset<int>	ft;

		std.insert(v.begin(), v.end());
		ft.insert(v.begin(), v.end());

		for (int i = 1; i <= 10; ++i) {
			std::cout << i << " appears " << std.count(i) << " times in std, " << ft.count(i) << " times in ft." << std::endl;
		}
	}

	std::cout << "---" << std::endl;

	{ // lower and upper bound
		std::multiset<int>	std;
		ft::multiset<int>	ft;

		for (int i = 1; i <= 5; ++i) {
			std.insert(i);
			ft.insert(i);
		}

		for (int i = 0; i < 3; ++i) {
			std.insert(2);
			ft.insert(2);
		}

		PRINT(std);
		PRINT(ft);

		std.erase(std.lower_bound(2), std.upper_bound(2));
		ft.erase(ft.lower_bound(2), ft.upper_bound(2));

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // equal_range
		std::multiset<int>	std;
		ft::multiset<int>	ft;

		for (int i = 1; i <= 4; ++i) {
			std.insert(i * 10);
			ft.insert(i * 10);
		}

		for (int i = 0; i < 5; ++i) {
			std.insert(30);
			ft.insert(30);
		}

		{
			std::pair<std::multiset<int>::iterator, std::multiset<int>::iterator>	ret;

			ret = std.equal_range(30);

			std.erase(ret.first, ret.second);
		}

		{
			ft::pair<ft::multiset<int>::iterator, ft::multiset<int>::iterator>	ret;

			ret = ft.equal_range(30);

			ft.erase(ret.first, ret.second);
		}

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // relational operators
		std::multiset<int>	stdFoo;
		ft::multiset<int>	ftFoo;

		for (int i = 1; i < 3; ++i) {
			for (int j = i; j < 4; ++j) {
				stdFoo.insert(j * 3 / 2);
				ftFoo.insert(j * 3 / 2);
			}
		} // 1 3 4 3 4

		std::multiset<int>	stdBar(stdFoo);
		ft::multiset<int>	ftBar(ftFoo);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);

		stdBar.erase(4);
		stdBar.insert(5);

		ftBar.erase(4);
		ftBar.insert(5);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);

		stdFoo.erase(4);
		stdFoo.insert(5);
		stdFoo.insert(6);

		ftFoo.erase(4);
		ftFoo.insert(5);
		ftFoo.insert(6);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);

	}

	std::cout << "---" << std::endl;

	{ // different comparison object
		std::multiset<int, std::greater<int> >	std;
		ft::multiset<int, ft::greater<int> >	ft;

		std.insert(5);
		std.insert(7);
		std.insert(3);
		std.insert(11);
		std.insert(9);
		std.insert(9);
		std.insert(5);

		ft.insert(5);
		ft.insert(7);
		ft.insert(3);
		ft.insert(11);
		ft.insert(9);
		ft.insert(9);
		ft.insert(5);

		PRINT(std);
		PRINT(ft);
	}

	return 0;
}

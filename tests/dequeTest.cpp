#include <exception>
#include <iomanip>
#include <iostream>
#include <deque>
#include "deque.hpp"
#include <string>

#define PRINT(x) print(x, #x)
#define PRINTR(x) printr(x, #x)
#define COMP(x, y) relational_operator(x, #x, y, #y)

template <class T>
void	print(T const & t, char const * s) {
	typename T::const_iterator	it;

	std::cout << std::setw(3) << s << " contains:";
	for (it = t.begin(); it != t.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;
}

template <class T>
void 	printr(T const & t, char const * s) {
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
		std::deque<std::string>	std;
		ft::deque<std::string>	ft;

		if (std.empty()) std::cout << "std is empty" << std::endl;
		if (ft.empty()) std::cout << " ft is empty" << std::endl;

		std::cout << "max size of std(int) is: " << std.max_size() << std::endl;
		std::cout << "max size of ft(int)  is: " << ft.max_size() << std::endl;
	}

	std::cout << "---" << std::endl;

	{ // fill constructor
		std::deque<char>	std(5, '+');
		ft::deque<char>		ft(5, '+');

		std::cout << "max size of std(char) is: " << std.max_size() << std::endl;
		std::cout << "max size of ft(char)  is: " << ft.max_size() << std::endl;

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // range and copy constructors
		int intArray[] = { 94, 156, 32, 41, 8, 27 };

		std::deque<int>	std(intArray, intArray + sizeof(intArray) / sizeof(int));
		ft::deque<int>	ft(intArray, intArray + sizeof(intArray) / sizeof(int));

		PRINT(std);
		PRINT(ft);

		ft::deque<int>	range(ft.begin() + 1, ft.end() - 2);
		ft::deque<int>	copy(ft);

		PRINT(range);
		PRINTR(copy);
	}

	std::cout << "---" << std::endl;

	{ // assignment operator
		int intArray[] = { 11, 15, 21, 14, 108, 7 };

		std::deque<int>	stdCopy(intArray, intArray + sizeof(intArray) / sizeof(int));
		ft::deque<int>	ftCopy(intArray, intArray + sizeof(intArray) / sizeof(int));

		std::deque<int>	std;
		ft::deque<int>	ft;

		std = stdCopy;
		ft = ftCopy;

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // resize
		int intArray[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		std::deque<int>	std(intArray, intArray + sizeof(intArray) / sizeof(int));
		ft::deque<int>	ft(intArray, intArray + sizeof(intArray) / sizeof(int));

		std.resize(6);
		std.resize(9, 250);
		std.resize(12);

		ft.resize(6);
		ft.resize(9, 250);
		ft.resize(12);

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // element access
		std::string stringArray[] = { "somebody", "once", "told", "me", "the", "world", "is", "gonna", "roll", "me",
										"I", "ain't", "the", "sharpest", "tool", "in", "the", "shed" };

		std::deque<std::string>	std(stringArray, stringArray + sizeof(stringArray) / sizeof(std::string));
		ft::deque<std::string>	ft(stringArray, stringArray + sizeof(stringArray) / sizeof(std::string));

		std::cout << "The element at the front of std is: " << std.front() << std::endl;
		std::cout << "The element at the front of ft  is: " << ft.front() << std::endl;

		std::cout << "The element at the back of std is: " << std.back() << std::endl;
		std::cout << "The element at the back of ft  is: " << ft.back() << std::endl;

		for (ft::deque<std::string>::size_type i = 0; i < ft.size(); ++i)
		{
			std::cout << "ft[" << i << "]: " << ft[i];
			std::cout << " - std[" << i << "]: " << std[i] << std::endl;
		}

		for (ft::deque<std::string>::size_type i = 0; i < ft.size(); ++i)
		{
			std::cout << "ft.at(" << i << "): " << ft.at(i);
			std::cout << " - std.at(" << i << "): " << std.at(i) << std::endl;
		}

		// UNDEFINED BEHAVIOUR
//		std::cout << std[180] << std::endl;
//		std::cout << ft[180] << std::endl;

		try {
			std::cout << std.at(180) << std::endl;
		}
		catch (std::exception & e) {
			std::cout << e.what() << ": ";
			std::cout << "std out of bounds" << std::endl;
		}

		try {
			std::cout << ft.at(180) << std::endl;
		}
		catch (std::exception & e) {
			std::cout << e.what() << ": ";
			std::cout << "ft out of bounds" << std::endl;
		}
	}

	std::cout << "---" << std::endl;

	{ // element modifiers
		std::deque<int>	std;
		ft::deque<int>	ft;

		for (int i = 9; i <= 16; ++i) {
			std.push_back(i);
			ft.push_back(i);
		} // 9 10 11 12 13 14 15 16

		for (int i = 8; i >= 1; --i) {
			std.push_front(i);
			ft.push_front(i);
		} // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16

		std.pop_front();
		std.pop_front();
		ft.pop_front();
		ft.pop_front();

		std.pop_back();
		std.pop_back();
		ft.pop_back();
		ft.pop_back();

		// 3 4 5 6 7 8 9 10 11 12 13 14

		PRINT(std);
		PRINT(ft);

		std::deque<int>::iterator	its = std.begin() + 4;
		std::cout << *std.insert(its, 19) << std::endl;

		ft::deque<int>::iterator	itf = ft.begin() + 4;
		std::cout << *ft.insert(itf, 19) << std::endl;

		// 3 4 5 6 19 7 8 9 10 11 12 13 14

		its = std.end() - 2;
		std.insert(its, 3, 23);

		itf = ft.end() - 2;
		ft.insert(itf, 3, 23);

		// 3 4 5 6 19 7 8 9 10 11 12 23 23 23 13 14

		int intArray[] = { 89, 75, 43 };

		its = std.begin() + 7;
		std.insert(its, intArray, intArray + sizeof(intArray) / sizeof(int));

		itf = ft.begin() + 7;
		ft.insert(itf, intArray, intArray + sizeof(intArray) / sizeof(int));

		// 3 4 5 6 19 7 8 89 75 43 9 10 11 12 23 23 23 13 14

		PRINT(std);
		PRINT(ft);

		std.erase(std.end() - 2);
		ft.erase(ft.end() - 2);

		// 3 4 5 6 19 7 8 89 75 43 9 10 11 12 23 23 23 14

		std.erase(std.begin() + 9, std.begin() + 14);
		ft.erase(ft.begin() + 9, ft.begin() + 14);

		// 3 4 5 6 19 7 8 89 75 23 23 23 14

		PRINT(std);
		PRINT(ft);

		std.clear();
		ft.clear();

		for (int i = 1; i <= 5; ++i) {
			std.push_front(i);
			ft.push_front(i);
		}

		PRINT(std);
		PRINT(ft);

		std.assign(4, 38);
		ft.assign(4, 38);

		PRINT(std);
		PRINT(ft);

		int range[] = { 144, 22, 8, 64, 99, 107, 45, 10, 36, 48 };

		std.assign(range, range + sizeof(range) / sizeof(int));
		ft.assign(range, range + sizeof(range) / sizeof(int));

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{
		std::deque<std::string>	stdFoo(2, "foo");
		std::deque<std::string>	stdBar(6, "bar");

		ft::deque<std::string>	ftFoo(2, "foo");
		ft::deque<std::string>	ftBar(6, "bar");

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

	{ // relational operators
		int intArray[] = { 2, 44, 51, 6, 17, 71 };

		std::deque<int>	stdFoo(intArray, intArray + sizeof(intArray) / sizeof(int));
		std::deque<int>	stdBar(stdFoo);

		ft::deque<int>	ftFoo(intArray, intArray + sizeof(intArray) / sizeof(int));
		ft::deque<int>	ftBar(ftFoo);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);

		stdBar.pop_back();
		stdBar.push_back(75);
		ftBar.pop_back();
		ftBar.push_back(75);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);

		stdFoo.pop_back();
		stdFoo.push_back(75);
		stdFoo.push_back(9);
		ftFoo.pop_back();
		ftFoo.push_back(75);
		ftFoo.push_back(9);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);
	}

	std::cout << "---" << std::endl;

	{ // yes
		ft::deque<int>	ft;

		for (int i = 1; i <= 5000; ++i) {
			ft.push_back(5000 + i);
			ft.push_front(5001 - i);
		}

		PRINT(ft);
	}

	return 0;
}

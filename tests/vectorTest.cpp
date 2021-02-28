#include <exception>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "vector.hpp"

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

int		main() {
	{ // tests for default constructor and some basic functions
		std::vector<int>	std;
		ft::vector<int>		ft;

		if (std.empty()) std::cout << "std is empty" << std::endl;
		if (ft.empty()) std::cout << " ft is empty" << std::endl;

		std::cout << "capacity of std is: " << std.capacity() << std::endl;
		std::cout << "capacity of ft  is: " << ft.capacity() << std::endl;

		std::cout << "max size of std(int) is: " << std.max_size() << std::endl;
		std::cout << "max size of ft(int)  is: " << ft.max_size() << std::endl;
	}

	std::cout << "---" << std::endl;

	{ // test for fill constructor
		std::vector<char>	std(3, '*');
		ft::vector<char>	ft(3, '*');

		PRINT(std);
		PRINT(ft);

		std::cout << "capacity of std is: " << std.capacity() << std::endl;
		std::cout << "capacity of ft  is: " << ft.capacity() << std::endl;

		std::cout << "max size of std(char) is: " << std.max_size() << std::endl;
		std::cout << "max size of ft(char)  is: " << ft.max_size() << std::endl;
	}

	std::cout << "---" << std::endl;

	{ // tests for range and copy constructors
		int intArray[] = { 128, 17, 55, 4, 93 };

		std::vector<int>	std(intArray, intArray + sizeof(intArray) / sizeof(int));
		ft::vector<int>		ft(intArray, intArray + sizeof(intArray) / sizeof(int));

		PRINTR(std);
		PRINTR(ft);

		ft::vector<int>	range(ft.begin() + 1, ft.end() - 1);
		ft::vector<int>	copy(ft);

		PRINT(range);
		PRINT(copy);
	}

	std::cout << "---" << std::endl;

	{ // assignment operator overload
		int intArray[] = { 14, 39, 22, 54, 33, 19 };

		std::vector<int>	stdCopy(intArray, intArray + sizeof(intArray) / sizeof(int));
		ft::vector<int>		ftCopy(intArray, intArray + sizeof(intArray) / sizeof(int));

		std::vector<int>	std;
		ft::vector<int>		ft;

		std = stdCopy;
		ft = ftCopy;

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // tests for resize and reserve
		std::vector<double>	std;
		ft::vector<double>	ft;

		std.reserve(11);
		ft.reserve(11);

		std::cout << "capacity of std after reserve is: " << std.capacity() << std::endl;
		std::cout << "capacity of ft  after reserve is: " << ft.capacity() << std::endl;

		double d = 4.2;
		for (int i = 0; i < 12; ++i)
		{
			std.push_back(d);
			ft.push_back(d);
			d *= 1.5;
		}

		PRINT(std);
		PRINT(ft);

		std::cout << "size of std is: " << std.size() << std::endl;
		std::cout << "size of ft  is: " << ft.size() << std::endl;

		std::cout << "capacity of std is: " << std.capacity() << std::endl;
		std::cout << "capacity of ft  is: " << ft.capacity() << std::endl;

		std.resize(9);
		std.resize(15, 4.2);
		std.resize(25);

		ft.resize(9);
		ft.resize(15, 4.2);
		ft.resize(25);

		PRINT(std);
		PRINT(ft);

		std::cout << "capacity of std after resize is: " << std.capacity() << std::endl;
		std::cout << "capacity of ft  after resize is: " << ft.capacity() << std::endl;
	}

	std::cout << "---" << std::endl;

	{ // tests for element access functions
		std::vector<std::string>	std;
		ft::vector<std::string>		ft;

		std.push_back("aap");
		std.push_back("noot");
		std.push_back("mies");
		std.push_back("wim");
		std.push_back("zus");
		std.push_back("jet");

		ft.push_back("aap");
		ft.push_back("noot");
		ft.push_back("mies");
		ft.push_back("wim");
		ft.push_back("zus");
		ft.push_back("jet");

		std::cout << "The element at the front of std is: " << std.front() << std::endl;
		std::cout << "The element at the front of ft  is: " << ft.front() << std::endl;

		std::cout << "The element at the back of std is: " << std.back() << std::endl;
		std::cout << "The element at the back of ft  is: " << ft.back() << std::endl;

		for (ft::vector<std::string>::size_type i = 0; i < ft.size(); ++i)
		{
			std::cout << "ft[" << i << "]: " << ft[i];
			std::cout << " - std[" << i << "]: " << std[i] << std::endl;
		}

		for (ft::vector<std::string>::size_type i = 0; i < ft.size(); ++i)
		{
			std::cout << "ft.at(" << i << "): " << ft.at(i);
			std::cout << " - std.at(" << i << "): " << std.at(i) << std::endl;
		}

//		std[999] = "if you uncomment this you are put on the naughty list >:(";
//		ft[999] = "if you uncomment this you are put on the naughty list >:(";

		try {
			std.at(999) = "ooh elden ring";
		}
		catch (std::exception & e) {
			std::cout << e.what() << ": ";
			std::cout << "disaster avoided, be safe kids. use a condom and the vector::at() function :)" << std::endl;
		}

		try {
			ft.at(999) = "that which commanded the stars";
		}
		catch (std::exception & e) {
			std::cout << e.what() << ": ";
			std::cout << "my vector also throws exceptions yes yes" << std::endl;
		}
	}

	std::cout << "---" << std::endl;

	{ // pushin' 'n' poppin'
		std::vector<const char *>	std;
		ft::vector<const char *>	ft;

		std.push_back("what's");
		std.push_back("in");
		std.push_back("the");
		std.push_back("fucking");
		std.push_back("box");

		ft.push_back("what's");
		ft.push_back("in");
		ft.push_back("the");
		ft.push_back("fucking");
		ft.push_back("box");

		PRINT(std);
		PRINT(ft);

		for (int i = 0; i < 4; ++i)
		{
			std.pop_back();
			ft.pop_back();
		}

		std.push_back("up");
		std.push_back("dog");

		ft.push_back("up");
		ft.push_back("dog");

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // assign
		std::vector<int>	std;
		ft::vector<int>		ft;

		for (int i = 0; i < 3; ++i) {
			std.push_back(i);
			ft.push_back(i);
		}

		std.assign(4, 42);
		ft.assign(4, 42);

		PRINTR(std);
		PRINTR(ft);

		int intArray[] = { 0, 0, 78, 2, 14, 8, 16, 11, 9, 25, 0 };

		std.assign(intArray + 2, intArray + (sizeof(intArray) / sizeof(int)) - 1);
		ft.assign(intArray + 2, intArray + (sizeof(intArray) / sizeof(int)) - 1);

		PRINT(std);
		PRINT(ft);

		std::vector<int>	stR;
		ft::vector<int>		ftR;

		stR.assign(std.begin() + 2, std.end() - 3);
		ftR.assign(ft.begin() + 2, ft.end() - 3);

		PRINT(stR);
		PRINT(ftR);
	}

	std::cout << "---" << std::endl;

	{ // insert and erase
		std::vector<int>	std;
		ft::vector<int>		ft;

		std.push_back(1);
		std.push_back(5);
		std.push_back(11);
		std.push_back(18);
		std.push_back(20);

		ft.push_back(1);
		ft.push_back(5);
		ft.push_back(11);
		ft.push_back(18);
		ft.push_back(20);

		// 1 5 11 18 20

		{
			std::vector<int>::iterator it = std.begin() + 1;

			it = std.insert(it, 4);
			it = std.insert(it, 3);
			std.insert(it, 2);

			std.insert(std.end() - 1, 19);
		}

		{
			ft::vector<int>::iterator	it = ft.begin() + 1;

			it = ft.insert(it, 4);
			it = ft.insert(it, 3);
			ft.insert(it, 2);

			ft.insert(ft.end() - 1, 19);
		}

		// 1 2 3 4 5 11 18 19 20

		std.insert(std.begin(), 3, 42);
		std.insert(std.end(), 3, 42);

		ft.insert(ft.begin(), 3, 42);
		ft.insert(ft.end(), 3, 42);

		// 42 42 42 1 2 3 4 5 11 18 19 20 42 42 42

		int pim[] = { 6, 7, 8, 9, 10 };

		std.insert(std.begin() + 8, pim, pim + sizeof(pim) / sizeof(int));
		ft.insert(ft.begin() + 8, pim, pim + sizeof(pim) / sizeof(int));

		// 42 42 42 1 2 3 4 5 6 7 8 9 10 11 18 19 20 42 42 42

		std.erase(std.begin(), std.begin() + 2);
		std.erase(std.end() - 2, std.end());

		ft.erase(ft.begin(), ft.begin() + 2);
		ft.erase(ft.end() - 2, ft.end());

		// 42 1 2 3 4 5 6 7 8 9 10 11 18 19 20 42

		int pam[] = { 12, 13, 14, 15, 16, 17 };

		std.insert(std.begin() + 12, pam, pam + sizeof(pam) / sizeof(int));
		ft.insert(ft.begin() + 12, pam, pam + sizeof(pam) / sizeof(int));

		// 42 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 42

		// removing all even numbers
		for (std::vector<int>::iterator it = std.begin(); it != std.end(); ++it) {
			if (*it % 2 != 0) {
				it = std.erase(it);
			}
		}

		for (ft::vector<int>::iterator it = ft.begin(); it != ft.end(); ++it) {
			if (*it % 2 != 0) {
				it = ft.erase(it);
			}
		}

		// 42 2 4 6 8 10 12 14 16 18 20 42

		int pet[] = { 22, 24, 26, 28, 30 };

		std.insert(std.end() - 1, pet, pet + sizeof(pet) / sizeof(int));
		ft.insert(ft.end() - 1, pet, pet + sizeof(pet) / sizeof(int));

		// 42 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30 42

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // swappin' 'n' clearin'
		std::vector<int>	stdFoo(3, 100);
		std::vector<int>	stdBar(5, 200);

		ft::vector<int>	ftFoo(3, 100);
		ft::vector<int>	ftBar(5, 200);

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
		int intArray[] = { 1, 3, 6, 7, 11 };

		std::vector<int>	stdFoo(intArray, intArray + sizeof(intArray) / sizeof(int));
		std::vector<int>	stdBar(stdFoo);

		ft::vector<int>	ftFoo(intArray, intArray + sizeof(intArray) / sizeof(int));
		ft::vector<int>	ftBar(ftFoo);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);

		stdBar.pop_back();
		stdBar.push_back(12);
		ftBar.pop_back();
		ftBar.push_back(12);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);

		stdFoo.pop_back();
		stdFoo.push_back(12);
		stdFoo.push_back(15);
		ftFoo.pop_back();
		ftFoo.push_back(12);
		ftFoo.push_back(15);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);
	}

	return 0;
}

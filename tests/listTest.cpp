#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <list>
#include "list.hpp"
#include <vector>

#include "memory.hpp"

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
void	printr(T const & t, char const * s) {
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

// predicate as function pointer
bool	single_digit(int const & value) { return (value < 10); }

// predicate as bracket operator overload
struct	is_odd {
	bool	operator() (int const & value) { return (value % 2) == 1; }
};

// binary predicate as function pointer
bool	same_integral_part(double first, double second) {
	return static_cast<int>(first) == static_cast<int>(second);
}

// binary predicate as bracket operator overload
struct	is_near {
	bool	operator() (double first, double second) {
		return fabs(first - second) < 5.0;
	}
};

// binary predicate as function pointer
bool	less_integral(double first, double second) {
	return static_cast<int>(first) < static_cast<int>(second);
}

// case insensitive comparison
bool	nocase_compare(std::string const & first, std::string const & second) {
	for (unsigned int i = 0; i < first.length() && i < second.length(); ++i) {
		if (tolower(first[i]) < tolower(second[i])) return true;
		if (tolower(first[i]) > tolower(second[i])) return false;
	}
	return first.length() < second.length();
}

int		main() {
	{ // tests for default constructor and max_size
		std::list<int>	std;
		ft::list<int>	ft;

		if (std.empty()) std::cout << "std is empty" << std::endl;
		if (ft.empty()) std::cout << " ft is empty" << std::endl;

		std::cout << "max size of std(int) is: " << std.max_size() << std::endl;
		std::cout << "max size of ft(int)  is: " << ft.max_size() << std::endl;
	}

	std::cout << "---" << std::endl;

	{ // test for fill constructor and max_size
		std::list<std::string>	std(3, "hello world");
		ft::list<std::string>	ft(3, "hello world");

		PRINT(std);
		PRINT(ft);

		std::cout << "max size of std(string) is: " << std.max_size() << std::endl;
		std::cout << "max size of ft(string)  is: " << ft.max_size() << std::endl;
	}

	std::cout << "---" << std::endl;

	{ // tests for range and copy constructors
		int intArray[] = { 14, 7, 9, 91, 44, 52, 1 };

		std::list<int>	std(intArray, intArray + sizeof(intArray) / sizeof(int));
		ft::list<int>	ft(intArray, intArray + sizeof(intArray) / sizeof(int));

		PRINTR(std);
		PRINTR(ft);

		ft::list<int>::iterator	it = ft.begin();
		++it;

		ft::list<int>	range(it, ft.end());
		ft::list<int>	copy(ft);

		PRINT(range);
		PRINT(copy);
	}

	std::cout << "---" << std::endl;

	{ // assignment operator
		int intArray[] = { 101, 381, 9, 88, 39 };

		std::list<int>	stdCopy(intArray, intArray + sizeof(intArray) / sizeof(int));
		ft::list<int>	ftCopy(intArray, intArray + sizeof(intArray) / sizeof(int));

		std::list<int>	std;
		ft::list<int>	ft;

		std = stdCopy;
		ft = ftCopy;

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // the only element access is at the front or the back
		std::vector<std::string>	vec;
		vec.push_back("first");
		vec.push_back("second");
		vec.push_back("third");
		vec.push_back("last");

		std::list<std::string>	std(vec.begin(), vec.end());
		ft::list<std::string>	ft(vec.begin(), vec.end());

		std::cout << "The element at the front of std is: " << std.front() << std::endl;
		std::cout << "The element at the front of ft  is: " << ft.front() << std::endl;

		std::cout << "The element at the back of std is: " << std.back() << std::endl;
		std::cout << "The element at the back of ft  is: " << ft.back() << std::endl;
	}

	std::cout << "---" << std::endl;

	{ // assign tests
		std::list<int>	std;
		ft::list<int>	ft;

		for (int i = 0; i < 3; ++i) {
			std.push_back(i);
			ft.push_back(i);
		}

		std.assign(3, 30);
		ft.assign(3, 30);

		PRINT(std);
		PRINT(ft);

		int intArray[] = { 9, 18, 27, 36, 45, 54, 63 };

		std.assign(intArray, intArray + sizeof(intArray) / sizeof(int));
		ft.assign(intArray, intArray + sizeof(intArray) / sizeof(int));

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // push and pop
		std::list<int>	std;
		ft::list<int>	ft;

		std.push_back(3);
		ft.push_back(3);
		std.push_front(2);
		ft.push_front(2);
		std.push_back(4);
		ft.push_back(4);
		std.push_front(1);
		ft.push_front(1);
		std.push_back(5);
		ft.push_back(5);

		PRINT(std);
		PRINT(ft);

		int intArray[] = { 10, 10, 10, 20, 30, 40, 50, 50, 50 };

		std.assign(intArray, intArray + sizeof(intArray) / sizeof(int));
		ft.assign(intArray, intArray + sizeof(intArray) / sizeof(int));

		std.pop_front();
		std.pop_front();
		ft.pop_front();
		ft.pop_front();

		std.pop_back();
		std.pop_back();
		ft.pop_back();
		ft.pop_back();

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // insert and erase
		int intArray[] = { 1, 2, 3, 4, 5 };

		std::list<int>	std(intArray, intArray + sizeof(intArray) / sizeof(int));
		ft::list<int>	ft(intArray, intArray + sizeof(intArray) / sizeof(int));

		std::vector<int>	range;

		range.push_back(25);
		range.push_back(33);
		range.push_back(47);
		range.push_back(63);
		range.push_back(78);

		{
			std::list<int>::iterator it = std.begin();
			it++;

			// 1 2 3 4 5
			//   ^

			std.insert(it, 10);

			// 1 10 2 3 4 5
			//      ^

			std.insert(it, 2, 20);

			// 1 10 20 20 2 3 4 5
			//            ^

			++it; ++it;

			// 1 10 20 20 2 3 4 5
			//                ^

			it = std.erase(it);

			// 1 10 20 20 2 3 5
			//                ^

			std.insert(it, range.begin(), range.end());

			// 1 10 20 20 2 3 25 33 47 63 78 5
			//                               ^

			--it; it--;

			// 1 10 20 20 2 3 25 33 47 63 78 5
			//                          ^

			std.erase(it, std.end());

			// 1 10 20 20 2 3 25 33 47

			PRINT(std);
		}

		{
			ft::list<int>::iterator it = ft.begin();
			it++;

			ft.insert(it, 10);

			ft.insert(it, 2, 20);

			++it; ++it;

			it = ft.erase(it);

			ft.insert(it, range.begin(), range.end());

			--it; it--;

			ft.erase(it, ft.end());

			PRINT(ft);
		}

		std::cout << "---" << std::endl;

		{ // resize
			std::list<int>	std;
			ft::list<int>	ft;

			for (int i = 0; i < 10; ++i) {
				std.push_front(10 - i);
				ft.push_front(10 - i);
			}

			// 1 2 3 4 5 6 7 8 9 10

			std.resize(5);
			ft.resize(5);

			// downscaling ; 1 2 3 4 5

			std.resize(8, 42);
			ft.resize(8, 42);

			// 1 2 3 4 5 42 42 42

			std.resize(12);
			ft.resize(12);

			// upscaling ; 1 2 3 4 5 42 42 42 0 0 0

			PRINT(std);
			PRINT(ft);
		}

		std::cout << "---" << std::endl;

		{ // swappin' 'n' clearin'
			std::list<int>	stdFoo(3, 100);
			std::list<int>	stdBar(5, 200);

			ft::list<int>	ftFoo(3, 100);
			ft::list<int>	ftBar(5, 200);

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
	}

	std::cout << "---" << std::endl;

	{ // relational operators
		int intArray[] = { 1, 3, 6, 7, 11 };

		std::list<int>	stdFoo(intArray, intArray + sizeof(intArray) / sizeof(int));
		std::list<int>	stdBar(stdFoo);

		ft::list<int>	ftFoo(intArray, intArray + sizeof(intArray) / sizeof(int));
		ft::list<int>	ftBar(ftFoo);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);

		stdBar.pop_front();
		stdBar.push_front(2);
		ftBar.pop_front();
		ftBar.push_front(2);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);

		stdFoo.pop_front();
		stdFoo.push_front(2);
		stdFoo.push_back(1);
		ftFoo.pop_front();
		ftFoo.push_front(2);
		ftFoo.push_back(1);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);
	}

	std::cout << "---" << std::endl;

	{ // splicin'
		std::list<int> stdFoo, stdBar;
		ft::list<int> ftFoo, ftBar;

		for (int i = 1; i <= 4; ++i) {
			stdFoo.push_back(i);
			ftFoo.push_back(i);
		} // 1 2 3 4

		for (int i = 1; i <= 3; ++i) {
			stdBar.push_back(i * 10);
			ftBar.push_back(i * 10);
		} // 10 20 30

		{
			std::list<int>::iterator it = stdFoo.begin();
			++it; // points to 2

			stdFoo.splice(it, stdBar);
			// stdFoo: 1 10 20 30 2 3 4
			// stdBar: empty
			// it still points to 2 in stdFoo

			stdBar.splice(stdBar.begin(), stdFoo, it);
			// stdFoo: 1 10 20 30 3 4
			// stdBar: 2
			// it is now invalid

			it = stdFoo.begin();
			++it;
			++it;
			++it;

			stdFoo.splice(stdFoo.begin(), stdFoo, it, stdFoo.end());
			// stdFoo: 30 3 4 1 10 20
			// stdBar: 2

			PRINT(stdFoo);
			PRINT(stdBar);
		}

		{
			ft::list<int>::iterator it = ftFoo.begin();
			++it;

			ftFoo.splice(it, ftBar);

			ftBar.splice(ftBar.begin(), ftFoo, it);

			it = ftFoo.begin();
			++it;
			++it;
			++it;

			ftFoo.splice(ftFoo.begin(), ftFoo, it, ftFoo.end());

			PRINT(ftFoo);
			PRINT(ftBar);
		}
	}

	std::cout << "---" << std::endl;

	{ // sometimes you just have to remove stuff, like a president from a white house
		int intArray[] = { 7, 79, 39, 88, 47, 16, 39, 4, 39, 18, 8, 23 };

		std::list<int>	std(intArray, intArray + sizeof(intArray) / sizeof(int));
		ft::list<int>	ft(intArray, intArray + sizeof(intArray) / sizeof(int));

		std.remove(39);
		ft.remove(39);

		PRINT(std);
		PRINT(ft);

		std.remove_if(single_digit);
		std.remove_if(is_odd());

		ft.remove_if(single_digit);
		ft.remove_if(is_odd());

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // no duplicates allowed >:(
		double doubleArray[] = { 2.72, 3.14, 12.15, 12.77, 12.77, 15.3, 72.25, 72.25, 73.0, 73.35 };

		std::list<double>	std(doubleArray, doubleArray + sizeof(doubleArray) / sizeof(double));
		ft::list<double>	ft(doubleArray, doubleArray + sizeof(doubleArray) / sizeof(double));

		std.unique();
		ft.unique();

		// 2.72 3.14 12.15 12.77 15.3 72.25 73.0 73.35

		std.unique(same_integral_part);
		ft.unique(same_integral_part);

		// 2.72 3.14 12.15 15.3 72.25 73.0

		std.unique(is_near());
		ft.unique(is_near());

		// 2.72 12.15 72.25

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // merge
		double foo[] = { 2.3, 3.9, 4.2, 4.6, 7.9 };
		double bar[] = { 1.5, 3.6, 9.1 };

		std::list<double>	stdFoo(foo, foo + sizeof(foo) / sizeof(double));
		std::list<double>	stdBar(bar, bar + sizeof(bar) / sizeof(double));

		ft::list<double>	ftFoo(foo, foo + sizeof(foo) / sizeof(double));
		ft::list<double>	ftBar(bar, bar + sizeof(bar) / sizeof(double));

		stdFoo.merge(stdBar);
		ftFoo.merge(ftBar);

		stdBar.push_front(3.3);
		ftBar.push_front(3.3);

		stdFoo.merge(stdBar, less_integral);
		ftFoo.merge(ftBar, less_integral);

		PRINT(stdFoo);
		PRINT(ftFoo);
		PRINT(stdBar);
		PRINT(ftBar);
	}

	std::cout << "---" << std::endl;

	{ // string sort
		std::list<std::string>	std(1, "pet");
		ft::list<std::string>	ft(1, "pet");

		std.push_back("Pim");
		std.push_front("pam");
		ft.push_back("Pim");
		ft.push_front("pam");
		// pam pet Pim

		std.sort();
		ft.sort();
		// Pim pam pet :D

		PRINT(std);
		PRINT(ft);

		std.sort(nocase_compare);
		ft.sort(nocase_compare);
		// pam pet Pim :'(

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // reverse
		int intArray[] = { 2, 10, 8, 4, 3, 5, 14, 6, 1, 9, 7, 8, 5 };

		std::list<int>	std(intArray, intArray + sizeof(intArray) / sizeof(int));
		ft::list<int>	ft(intArray, intArray + sizeof(intArray) / sizeof(int));

		std.remove(14);
		ft.remove(14);

		std.sort();
		ft.sort();

		std.unique();
		ft.unique();

		PRINTR(std);
		PRINTR(ft);

		std.reverse();
		ft.reverse();

		PRINTR(std);
		PRINTR(ft);
	}

	return 0;
}

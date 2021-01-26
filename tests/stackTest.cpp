#include <iomanip>
#include <iostream>
#include <list>
#include "list.hpp"
#include <stack>
#include "stack.hpp"

#define PRINT(x) print(x, #x)
#define COMP(x, y) relational_operator(x, #x, y, #y)

template <class T>
void	print(T & t, char const * s) {
	std::cout << std::setw(3) << s << " contains:";
	while (!t.empty()) {
		std::cout << ' ' << t.top();
		t.pop();
	}
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

int 	main() {
	{ // constructors and some basic functions
		std::stack<char>	std;
		ft::stack<char>		ft;

		if (std.empty()) std::cout << "std is empty" << std::endl;
		if (ft.empty()) std::cout << " ft is empty" << std::endl;

		std::cout << "size of std is: " << std.size() << std::endl;
		std::cout << "size of ft  is: " << ft.size() << std::endl;
	}

	std::cout << "---" << std::endl;

	{ // push pop and top
		std::stack<double>	std;
		ft::stack<double>	ft;

		for (int i = 1; i <= 7; ++i) {
			std.push(i / 3.0);
			ft.push(i / 3.0);
		}

		std::cout << "size of std is: " << std.size() << std::endl;
		std::cout << "size of ft  is: " << ft.size() << std::endl;

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // copy constructor
		std::stack<int>	stdCopy;
		ft::stack<int>	ftCopy;

		for (int i = 1; i <= 5; ++i) {
			stdCopy.push(i);
			ftCopy.push(i);
		}

		std::stack<int>	std(stdCopy);
		ft::stack<int>	ft(ftCopy);

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // different underlying container
		std::list<char>	stdL(3, '~');
		ft::list<char>	ftL(3, '~');

		std::stack<char, std::list<char> >	std(stdL);
		ft::stack<char, ft::list<char> >	ft(ftL);

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // relational operators
		std::stack<int>	stdFoo, stdBar;
		ft::stack<int>	ftFoo, ftBar;

		stdFoo.push(5);
		stdBar.push(5);
		ftFoo.push(5);
		ftBar.push(5);

		stdFoo.push(11);
		stdBar.push(11);
		ftFoo.push(11);
		ftBar.push(11);

		stdFoo.push(19);
		stdBar.push(19);
		ftFoo.push(19);
		ftBar.push(19);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);

		stdFoo.pop();
		stdFoo.push(21);
		ftFoo.pop();
		ftFoo.push(21);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);

		stdBar.pop();
		stdBar.push(21);
		stdBar.push(3);
		ftBar.pop();
		ftBar.push(21);
		ftBar.push(3);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);
	}
	return 0;
}

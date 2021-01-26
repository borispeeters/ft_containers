#include <iomanip>
#include <iostream>
#include <list>
#include "list.hpp"
#include <queue>
#include "queue.hpp"

#define PRINT(x) print(x, #x)
#define COMP(x, y) relational_operator(x, #x, y, #y)

template <class T>
void	print(T & t, char const * s) {
	std::cout << std::setw(3) << s << " contains:";
	while (!t.empty()) {
		std::cout << ' ' << t.front();
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
		std::queue<int>	std;
		ft::queue<int>	ft;

		if (std.empty()) std::cout << "std is empty" << std::endl;
		if (ft.empty()) std::cout << " ft is empty" << std::endl;

		std::cout << "size of std is: " << std.size() << std::endl;
		std::cout << "size of ft  is: " << ft.size() << std::endl;
	}

	std::cout << "---" << std::endl;

	{ // push pop and element access at the front and back
		std::queue<int>	std;
		ft::queue<int>	ft;

		for (int i = 1; i <= 5; ++i) {
			std.push(i);
			ft.push(i);
		}

		std::cout << "size of std is: " << std.size() << std::endl;
		std::cout << "size of ft  is: " << ft.size() << std::endl;

		std::cout << "front of std: " << std.front() << std::endl;
		std::cout << "back of std: " << std.back() << std::endl;
		std::cout << "front of ft: " << ft.front() << std::endl;
		std::cout << "back of ft: " << ft.back() << std::endl;

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // copy constructor
		std::queue<int>	stdCopy;
		ft::queue<int>	ftCopy;

		for (int i = 1; i <= 4; ++i) {
			stdCopy.push(i * 10);
			ftCopy.push(i * 10);
		}

		std::queue<int>	std(stdCopy);
		ft::queue<int>	ft(ftCopy);

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // different underlying container
		std::list<int>	stdL(4, 40);
		ft::list<int>	ftL(4, 40);

		std::queue<int, std::list<int> >	std(stdL);
		ft::queue<int, ft::list<int> >		ft(ftL);

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // relational operators
		std::queue<int>	stdFoo, stdBar;
		ft::queue<int>	ftFoo, ftBar;

		stdFoo.push(4);
		stdBar.push(4);
		ftFoo.push(4);
		ftBar.push(4);

		stdFoo.push(15);
		stdBar.push(15);
		ftFoo.push(15);
		ftBar.push(15);

		stdFoo.push(25);
		stdBar.push(25);
		ftFoo.push(25);
		ftBar.push(25);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);

		stdFoo.pop();
		stdFoo.push(33);
		ftFoo.pop();
		ftFoo.push(33);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);

		stdBar.pop();
		stdBar.push(33);
		stdBar.push(2);
		ftBar.pop();
		ftBar.push(33);
		ftBar.push(2);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);
	}
	return 0;
}

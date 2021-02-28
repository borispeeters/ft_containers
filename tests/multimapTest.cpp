#include <functional>
#include "functional.hpp"
#include <iomanip>
#include <iostream>
#include <list>
#include "list.hpp"
#include <map>
#include "map.hpp"
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

int main() {
	{ // default constructor and basic functions
		std::multimap<int, int>	std;
		ft::multimap<int, int>	ft;

		if (std.empty()) std::cout << "std is empty" << std::endl;
		if (ft.empty()) std::cout << " ft is empty" << std::endl;

		std::cout << "size of std is: " << std.size() << std::endl;
		std::cout << "size of ft  is: " << ft.size() << std::endl;

		std::cout << "max size of std(std::string, int) is: " << std.max_size() << std::endl;
		std::cout << "max size of ft(std::string, int)  is: " << ft.max_size() << std::endl;
	}

	std::cout << "---" << std::endl;

	{ // range constructor
		std::vector<std::pair<int, std::string> >	vs;
		ft::vector<ft::pair<int, std::string> >		vf;

		vs.push_back(std::make_pair(1, "cat"));
		vs.push_back(std::make_pair(2, "dog"));
		vs.push_back(std::make_pair(3, "fish"));
		vs.push_back(std::make_pair(1, "lion"));

		vf.push_back(ft::make_pair(1, "cat"));
		vf.push_back(ft::make_pair(2, "dog"));
		vf.push_back(ft::make_pair(3, "fish"));
		vf.push_back(ft::make_pair(1, "lion"));

		std::multimap<int, std::string>	std(vs.begin(), vs.end());
		ft::multimap<int, std::string>	ft(vf.begin(), vf.end());

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // copy constructor
		std::vector<std::pair<int, std::string> >	vs;
		ft::vector<ft::pair<int, std::string> >		vf;

		vs.push_back(std::make_pair(1, "red"));
		vs.push_back(std::make_pair(2, "blue"));
		vs.push_back(std::make_pair(3, "purple"));
		vs.push_back(std::make_pair(1, "green"));
		vs.push_back(std::make_pair(3, "yellow"));

		vf.push_back(ft::make_pair(1, "red"));
		vf.push_back(ft::make_pair(2, "blue"));
		vf.push_back(ft::make_pair(3, "purple"));
		vf.push_back(ft::make_pair(1, "green"));
		vf.push_back(ft::make_pair(3, "yellow"));

		std::multimap<int, std::string>	stdCopy(vs.begin(), vs.end());
		ft::multimap<int, std::string>	ftCopy(vf.begin(), vf.end());

		std::multimap<int, std::string>	std(stdCopy);
		ft::multimap<int, std::string>	ft(ftCopy);

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // assignment operator
		std::vector<std::pair<int, std::string> >	vs;
		ft::vector<ft::pair<int, std::string> >		vf;

		vs.push_back(std::make_pair(2, "germany"));
		vs.push_back(std::make_pair(1, "england"));
		vs.push_back(std::make_pair(2, "poland"));
		vs.push_back(std::make_pair(3, "spain"));
		vs.push_back(std::make_pair(1, "portugal"));

		vf.push_back(ft::make_pair(2, "germany"));
		vf.push_back(ft::make_pair(1, "england"));
		vf.push_back(ft::make_pair(2, "poland"));
		vf.push_back(ft::make_pair(3, "spain"));
		vf.push_back(ft::make_pair(1, "portugal"));

		std::multimap<int, std::string>	stdCopy(vs.begin(), vs.end());
		ft::multimap<int, std::string>	ftCopy(vf.begin(), vf.end());

		std::multimap<int, std::string>	std;
		ft::multimap<int, std::string>	ft;

		std = stdCopy;
		ft = ftCopy;

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // insert erase and find
		std::multimap<int, int>	std;
		ft::multimap<int, int>	ft;

		std::multimap<int, int>::iterator	its;
		ft::multimap<int, int>::iterator	itf;

		int val;

		for (int i = 12; i > 0; --i) {
			val = i * 3 / 2;
			std::cout << "Inserted " << std.insert(std::make_pair(val, val))->first << " in std" << std::endl;
			std::cout << "Inserted " << ft.insert(ft::make_pair(val, val))->first << " in ft" << std::endl;
		} // 1 3 4 6 7 9 10 12 13 15 16 18

		for (int i = 1; i < 10; ++i) {
			val = i * 3 / 2 + 2;
			std::cout << "Hint insertion of " << std.insert(std.begin(), std::make_pair(val, val))->first << " in std" << std::endl;
			std::cout << "Hint insertion of " << ft.insert(ft.begin(), ft::make_pair(val, val))->first << " in ft" << std::endl;
		} // 1 3 3 4 5 6 6 7 8 9 9 10 11 12 12 13 14 15 15 16 18

		std::list<std::pair<int, int> >	s;
		ft::list<ft::pair<int, int> >	f;

		val = 11;
		s.push_back(std::make_pair(val, val));
		f.push_back(ft::make_pair(val, val));

		val = 20;
		s.push_back(std::make_pair(val, val));
		f.push_back(ft::make_pair(val, val));

		val = 35;
		s.push_back(std::make_pair(val, val));
		f.push_back(ft::make_pair(val, val));

		val = 1;
		s.push_back(std::make_pair(val, val));
		f.push_back(ft::make_pair(val, val));

		val = 9;
		s.push_back(std::make_pair(val, val));
		f.push_back(ft::make_pair(val, val));

		std.insert(s.begin(), s.end());
		ft.insert(f.begin(), f.end());

		// 1 1 3 3 4 5 6 6 7 8 9 9 9 10 11 11 12 12 13 14 15 15 16 18 20 35

		PRINT(std);
		PRINT(ft);

		its = std.find(1);
		if (its != std.end()) {
			std::cout << "std: erasing " << its->first << std::endl;
			std.erase(its);
		}

		itf = ft.find(1);
		if (itf != ft.end()) {
			std::cout << " ft: erasing " << itf->first << std::endl;
			ft.erase(itf);
		}

		its = std.find(35);
		if (its != std.end()) {
			std::cout << "std: erasing " << its->first << std::endl;
			std.erase(its);
		}

		itf = ft.find(35);
		if (itf != ft.end()) {
			std::cout << " ft: erasing " << itf->first << std::endl;
			ft.erase(itf);
		}

		its = std.find(17);
		if (its != std.end()) {
			std::cout << "std: erasing " << its->first << std::endl;
			std.erase(its);
		}

		itf = ft.find(17);
		if (itf != ft.end()) {
			std::cout << " ft: erasing " << itf->first << std::endl;
			ft.erase(itf);
		}

		its = std.find(9);
		if (its != std.end()) {
			std::cout << "std: erasing " << its->first << std::endl;
			std.erase(its);
		}

		itf = ft.find(9);
		if (itf != ft.end()) {
			std::cout << " ft: erasing " << itf->first << std::endl;
			ft.erase(itf);
		}

		// 1 3 3 4 5 6 6 7 8 9 9 10 11 11 12 12 13 14 15 15 16 18 20

		for (int i = 15; i >= 5; --i) {
			for (int j = 1; j <= i; ++j) {
				std.insert(std::make_pair(j, j));
				ft.insert(ft::make_pair(j, j));
			}
		} // a lot

		for (int i = 1; i <= 15; ++i) {
			std::cout << "std: " << i << " was erased " << std.erase(i) << " times!" << std::endl;
			std::cout << " ft: " << i << " was erased " << ft.erase(i) << " times!" << std::endl;
		} // 16 18 20

		val = 16;
		std.insert(std::make_pair(val, val));
		ft.insert(ft::make_pair(val, val));

		val = 21;
		std.insert(std::make_pair(val, val));
		ft.insert(ft::make_pair(val, val));

		val = 22;
		std.insert(std::make_pair(val, val));
		ft.insert(ft::make_pair(val, val));

		val = 22;
		std.insert(std::make_pair(val, val));
		ft.insert(ft::make_pair(val, val));

		// 16 16 18 20 21 22 22

		its = std.find(18);
		--its;

		itf = ft.find(18);
		--itf;

		std.erase(its, std.find(22));
		ft.erase(itf, ft.find(22));

		// 16 22 22

		PRINT(std);
		PRINT(ft);
	}

	std::cout << "---" << std::endl;

	{ // swap and clear
		std::multimap<int, float>	stdFoo;
		std::multimap<int, float>	stdBar;

		ft::multimap<int, float>	ftFoo;
		ft::multimap<int, float>	ftBar;

		stdFoo.insert(std::make_pair(1, 1.0));
		stdFoo.insert(std::make_pair(2, 2.0));
		stdFoo.insert(std::make_pair(3, 3.0));
		stdFoo.insert(std::make_pair(2, 2.2));

		stdBar.insert(std::make_pair(10, 1.0));
		stdBar.insert(std::make_pair(10, 1.1));
		stdBar.insert(std::make_pair(20, 2.0));

		ftFoo.insert(ft::make_pair(1, 1.0));
		ftFoo.insert(ft::make_pair(2, 2.0));
		ftFoo.insert(ft::make_pair(3, 3.0));
		ftFoo.insert(ft::make_pair(2, 2.2));

		ftBar.insert(ft::make_pair(10, 1.0));
		ftBar.insert(ft::make_pair(10, 1.1));
		ftBar.insert(ft::make_pair(20, 2.0));

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
		std::multimap<std::string, std::string>	std;
		ft::multimap<std::string, std::string>	ft;

		std.insert(std::make_pair("italy", "pasta"));
		std.insert(std::make_pair("germany", "bradwurst"));
		std.insert(std::make_pair("spain", "paella"));
		std.insert(std::make_pair("france", "baguette"));

		ft.insert(ft::make_pair("italy", "pasta"));
		ft.insert(ft::make_pair("germany", "bradwurst"));
		ft.insert(ft::make_pair("spain", "paella"));
		ft.insert(ft::make_pair("france", "baguette"));

		{
			std::multimap<std::string, std::string>::key_compare	stdcomp = std.key_comp();
			std::multimap<std::string, std::string>::iterator it = std.begin();
			std::string highest = std.rbegin()->first;

			std::cout << "std contains:";
			do {
				std::cout << " (" << it->first << " => " << it->second << ')';
			} while (stdcomp((it++)->first, highest));
			std::cout << std::endl;
		}

		{
			ft::multimap<std::string, std::string>::key_compare	ftcomp = ft.key_comp();
			ft::multimap<std::string, std::string>::iterator	it = ft.begin();
			std::string highest = ft.rbegin()->first;

			std::cout << " ft contains:";
			do {
				std::cout << " (" << it->first << " => " << it->second << ')';
			} while (ftcomp((it++)->first, highest));
			std::cout << std::endl;
		}

		std.insert(std::make_pair("italy", "pizza"));
		std.insert(std::make_pair("france", "croissant"));

		ft.insert(ft::make_pair("italy", "pizza"));
		ft.insert(ft::make_pair("france", "croissant"));

		{
			std::multimap<std::string, std::string>::value_compare	stdcomp = std.value_comp();
			std::multimap<std::string, std::string>::iterator it = std.begin();
			std::pair<std::string, std::string>	highest = *std.rbegin();

			std::cout << "std contains:";
			do {
				std::cout << " (" << it->first << " => " << it->second << ')';
			} while (stdcomp(*it++, highest));
			std::cout << std::endl;
		}

		{
			ft::multimap<std::string, std::string>::value_compare	ftcomp = ft.value_comp();
			ft::multimap<std::string, std::string>::iterator	it = ft.begin();
			ft::pair<std::string, std::string>	highest = *ft.rbegin();

			std::cout << " ft contains:";
			do {
				std::cout << " (" << it->first << " => " << it->second << ')';
			} while (ftcomp(*it++, highest));
			std::cout << std::endl;
		}
	}

	std::cout << "---" << std::endl;

	{ // count
		std::multimap<int, int>	std;
		ft::multimap<int, int>	ft;

		std.insert(std::make_pair(1, 1));
		std.insert(std::make_pair(3, 3));
		std.insert(std::make_pair(4, 4));
		std.insert(std::make_pair(9, 9));
		std.insert(std::make_pair(8, 8));
		std.insert(std::make_pair(4, 4));
		std.insert(std::make_pair(6, 6));
		std.insert(std::make_pair(7, 7));
		std.insert(std::make_pair(6, 6));
		std.insert(std::make_pair(2, 2));
		std.insert(std::make_pair(10, 10));
		std.insert(std::make_pair(1, 1));
		std.insert(std::make_pair(6, 6));
		std.insert(std::make_pair(7, 7));
		std.insert(std::make_pair(5, 5));
		std.insert(std::make_pair(6, 6));
		std.insert(std::make_pair(7, 7));
		std.insert(std::make_pair(5, 5));
		std.insert(std::make_pair(7, 7));
		std.insert(std::make_pair(6, 6));

		ft.insert(ft::make_pair(1, 1));
		ft.insert(ft::make_pair(3, 3));
		ft.insert(ft::make_pair(4, 4));
		ft.insert(ft::make_pair(9, 9));
		ft.insert(ft::make_pair(8, 8));
		ft.insert(ft::make_pair(4, 4));
		ft.insert(ft::make_pair(6, 6));
		ft.insert(ft::make_pair(7, 7));
		ft.insert(ft::make_pair(6, 6));
		ft.insert(ft::make_pair(2, 2));
		ft.insert(ft::make_pair(10, 10));
		ft.insert(ft::make_pair(1, 1));
		ft.insert(ft::make_pair(6, 6));
		ft.insert(ft::make_pair(7, 7));
		ft.insert(ft::make_pair(5, 5));
		ft.insert(ft::make_pair(6, 6));
		ft.insert(ft::make_pair(7, 7));
		ft.insert(ft::make_pair(5, 5));
		ft.insert(ft::make_pair(7, 7));
		ft.insert(ft::make_pair(6, 6));

		for (int i = 1; i <= 10; ++i) {
			std::cout << i << " appears " << std.count(i) << " times in std, " << ft.count(i) << " times in ft." << std::endl;
		}
	}

	std::cout << "---" << std::endl;

	{ // lower and upper bound
		std::multimap<std::string, std::string>	std;
		ft::multimap<std::string, std::string>	ft;

		std.insert(std::make_pair("audi", "r8"));
		std.insert(std::make_pair("audi", "quattro"));
		std.insert(std::make_pair("fiat", "punto"));
		std.insert(std::make_pair("fiat", "uno"));
		std.insert(std::make_pair("fiat", "panda"));
		std.insert(std::make_pair("honda", "civic"));
		std.insert(std::make_pair("opel", "astra"));
		std.insert(std::make_pair("opel", "corsa"));
		std.insert(std::make_pair("renault", "clio"));
		std.insert(std::make_pair("seat", "ibiza"));
		std.insert(std::make_pair("toyota", "prius"));
		std.insert(std::make_pair("toyota", "corolla"));
		std.insert(std::make_pair("tesla", "model s"));
		std.insert(std::make_pair("tesla", "model 3"));
		std.insert(std::make_pair("volkswagen", "golf"));
		std.insert(std::make_pair("volkswagen", "passat"));
		std.insert(std::make_pair("volkswagen", "polo"));
		std.insert(std::make_pair("volkswagen", "tiguan"));
		std.insert(std::make_pair("volvo", "v70"));

		ft.insert(ft::make_pair("audi", "r8"));
		ft.insert(ft::make_pair("audi", "quattro"));
		ft.insert(ft::make_pair("fiat", "punto"));
		ft.insert(ft::make_pair("fiat", "uno"));
		ft.insert(ft::make_pair("fiat", "panda"));
		ft.insert(ft::make_pair("honda", "civic"));
		ft.insert(ft::make_pair("opel", "astra"));
		ft.insert(ft::make_pair("opel", "corsa"));
		ft.insert(ft::make_pair("renault", "clio"));
		ft.insert(ft::make_pair("seat", "ibiza"));
		ft.insert(ft::make_pair("toyota", "prios"));
		ft.insert(ft::make_pair("toyota", "corolla"));
		ft.insert(ft::make_pair("tesla", "model s"));
		ft.insert(ft::make_pair("tesla", "model 3"));
		ft.insert(ft::make_pair("volkswagen", "golf"));
		ft.insert(ft::make_pair("volkswagen", "passat"));
		ft.insert(ft::make_pair("volkswagen", "polo"));
		ft.insert(ft::make_pair("volkswagen", "tiguan"));
		ft.insert(ft::make_pair("volvo", "v70"));

		{
			std::multimap<std::string, std::string>::iterator it;
			std::multimap<std::string, std::string>::iterator ite;

			it = std.lower_bound("fiat");
			ite = std.upper_bound("fiat");

			std::cout << "std fiat:";
			while (it != ite) {
				std::cout << ' ' << it->second;
				++it;
			} std::cout << std::endl;

			it = std.lower_bound("volkswagen");
			ite = std.upper_bound("volkswagen");

			std::cout << "std volkswagen:";
			while (it != ite) {
				std::cout << ' ' << it->second;
				++it;
			} std::cout << std::endl;

			it = std.lower_bound("ferrari");
			ite = std.upper_bound("ferrari");

			while (it != ite) {
				std::cout << "lol i can't afford a ferrari" << std::endl;
				++it;
			}
		}

		{
			ft::multimap<std::string, std::string>::iterator it;
			ft::multimap<std::string, std::string>::iterator ite;

			it = ft.lower_bound("fiat");
			ite = ft.upper_bound("fiat");

			std::cout << " ft fiat:";
			while (it != ite) {
				std::cout << ' ' << it->second;
				++it;
			} std::cout << std::endl;

			it = ft.lower_bound("volkswagen");
			ite = ft.upper_bound("volkswagen");

			std::cout << " ft volkswagen:";
			while (it != ite) {
				std::cout << ' ' << it->second;
				++it;
			} std::cout << std::endl;

			it = ft.lower_bound("ferrari");
			ite = ft.upper_bound("ferrari");

			while (it != ite) {
				std::cout << "lol i can't afford a ferrari" << std::endl;
				++it;
			}
		}
	}

	std::cout << "---" << std::endl;

	{ // equal_range
		std::multimap<char, int>	std;
		ft::multimap<char, int>		ft;

		std.insert(std::make_pair('a', 10));
		std.insert(std::make_pair('b', 20));
		std.insert(std::make_pair('b', 30));
		std.insert(std::make_pair('b', 40));
		std.insert(std::make_pair('c', 50));
		std.insert(std::make_pair('c', 60));
		std.insert(std::make_pair('c', 70));
		std.insert(std::make_pair('c', 80));
		std.insert(std::make_pair('d', 90));
		std.insert(std::make_pair('e', 100));
		std.insert(std::make_pair('e', 150));
		std.insert(std::make_pair('g', 200));

		ft.insert(ft::make_pair('a', 10));
		ft.insert(ft::make_pair('b', 20));
		ft.insert(ft::make_pair('b', 30));
		ft.insert(ft::make_pair('b', 40));
		ft.insert(ft::make_pair('c', 50));
		ft.insert(ft::make_pair('c', 60));
		ft.insert(ft::make_pair('c', 70));
		ft.insert(ft::make_pair('c', 80));
		ft.insert(ft::make_pair('d', 90));
		ft.insert(ft::make_pair('e', 100));
		ft.insert(ft::make_pair('e', 150));
		ft.insert(ft::make_pair('g', 200));

		std::cout << "std contains:" << std::endl;
		for (char c = 'a'; c <= 'g'; ++c) {
			std::pair<std::multimap<char, int>::iterator, std::multimap<char, int>::iterator>	ret;
			ret = std.equal_range(c);
			std::cout << c << " =>";
			for (std::multimap<char, int>::iterator it = ret.first; it != ret.second; ++it) {
				std::cout << ' ' << it->second;
			} std::cout << std::endl;
		} std::cout << std::endl;

		std::cout << " ft contains:" << std::endl;
		for (char c = 'a'; c <= 'g'; ++c) {
			ft::pair<ft::multimap<char, int>::iterator, ft::multimap<char, int>::iterator>	ret;
			ret = ft.equal_range(c);
			std::cout << c << " =>";
			for (ft::multimap<char, int>::iterator it = ret.first; it != ret.second; ++it) {
				std::cout << ' ' << it->second;
			} std::cout << std::endl;
		} std::cout << std::endl;
	}

	std::cout << "---" << std::endl;

	{ // relational operators
		std::multimap<int, int>	stdFoo;
		ft::multimap<int, int>	ftFoo;

		for (int i = 1; i < 3; ++i) {
			for (int j = i; j < 4; ++j) {
				int n = j * 3 / 2;
				stdFoo.insert(std::make_pair(n, n));
				ftFoo.insert(ft::make_pair(n, n));
			}
		} // 1 3 4 3 4

		std::multimap<int, int>	stdBar(stdFoo);
		ft::multimap<int, int>	ftBar(ftFoo);

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);

		stdBar.erase(4);
		stdBar.insert(std::make_pair(5, 5));

		ftBar.erase(4);
		ftBar.insert(ft::make_pair(5, 5));

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);

		stdFoo.erase(4);
		stdFoo.insert(std::make_pair(5, 5));
		stdFoo.insert(std::make_pair(6, 6));

		ftFoo.erase(4);
		ftFoo.insert(ft::make_pair(5, 5));
		ftFoo.insert(ft::make_pair(6, 6));

		COMP(stdFoo, stdBar);
		COMP(ftFoo, ftBar);
	}

	std::cout << "---" << std::endl;

	{ // different comparison object
		std::multimap<int, int, std::greater<int> >	std;
		ft::multimap<int, int, ft::greater<int> >	ft;

		std.insert(std::make_pair(5, 5));
		std.insert(std::make_pair(3, 3));
		std.insert(std::make_pair(11, 11));
		std.insert(std::make_pair(9, 9));
		std.insert(std::make_pair(11, 11));
		std.insert(std::make_pair(7, 7));
		std.insert(std::make_pair(3, 3));

		ft.insert(ft::make_pair(5, 5));
		ft.insert(ft::make_pair(3, 3));
		ft.insert(ft::make_pair(11, 11));
		ft.insert(ft::make_pair(9, 9));
		ft.insert(ft::make_pair(11, 11));
		ft.insert(ft::make_pair(7, 7));
		ft.insert(ft::make_pair(3, 3));

		PRINT(std);
		PRINT(ft);
	}

	return 0;
}

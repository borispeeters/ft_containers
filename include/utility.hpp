#ifndef _FT_UTILITY_HPP
# define _FT_UTILITY_HPP

namespace ft
{

template <class T1, class T2>
struct pair
{
	typedef T1	first_type;
	typedef T2	second_type;

	first_type	first;
	second_type	second;

	// 1. default constructor
	pair(): first(), second() {}

	// 2. copy constructor
	template <class U, class V>
	pair(ft::pair<U, V> const & pr): first(pr.first), second(pr.second) {}

	// 3. initialization constructor
	pair(first_type const & a, second_type const & b): first(a), second(b) {}

	~pair() {}

	pair&	operator=(pair const & rhs) {
		if (&rhs != this) {
			this->first = rhs.first;
			this->second = rhs.second;
		}
		return *this;
	}
};

template <class T1, class T2>
bool operator==(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs) {
	return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <class T1, class T2>
bool operator!=(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs) {
	return !(lhs == rhs);
}

template <class T1, class T2>
bool operator<(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs) {
	return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template <class T1, class T2>
bool operator<=(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs) {
	return !(rhs < lhs);
}

template <class T1, class T2>
bool operator>(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs) {
	return rhs < lhs;
}

template <class T1, class T2>
bool operator>=(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs) {
	return !(lhs < rhs);
}

template <class T1, class T2>
ft::pair<T1, T2>	make_pair(T1 x, T2 y) {
	return ft::pair<T1, T2>(x, y);
}

} //end of namespace ft

#endif

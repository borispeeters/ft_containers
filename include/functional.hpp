#ifndef _FT_FUNCTIONAL_HPP
# define _FT_FUNCTIONAL_HPP

namespace ft
{

template <class Arg, class Result>
struct unary_function
{
	typedef Arg		argument_type;
	typedef Result	result_type;
};

template <class Arg1, class Arg2, class Result>
struct binary_function
{
	typedef Arg1	first_argument_type;
	typedef Arg2	second_argument_type;
	typedef Result	result_type;
};

template <class T>
struct equal_to : public ft::binary_function<T, T, bool> {
	bool operator()(T const & x, T const & y) const { return x == y; }
};

template <class T>
struct not_equal_to : public ft::binary_function<T, T, bool> {
	bool operator()(T const & x, T const & y) const { return x != y; }
};

template <class T>
struct greater : public ft::binary_function<T, T, bool> {
	bool operator()(T const &x, T const &y) const { return x > y; }
};

template <class T>
struct less : public ft::binary_function<T, T, bool> {
	bool operator()(T const & x, T const & y) const { return x < y; }
};

template <class T>
struct greater_equal : public ft::binary_function<T, T, bool> {
	bool operator()(T const &x, T const &y) const { return x >= y; }
};

template <class T>
struct less_equal : public ft::binary_function<T, T, bool> {
	bool operator()(T const & x, T const & y) const { return x <= y; }
};

} //end of namespace ft

#endif

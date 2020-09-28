#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft
{

template <class T>
T const &	max(T const & a, T const & b) { return (a < b) ? b : a; }

template <class T>
T const &	min(T const & a, T const & b) { return !(b < a) ? a : b; }

};

#endif

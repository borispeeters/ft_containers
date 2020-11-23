#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

# include "iterator.hpp"
# include "type_traits.hpp"

namespace ft
{

template <class T>
T const &	max(T const & a, T const & b) { return (a < b) ? b : a; }

template <class T>
T const &	min(T const & a, T const & b) { return !(b < a) ? a : b; }

template <class T>
void 		swap(T & a, T & b)
{
	T	c = a;
	a = b;
	b = c;
}

template <class Iterator>
Iterator	min_element(Iterator first, Iterator last,
						typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0)
{
	if (first == last) return first;

	Iterator	smallest = first;
	while (++first != last)
	{
		if (*first < *smallest)
			smallest = first;
	}
	return smallest;
}

template <class Iterator, class Compare>
Iterator	min_element(Iterator first, Iterator last, Compare comp,
						typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0)
{
	if (first == last) return first;

	Iterator	smallest = first;
	while (++first != last)
	{
		if (comp(*first, *smallest))
			smallest = first;
	}
	return smallest;
}

template <class Iterator>
Iterator	max_element(Iterator first, Iterator last,
						typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0)
{
	if (first == last) return first;

	Iterator	largest = first;
	while (++first != last)
	{
		if (*largest < *first)
			largest = first;
	}
	return largest;
}

template <class Iterator, class Compare>
Iterator	max_element(Iterator first, Iterator last, Compare comp,
						typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0)
{
	if (first == last) return first;

	Iterator	largest = first;
	while (++first != last)
	{
		if (comp(*largest, *first))
			largest = first;
	}
	return largest;
}

template <class Iterator1, class Iterator2>
bool equal(Iterator1 first1, Iterator1 last1, Iterator2 first2,
		   typename ft::_void_t<typename ft::iterator_traits<Iterator1>::iterator_category>::type * = 0,
		   typename ft::_void_t<typename ft::iterator_traits<Iterator2>::iterator_category>::type * = 0)
{
	while (first1 != last1)
	{
		if (!(*first1 == *first2)) return false;
		++first1; ++first2;
	}
	return true;
}

template <class Iterator1, class Iterator2, class BinaryPredicate>
bool equal(Iterator1 first1, Iterator1 last1, Iterator2 first2, BinaryPredicate pred,
		   typename ft::_void_t<typename ft::iterator_traits<Iterator1>::iterator_category>::type * = 0,
		   typename ft::_void_t<typename ft::iterator_traits<Iterator2>::iterator_category>::type * = 0)
{
	while (first1 != last1)
	{
		if (!pred(*first1, *first2)) return false;
		++first1; ++first2;
	}
	return true;
}

template <class Iterator1, class Iterator2>
bool lexicographical_compare(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2,
							 typename ft::_void_t<typename ft::iterator_traits<Iterator1>::iterator_category>::type * = 0,
							 typename ft::_void_t<typename ft::iterator_traits<Iterator2>::iterator_category>::type * = 0)
{
	while (first1 != last1)
	{
		if (first2 == last2 || *first2 < *first1) return false;
		else if (*first1 < *first2) return true;
		++first1; ++first2;
	}
	return first2 != last2;
}

template <class Iterator1, class Iterator2, class Compare>
bool lexicographical_compare(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2, Compare comp,
							 typename ft::_void_t<typename ft::iterator_traits<Iterator1>::iterator_category>::type * = 0,
							 typename ft::_void_t<typename ft::iterator_traits<Iterator2>::iterator_category>::type * = 0)
{
	while (first1 != last1)
	{
		if (first2 == last2 || comp(*first2, *first1)) return false;
		else if (comp(*first1, *first2)) return true;
		++first1; ++first2;
	}
	return first2 != last2;
}

template <class Iterator, class Function>
Function	for_each(Iterator first, Iterator last, Function fn,
					 typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0)
{
	while (first != last)
	{
		fn(*first);
		++first;
	}
	return fn;
}

} //end of namespace ft

#endif

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

};

#endif

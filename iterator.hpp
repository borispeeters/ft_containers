#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include "type_traits.hpp"
# include "vector.hpp"

namespace ft
{

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag {};
struct bidirectional_iterator_tag {};
struct random_access_iterator_tag {};

template <class Iterator>
struct iterator_traits
{
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;
};

template <typename vector>
class vectorIterator;

template <typename T>
struct iterator_traits<vectorIterator<T> >
{
	typedef typename vectorIterator<T>::value_type			value_type;
	typedef typename vectorIterator<T>::difference_type		difference_type;
	typedef typename vectorIterator<T>::pointer				pointer;
	typedef typename vectorIterator<T>::reference			reference;
	typedef typename vectorIterator<T>::iterator_category	iterator_category;
};

template <class T>
struct iterator_traits<T*>
{
	typedef std::ptrdiff_t				difference_type;
	typedef T							value_type;
	typedef T*							pointer;
	typedef T&							reference;
	typedef random_access_iterator_tag	iterator_category;
};

template <class T>
struct iterator_traits<const T*>
{
	typedef std::ptrdiff_t				difference_type;
	typedef T							value_type;
	typedef const T*					pointer;
	typedef const T&					reference;
	typedef random_access_iterator_tag	iterator_category;
};

//template <>
//struct iterator_traits<InputIterator>
//{
//	typedef typename Iterator::difference_type		difference_type;
//	typedef typename Iterator::value_type			value_type;
//	typedef typename Iterator::pointer				pointer;
//	typedef typename Iterator::reference			reference;
//	typedef typename Iterator::iterator_category	iterator_category;
//};
//
//template <>
//struct iterator_traits<output_iterator_tag>;
//
//template <>
//struct iterator_traits<forward_iterator_tag>;
//
//template <>
//struct iterator_traits<bidirectional_iterator_tag>;
//
//template <>
//struct iterator_traits<random_access_iterator_tag>;

template <class Iterator>
class reverse_iterator
{
public:
	typedef Iterator												iterator_type;
	typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename iterator_traits<Iterator>::value_type			value_type;
	typedef typename iterator_traits<Iterator>::difference_type 	difference_type;
	typedef typename iterator_traits<Iterator>::pointer				pointer;
	typedef typename iterator_traits<Iterator>::reference			reference;

private:
	iterator_type	_base_iterator;
public:
	// 1. default constructor
	reverse_iterator();
	// 2. initialization constructor
	explicit reverse_iterator(iterator_type it);
	// 3. copy / type-cast constructor
	template <class Iter>
	reverse_iterator(const reverse_iterator<Iter> & rev_it);
	iterator_type	base() const { return _base_iterator; }
};

template <typename T>
struct is_iterator { static const bool value = false; };

template <>
struct is_iterator<input_iterator_tag> { static const bool	value = true; };

template <>
struct is_iterator<output_iterator_tag> { static const bool	value = true; };

template <>
struct is_iterator<forward_iterator_tag> { static const bool	value = true; };

template <>
struct is_iterator<bidirectional_iterator_tag> { static const bool	value = true; };

template <>
struct is_iterator<random_access_iterator_tag> { static const bool	value = true; };

template <class Iterator>
typename iterator_traits<Iterator>::difference_type
	distance(Iterator first, Iterator last,
		  typename enable_if<is_iterator<typename iterator_traits<Iterator>::iterator_category>::value, Iterator>::type * = 0)
{
	typename iterator_traits<Iterator>::difference_type	distance = 0;

	while (first != last)
	{
		++first;
		++distance;
	}
	return distance;
}

};

#endif

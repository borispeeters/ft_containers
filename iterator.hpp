#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

namespace ft
{

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag {};
struct bidirectional_iterator_tag {};
struct random_access_iterator_tag {};

template <	class Category,						// iterator::iterator_category
			class T,							// iterator::value_type
			class Distance = std::ptrdiff_t,	// iterator::difference_type
			class Pointer = T*,					// iterator::pointer
			class Reference = T&				// iterator::reference
		>
struct iterator
{
	typedef	T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef	Category	iterator_category;
};

template <class Iterator>
struct iterator_traits
{
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;
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
//class iterator_traits<input_iterator_tag>
//{
//	typedef input_iterator_tag::difference_type difference_type;
//};

template <>
class iterator_traits<output_iterator_tag>;

template <>
class iterator_traits<forward_iterator_tag>;

template <>
class iterator_traits<bidirectional_iterator_tag>;

template <>
class iterator_traits<random_access_iterator_tag>;

template <class InputIterator>
typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last)
{

}

};

#endif

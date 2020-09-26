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

template <class Category,
		class T,
		class Distance = ptrdiff_t,
		class Pointer = T*,
		class Reference = T&
		>
struct iterator
{
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
};

template <class Iterator>
struct iterator_traits {};

template <class vector>
class vectorIterator;

template <class T>
struct iterator_traits<ft::vectorIterator<T> >
{
	typedef typename ft::vectorIterator<T>::value_type			value_type;
	typedef typename ft::vectorIterator<T>::difference_type		difference_type;
	typedef typename ft::vectorIterator<T>::pointer				pointer;
	typedef typename ft::vectorIterator<T>::reference			reference;
	typedef typename ft::vectorIterator<T>::iterator_category	iterator_category;
};

template <class T>
struct iterator_traits<T*>
{
	typedef std::ptrdiff_t					difference_type;
	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef ft::random_access_iterator_tag	iterator_category;
};

template <class T>
struct iterator_traits<const T*>
{
	typedef std::ptrdiff_t					difference_type;
	typedef T								value_type;
	typedef const T*						pointer;
	typedef const T&						reference;
	typedef ft::random_access_iterator_tag	iterator_category;
};

template <class Iterator>
class reverse_iterator
{
public:
	typedef Iterator													iterator_type;
	typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
	typedef typename ft::iterator_traits<Iterator>::difference_type 	difference_type;
	typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
	typedef typename ft::iterator_traits<Iterator>::reference			reference;

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
template <typename>
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
	if (typeid(typename ft::iterator_traits<Iterator>::iterator_category).name() == typeid(ft::random_access_iterator_tag).name())
	{
		std::cout << "random access iterator distance called" << std::endl;
		return static_cast<typename iterator_traits<Iterator>::difference_type>(last - first);
	}
	std::cout << "bidirectional iterator distance called" << std::endl;
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

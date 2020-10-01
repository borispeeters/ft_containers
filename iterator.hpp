#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include "type_traits.hpp"

namespace ft
{

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

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

template <class T>
struct _has_iterator_typedefs
{
private:
	struct	_two { char _lx; char _lxx; };
	template <class U>	static _two _test(...);
	template <class U>	static char _test(typename	ft::_void_t<typename U::iterator_category>::type * = 0,
											 typename	ft::_void_t<typename U::difference_type>::type * = 0,
											 typename	ft::_void_t<typename U::value_type>::type * = 0,
											 typename	ft::_void_t<typename U::reference>::type * = 0,
											 typename	ft::_void_t<typename U::pointer>::type * = 0
											 );
public:
	static const bool value = sizeof(_test<T>(0,0,0,0,0)) == 1;
};

template <class T>
struct _has_iterator_category
{
private:
	struct _two { char _lx; char _lxx; };
	template <class U>	static _two	_test(...);
	template <class U>	static char	_test(typename U::iterator_category * = 0);
public:
	static const bool value = sizeof(_test<T>(0)) == 1;
};

template <class Iter, bool>
struct _iterator_traits {};

template <class Iter>
struct _iterator_traits<Iter, true>
{
	typedef	typename Iter::value_type			value_type;
	typedef	typename Iter::difference_type		difference_type;
	typedef	typename Iter::pointer				pointer;
	typedef	typename Iter::reference			reference;
	typedef	typename Iter::iterator_category	iterator_category;
};

template <class Iter>
struct iterator_traits : public _iterator_traits<Iter, _has_iterator_typedefs<Iter>::value> {};

template <class T>
struct iterator_traits<T*>
{
	typedef T								value_type;
	typedef std::ptrdiff_t					difference_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef ft::random_access_iterator_tag	iterator_category;
};

template <class T>
struct iterator_traits<const T*>
{
	typedef T								value_type;
	typedef std::ptrdiff_t					difference_type;
	typedef const T*						pointer;
	typedef const T&						reference;
	typedef ft::random_access_iterator_tag	iterator_category;
};


template <class Iter>
struct is_iterator : public _has_iterator_category<Iter> {};

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

template <class Iterator>
typename iterator_traits<Iterator>::difference_type
	distance(Iterator first, Iterator last,
			 typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0)
{
	typename iterator_traits<Iterator>::difference_type	distance = 0;

	while (first != last)
	{
		++first;
		++distance;
	}
	return distance;
}

}; //end of namespace ft

#endif

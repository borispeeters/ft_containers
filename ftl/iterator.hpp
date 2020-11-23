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

template <class Iterator>
class reverse_iterator : public ft::iterator<typename ft::iterator_traits<Iterator>::iterator_category,
											typename ft::iterator_traits<Iterator>::value_type,
											typename ft::iterator_traits<Iterator>::difference_type,
											typename ft::iterator_traits<Iterator>::pointer,
											typename ft::iterator_traits<Iterator>::reference>
{
public:
	typedef Iterator													iterator_type;
	typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
	typedef typename ft::iterator_traits<Iterator>::difference_type 	difference_type;
	typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
	typedef typename ft::iterator_traits<Iterator>::reference			reference;

protected:
	iterator_type	current;

public:
	// 1. default constructor
	reverse_iterator(): current() {}

	// 2. initialization constructor
	explicit reverse_iterator(iterator_type it,
							  typename ft::_void_t<typename ft::iterator_traits<iterator_type>::iterator_category>::type * = 0): current(it) {}

	// 3. copy / type-cast constructor
	template <class Iter>
	reverse_iterator(reverse_iterator<Iter> const & rev_it): current(rev_it.base()) {}

	// assignment operator overload
	template <class Iter>
	reverse_iterator&	operator=(reverse_iterator<Iter> const & rev_it)
	{
		this->current = rev_it.base();
		return *this;
	}

	iterator_type	base() const { return this->current; }

	reference	operator*() const
	{
		iterator_type tmp(this->current);
		return *--tmp;
	}
	pointer		operator->() const { return &(this->operator*()); }

	reverse_iterator&	operator++()
	{
		--this->current;
		return *this;
	}

	reverse_iterator	operator++(int)
	{
		reverse_iterator	tmp(*this);
		++(*this);
		return tmp;
	}

	reverse_iterator&	operator--()
	{
		++this->current;
		return *this;
	}

	reverse_iterator	operator--(int)
	{
		reverse_iterator	tmp(*this);
		--(*this);
		return tmp;
	}

	reverse_iterator	operator+(difference_type n) const { return reverse_iterator(current - n); }

	reverse_iterator&	operator+=(difference_type n)
	{
		current -= n;
		return *this;
	}

	reverse_iterator	operator-(difference_type n) const { return reverse_iterator(current + n); }

	reverse_iterator&	operator-=(difference_type n)
	{
		current += n;
		return *this;
	}

	reference	operator[](difference_type n) const { return *(*this + n); }
};

template <class Iterator>
bool operator==(reverse_iterator<Iterator> const & lhs, reverse_iterator<Iterator> const & rhs) {
	return lhs.base() == rhs.base();
}

template <class Iterator>
bool operator!=(reverse_iterator<Iterator> const & lhs, reverse_iterator<Iterator> const & rhs) {
	return lhs.base() != rhs.base();
}

template <class Iterator>
bool operator<(reverse_iterator<Iterator> const & lhs, reverse_iterator<Iterator> const & rhs) {
	return lhs.base() > rhs.base();
}

template <class Iterator>
bool operator>(reverse_iterator<Iterator> const & lhs, reverse_iterator<Iterator> const & rhs) {
	return lhs.base() < rhs.base();
}

template <class Iterator>
bool operator<=(reverse_iterator<Iterator> const & lhs, reverse_iterator<Iterator> const & rhs) {
	return lhs.base() >= rhs.base();
}

template <class Iterator>
bool operator>=(reverse_iterator<Iterator> const & lhs, reverse_iterator<Iterator> const & rhs) {
	return lhs.base() <= rhs.base();
}

template <class Iterator>
reverse_iterator<Iterator>	operator+(typename reverse_iterator<Iterator>::difference_type n,
										reverse_iterator<Iterator> const & rev_it) {
	return reverse_iterator<Iterator>(rev_it.base() - n);
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type
operator-(reverse_iterator<Iterator> const & lhs, reverse_iterator<Iterator> const & rhs) {
	return rhs.base() - lhs.base();
}

template <class InputIter>
typename ft::iterator_traits<InputIter>::difference_type
	_distance(InputIter first, InputIter last, ft::input_iterator_tag)
{
	typename ft::iterator_traits<InputIter>::difference_type	dist(0);
	for (; first != last; ++first)
		++dist;
	return dist;
}

template <class RandIter>
typename ft::iterator_traits<RandIter>::difference_type
	_distance(RandIter first, RandIter last, ft::random_access_iterator_tag) {
	return last - first;
}

template <class InputIter>
typename ft::iterator_traits<InputIter>::difference_type
	distance(InputIter first, InputIter last,
			 typename ft::_void_t<typename ft::iterator_traits<InputIter>::iterator_category>::type * = 0) {
	return ft::_distance(first, last, typename ft::iterator_traits<InputIter>::iterator_category());
}

template <class InputIter>
void _advance(InputIter & it,
			  typename ft::iterator_traits<InputIter>::difference_type n, ft::input_iterator_tag) {
	for (; n > 0; --n) ++it;
}

template <class BiDirIter>
void _advance(BiDirIter & it,
			  typename ft::iterator_traits<BiDirIter>::difference_type n, ft::bidirectional_iterator_tag)
{
	if (n >= 0) for (; n > 0; --n) ++it;
	else for (; n < 0; ++n) --it;
}

template <class RandIter>
void _advance(RandIter & it,
			  typename ft::iterator_traits<RandIter>::difference_type n, ft::random_access_iterator_tag) {
	it += n;
}

template <class InputIter>
void advance(InputIter & it, typename ft::iterator_traits<InputIter>::difference_type n,
			 typename ft::_void_t<typename ft::iterator_traits<InputIter>::iterator_category>::type * = 0) {
	ft::_advance(it, n, typename ft::iterator_traits<InputIter>::iterator_category());
}

template <class ForwardIter>
void _next(ForwardIter & it, typename ft::iterator_traits<ForwardIter>::difference_type n, ft::forward_iterator_tag) {
	if (n >= 0)
		ft::advance(it, n);
}

template <class BiDirIter>
void _next(BiDirIter & it, typename ft::iterator_traits<BiDirIter>::difference_type n, ft::bidirectional_iterator_tag) {
	ft::advance(it, n);
}

template <class RandIter>
void _next(RandIter & it, typename ft::iterator_traits<RandIter>::difference_type n, ft::random_access_iterator_tag) {
	ft::advance(it, n);
}

template <class ForwardIterator>
ForwardIterator	next(ForwardIterator it, typename ft::iterator_traits<ForwardIterator>::difference_type n = 1,
					typename ft::_void_t<typename ft::iterator_traits<ForwardIterator>::iterator_category>::type * = 0) {
	ft::_next(it, n, typename ft::iterator_traits<ForwardIterator>::iterator_category());
	return it;
}

template <class BidirectionalIterator>
BidirectionalIterator	prev(BidirectionalIterator it, typename ft::iterator_traits<BidirectionalIterator>::difference_type n = 1,
							  typename ft::_void_t<typename ft::iterator_traits<BidirectionalIterator>::iterator_category>::type * = 0) {
	ft::advance(it, -n);
	return it;
}

} //end of namespace ft

#endif

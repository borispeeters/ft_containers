#ifndef DEQUEITERATOR_HPP
# define DEQUEITERATOR_HPP

# include <cstddef>
# include "iterator.hpp"

namespace ft
{

template <class T>
class dequeIterator : public ft::iterator<ft::random_access_iterator_tag, T>
{
public:
	typedef T								value_type;
	typedef std::ptrdiff_t					difference_type;
	typedef value_type*						pointer;
	typedef value_type&						reference;
	typedef const value_type*				const_pointer;
	typedef const value_type&				const_reference;
	typedef ft::random_access_iterator_tag	iterator_category;

private:
	// variables lol

public:
	dequeIterator();
	dequeIterator(pointer ptr);
	dequeIterator(dequeIterator const & other);
	dequeIterator&	operator=(dequeIterator const & rhs);
	virtual ~dequeIterator();
};

};

#endif

#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

# include <cstddef>
# include "iterator.hpp"

namespace ft
{

template <class T>
class vectorIterator : public ft::iterator<ft::random_access_iterator_tag, T>
{
public:
	typedef	T								value_type;
	typedef	std::ptrdiff_t					difference_type;
	typedef	value_type*						pointer;
	typedef value_type&						reference;
	typedef ft::random_access_iterator_tag	iterator_category;

private:
	pointer m_ptr;

public:
	vectorIterator(): m_ptr(0) {}
	vectorIterator(pointer ptr): m_ptr(ptr) {}
	vectorIterator(vectorIterator const & other): m_ptr(other.m_ptr) {}
	vectorIterator&	operator=(vectorIterator const & rhs)
	{
		if (&rhs != this) this->m_ptr = rhs.m_ptr;
		return *this;
	}
	~vectorIterator() {}

	vectorIterator& operator++()
	{
		++this->m_ptr;
		return *this;
	}
	vectorIterator  operator++(int)
	{
		vectorIterator  iterator = *this;
		++(*this);
		return iterator;
	}
	vectorIterator& operator--()
	{
		--this->m_ptr;
		return *this;
	}
	vectorIterator  operator--(int)
	{
		vectorIterator  iterator = *this;
		--(*this);
		return iterator;
	}
	vectorIterator&	operator+=(difference_type rhs)
	{
		this->m_ptr += rhs;
		return *this;
	}
	vectorIterator&	operator-=(difference_type rhs)
	{
		this->m_ptr -= rhs;
		return *this;
	}
	vectorIterator&	operator+=(vectorIterator const & rhs)
	{
		this->m_ptr += rhs.m_ptr;
		return *this;
	}
	vectorIterator&	operator-=(vectorIterator const & rhs)
	{
		this->m_ptr -= rhs.m_ptr;
		return *this;
	}
	friend	vectorIterator	operator+(vectorIterator const & lhs, vectorIterator const & rhs) { return vectorIterator(lhs.m_ptr + rhs.m_ptr); }
	friend	vectorIterator	operator+(vectorIterator const & lhs, difference_type rhs) { return vectorIterator(lhs.m_ptr + rhs); }
	friend	vectorIterator	operator+(difference_type lhs, vectorIterator const & rhs) { return vectorIterator(lhs + rhs.m_ptr); }
	friend	vectorIterator	operator-(vectorIterator const & lhs, vectorIterator const & rhs) { return vectorIterator(lhs.m_ptr - rhs.m_ptr); }
	friend	vectorIterator	operator-(vectorIterator const & lhs, difference_type rhs) { return vectorIterator(lhs.m_ptr - rhs); }
	friend	vectorIterator	operator-(difference_type lhs, vectorIterator const & rhs) { return vectorIterator(lhs - rhs.m_ptr); }
	reference	operator[](int index) { return *(this->m_ptr + index); }
	pointer		operator->() { return this->m_ptr; }
	reference	operator*() { return *this->m_ptr; }
	bool		operator==(vectorIterator const & rhs) const { return this->m_ptr == rhs.m_ptr; }
	bool 		operator!=(vectorIterator const & rhs) const { return !(*this == rhs); }
	bool 		operator<(vectorIterator const & rhs) { return this->m_ptr < rhs.m_ptr; }
	bool 		operator>(vectorIterator const & rhs) { return rhs < *this; }
	bool 		operator<=(vectorIterator const & rhs) { return !(rhs < *this); }
	bool 		operator>=(vectorIterator const & rhs) { return !(*this < rhs); }
};

}; //end of namespace ft

#endif

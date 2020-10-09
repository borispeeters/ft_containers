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
	typedef const value_type* 				const_pointer;
	typedef const value_type&				const_reference;
	typedef ft::random_access_iterator_tag	iterator_category;

protected:
	pointer m_ptr;

public:
	vectorIterator(): m_ptr(0) {}
	vectorIterator(pointer ptr): m_ptr(ptr) {}
	vectorIterator(vectorIterator const & other): m_ptr(other.data()) {}
	vectorIterator&	operator=(vectorIterator const & rhs)
	{
		if (&rhs != this) this->m_ptr = rhs.data();
		return *this;
	}
	virtual ~vectorIterator() {}

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
		this->m_ptr += rhs.data();
		return *this;
	}
	vectorIterator&	operator-=(vectorIterator const & rhs)
	{
		this->m_ptr -= rhs.data();
		return *this;
	}
	friend	vectorIterator	operator+(vectorIterator const & lhs, vectorIterator const & rhs) { return vectorIterator(lhs.m_ptr + rhs.m_ptr); }
	friend	vectorIterator	operator+(vectorIterator const & lhs, difference_type rhs) { return vectorIterator(lhs.m_ptr + rhs); }
	friend	vectorIterator	operator+(difference_type lhs, vectorIterator const & rhs) { return vectorIterator(lhs + rhs.m_ptr); }
	friend	vectorIterator	operator-(vectorIterator const & lhs, vectorIterator const & rhs) { return vectorIterator(lhs.m_ptr - rhs.m_ptr); }
	friend	vectorIterator	operator-(vectorIterator const & lhs, difference_type rhs) { return vectorIterator(lhs.m_ptr - rhs); }
	friend	vectorIterator	operator-(difference_type lhs, vectorIterator const & rhs) { return vectorIterator(lhs - rhs.m_ptr); }
	bool		operator==(vectorIterator const & rhs) const { return this->m_ptr == rhs.m_ptr; }
	bool 		operator!=(vectorIterator const & rhs) const { return !(*this == rhs); }
	bool 		operator<(vectorIterator const & rhs) const { return this->m_ptr < rhs.m_ptr; }
	bool 		operator>(vectorIterator const & rhs) const { return rhs < *this; }
	bool 		operator<=(vectorIterator const & rhs) const { return !(rhs < *this); }
	bool 		operator>=(vectorIterator const & rhs) const { return !(*this < rhs); }
	reference	operator[](int index) { return *(this->m_ptr + index); }
	pointer		operator->() { return this->m_ptr; }
	reference	operator*() { return *this->m_ptr; }
	pointer		data() const { return this->m_ptr; }
};

template <class T>
class constVectorIterator : public vectorIterator<T>
{
public:
	typedef	T								value_type;
	typedef	std::ptrdiff_t					difference_type;
	typedef	value_type*						pointer;
	typedef value_type&						reference;
	typedef const value_type* 				const_pointer;
	typedef const value_type&				const_reference;
	typedef ft::random_access_iterator_tag	iterator_category;


	constVectorIterator(): vectorIterator<value_type>() {}
	constVectorIterator(pointer ptr): vectorIterator<value_type>(ptr) {}
	constVectorIterator(vectorIterator<value_type> const & other): vectorIterator<value_type>(other) {}
	constVectorIterator(constVectorIterator const & other): vectorIterator<value_type>(other.data()) {}
	constVectorIterator&	operator=(vectorIterator<value_type> const & rhs)
	{
		if (&rhs != this) this->m_ptr = rhs.data();
		return *this;
	}
	constVectorIterator&	operator=(constVectorIterator const & rhs)
	{
		if (&rhs != this) this->m_ptr = rhs.data();
		return *this;
	}
	virtual ~constVectorIterator() {}

	const_reference	operator[](int index) const { return *(this->m_ptr + index); }
	const_pointer	operator->() const { return this->m_ptr; }
	const_reference	operator*() const { return *this->m_ptr; }
	const_pointer	data() const { return this->m_ptr; }

};

}; //end of namespace ft

#endif

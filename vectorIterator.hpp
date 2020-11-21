#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

# include <cstddef>
# include "iterator.hpp"

namespace ft
{

template <class T>
class vectorIterator : public ft::iterator<ft::random_access_iterator_tag, T>
{

	template <class, class> friend class vector;

public:
	typedef	T								value_type;
	typedef	std::ptrdiff_t					difference_type;
	typedef	value_type*						pointer;
	typedef const value_type* 				const_pointer;
	typedef value_type&						reference;
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
		vectorIterator  tmp(*this);
		++(*this);
		return tmp;
	}

	vectorIterator& operator--()
	{
		--this->m_ptr;
		return *this;
	}

	vectorIterator  operator--(int)
	{
		vectorIterator  tmp(*this);
		--(*this);
		return tmp;
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

	vectorIterator	operator+(difference_type rhs) const {
		return vectorIterator(this->data() + rhs);
	}

	friend	vectorIterator	operator+(difference_type lhs, vectorIterator const & rhs) {
		return vectorIterator(lhs + rhs.m_ptr);
	}

	difference_type	operator-(vectorIterator const & rhs) const {
		return this->data() - rhs.m_ptr;
	}

	vectorIterator	operator-(difference_type rhs) const {
		return vectorIterator(this->data() - rhs);
	}

	bool		operator==(vectorIterator const & rhs) const { return this->m_ptr == rhs.m_ptr; }
	bool 		operator!=(vectorIterator const & rhs) const { return !(*this == rhs); }
	bool 		operator<(vectorIterator const & rhs) const { return this->m_ptr < rhs.m_ptr; }
	bool 		operator>(vectorIterator const & rhs) const { return rhs < *this; }
	bool 		operator<=(vectorIterator const & rhs) const { return !(rhs < *this); }
	bool 		operator>=(vectorIterator const & rhs) const { return !(*this < rhs); }
	reference	operator[](difference_type idx) { return *(this->m_ptr + idx); }
	pointer		operator->() { return this->m_ptr; }
	reference	operator*() { return *this->m_ptr; }

protected:
	pointer		data() const { return this->m_ptr; }
};

template <class T>
class constVectorIterator : public vectorIterator<T>
{
public:
	typedef	T								value_type;
	typedef	std::ptrdiff_t					difference_type;
	typedef	value_type*						pointer;
	typedef const value_type* 				const_pointer;
	typedef value_type&						reference;
	typedef const value_type&				const_reference;
	typedef ft::random_access_iterator_tag	iterator_category;

	constVectorIterator(): vectorIterator<value_type>() {}
	constVectorIterator(pointer ptr): vectorIterator<value_type>(ptr) {}
	constVectorIterator(vectorIterator<value_type> const & other): vectorIterator<value_type>(other) {}
	constVectorIterator(constVectorIterator const & other): vectorIterator<value_type>() { *this = other; }
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

	const_reference	operator[](difference_type idx) const { return *(this->m_ptr + idx); }
	const_pointer	operator->() const { return this->m_ptr; }
	const_reference	operator*() const { return *this->m_ptr; }
};

}; //end of namespace ft

#endif

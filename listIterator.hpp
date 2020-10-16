#ifndef LISTITERATOR_HPP
# define LISTITERATOR_HPP

# include "iterator.hpp"
# include "listNode.hpp"

namespace ft
{

template <class T>
class listIterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
{
public:
	typedef	T								value_type;
	typedef	std::ptrdiff_t					difference_type;
	typedef	value_type*						pointer;
	typedef const value_type* 				const_pointer;
	typedef value_type&						reference;
	typedef const value_type&				const_reference;
	typedef ft::bidirectional_iterator_tag	iterator_category;

protected:
	listNode<value_type>*	m_node;

public:
	listIterator(): m_node(0) {}
	listIterator(listNode<value_type>* n): m_node(n) {}
	listIterator(listIterator const & other): m_node(other.node()) {}
	listIterator&	operator=(listIterator const & rhs)
	{
		if (&rhs != this) this->m_node = rhs.node();
		return *this;
	}
	virtual ~listIterator() {}

	listIterator& operator++()
	{
		this->m_node = this->node()->next;
		return *this;
	}
	listIterator  operator++(int)
	{
		listIterator  iterator(*this);
		++(*this);
		return iterator;
	}
	listIterator& operator--()
	{
		this->m_node = this->node()->prev;
		return *this;
	}
	listIterator  operator--(int)
	{
		listIterator  iterator(*this);
		--(*this);
		return iterator;
	}

	pointer		operator->() const { return this->node()->data; }
	reference	operator*() const { return *this->node()->data; }
	bool		operator==(listIterator const & rhs) const { return this->node() == rhs.node(); }
	bool 		operator!=(listIterator const & rhs) const { return !(*this == rhs); }

	listNode<value_type>*	node() const { return this->m_node; }
};

template <class T>
class constListIterator : public listIterator<T>
{
public:
	typedef	T								value_type;
	typedef	std::ptrdiff_t					difference_type;
	typedef	value_type*						pointer;
	typedef const value_type* 				const_pointer;
	typedef value_type&						reference;
	typedef const value_type&				const_reference;
	typedef ft::bidirectional_iterator_tag	iterator_category;

	constListIterator(): listIterator<value_type>() {}
	constListIterator(listNode<value_type>* n): listIterator<value_type>(n) {}
	constListIterator(listIterator<value_type> const & other): listIterator<value_type>(other) {}
	constListIterator(constListIterator const & other): listIterator<value_type>(other.node()) {}
	constListIterator&	operator=(listIterator<value_type> const & rhs)
	{
		if (&rhs != this) this->m_node = rhs.node();
		return *this;
	}
	constListIterator&	operator=(constListIterator const & rhs)
	{
		if (&rhs != this) this->m_node = rhs.node();
		return *this;
	}
	virtual ~constListIterator() {}

	const_pointer	operator->() const { return this->node()->data; }
	const_reference	operator*() const { return *this->node()->data; }
};

}; //end of namespace ft

#endif

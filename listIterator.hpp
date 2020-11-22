#ifdef _FT_LIST_HPP

#ifndef _FT_LISTITERATOR_HPP
# define _FT_LISTITERATOR_HPP

# include <memory>

# include "iterator.hpp"
# include "listNode.hpp"

# include "list.hpp"

namespace ft
{

template <class T>
class listIterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
{

	template <class, class> friend class list;

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
		listIterator  tmp(*this);
		++(*this);
		return tmp;
	}

	listIterator& operator--()
	{
		this->m_node = this->node()->prev;
		return *this;
	}

	listIterator  operator--(int)
	{
		listIterator  tmp(*this);
		--(*this);
		return tmp;
	}

	pointer		operator->() const { return this->node()->data; }
	reference	operator*() const { return *this->node()->data; }

	friend bool	operator==(listIterator const & lhs, listIterator const & rhs) { return lhs.node() == rhs.node(); }
	friend bool	operator!=(listIterator const & lhs, listIterator const & rhs) { return !(lhs == rhs); }

protected:
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

# else
# error "Please include list.hpp to access its iterator."
#endif
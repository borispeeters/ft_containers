#ifndef LISTITERATOR_HPP
# define LISTITERATOR_HPP

# include "iterator.hpp"
# include "listNode.hpp"

namespace ft
{

template <class T>
class listIterator : public iterator<ft::bidirectional_iterator_tag, T>
{
public:
	typedef	T								value_type;
	typedef	std::ptrdiff_t					difference_type;
	typedef	value_type*						pointer;
	typedef value_type&						reference;
	typedef ft::bidirectional_iterator_tag	iterator_category;

private:
	typedef listNode<T>*					node;

	node m_node;

public:
	listIterator(): m_node(0) {}
	listIterator(node n): m_node(n) {}
	listIterator(listIterator const & other): m_node(other.m_node) {}
	listIterator&	operator=(listIterator const & rhs)
	{
		if (&rhs != this) this->m_node = rhs.m_node;
		return *this;
	}
	~listIterator() {}
	listIterator& operator++()
	{
		this->m_node = this->m_node->next;
		return *this;
	}
	listIterator  operator++(int)
	{
		listIterator  iterator = *this;
		++(*this);
		return iterator;
	}
	listIterator& operator--()
	{
		this->m_node = this->m_node->prev;
		return *this;
	}
	listIterator  operator--(int)
	{
		listIterator  iterator = *this;
		--(*this);
		return iterator;
	}
	pointer		operator->() { return this->m_node->data; }
	reference	operator*() { return *this->m_node->data; }
	bool		operator==(listIterator const & rhs) const { return this->m_node == rhs.m_node; }
	bool 		operator!=(listIterator const & rhs) const { return !(*this == rhs); }
};

}; //end of namespace ft

#endif

#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

# include "iterator.hpp"
# include "mapNode.hpp"

namespace ft
{

template <class T>
class mapIterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
{
public:
	typedef	T								value_type;
	typedef std::ptrdiff_t					difference_type;
	typedef value_type*						pointer;
	typedef value_type&						reference;
	typedef	ft::bidirectional_iterator_tag	iterator_category;

private:
	mapNode<value_type>*	m_node;

public:
	mapIterator(): m_node(0) {}
	mapIterator(mapNode<value_type>* n): m_node(n) {}
	mapIterator(mapIterator const & other): m_node(other.node()) {}
	mapIterator&	operator=(mapIterator const & rhs)
	{
		if (&rhs != this) this->m_node = rhs.node();
		return *this;
	}
	~mapIterator() {}

	mapIterator&	operator++()
	{
		this->m_node;
		return *this;
	}

	pointer		operator->() const { return this->node()->value; }
	reference	operator*() const { return *this->node()->value; }
	bool 		operator==(mapIterator const & rhs) const { return this->node() == rhs.node(); }
	bool 		operator!=(mapIterator const & rhs) const { return !(*this == rhs); }

	mapNode<value_type>*	node() const { return this->m_node; }
};

}; //end of namespace ft

#endif

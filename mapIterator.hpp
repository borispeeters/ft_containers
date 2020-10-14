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
		if (this->node() == this->lastNode())
			this->m_node = this->node()->right;
		else if (this->node()->right)
		{
			this->m_node = this->node()->right;
			this->m_node = leftEnd(this->node());
			std::cout << "yey" << m_node->value->first << std::endl;
		}
		else
		{
			mapNode<value_type>*	prev(this->node());
			this->m_node = this->node()->parent;
			while (this->node()->right == prev)
			{
				prev = this->node();
				this->m_node = this->node()->parent;
			}
		}
		return *this;
	}
	mapIterator&	operator++(int)
	{
		mapIterator	iterator(*this);
		++(*this);
		return iterator;
	}
	mapIterator&	operator--()
	{
		if (this->node() == this->firstNode())
			this->m_node = this->node()->left;
		else if (this->node()->left)
		{
			this->m_node = this->node()->left;
			this->m_node = rightEnd(this->node());
		}
		else
		{
			mapNode<value_type>*	prev(this->node());
			this->m_node = this->node()->parent;
			while (this->node()->left == prev)
			{
				prev = this->node();
				this->m_node = this->node()->parent;
			}
		}
		return *this;
	}
	mapIterator&	operator--(int)
	{
		mapIterator	iterator(*this);
		--(*this);
		return iterator;
	}

	pointer		operator->() const { return this->node()->value; }
	reference	operator*() const { return *this->node()->value; }
	bool 		operator==(mapIterator const & rhs) const { return this->node() == rhs.node(); }
	bool 		operator!=(mapIterator const & rhs) const { return !(*this == rhs); }

	mapNode<value_type>*	node() const { return this->m_node; }

private:
	mapNode<value_type>*	leftEnd(mapNode<value_type>* node)
	{
		while (node->left)
			node = node->left;
		return node;
	}
	mapNode<value_type>*	rightEnd(mapNode<value_type>* node)
	{
		int i = 0;
		while (node->right && i < 10)
		{
			std::cout << node->value->first << std::endl;
			node = node->right;
			++i;
		}
		return node;
	}
	mapNode<value_type>*	findRoot()
	{
		mapNode<value_type>*	root(this->node());
		while (root->parent)
			root = root->parent;
		return root;
	}

	mapNode<value_type>*	firstNode() { return leftEnd(findRoot()); }
	mapNode<value_type>*	lastNode() { return rightEnd(findRoot()); }
};

}; //end of namespace ft

#endif

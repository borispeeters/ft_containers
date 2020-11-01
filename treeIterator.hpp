#ifndef TREEITERATOR_HPP
# define TREEITERATOR_HPP

# include <cstddef>
# include "iterator.hpp"
# include "treeNode.hpp"

namespace ft
{

template <class T>
class treeIterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
{
public:
	typedef T								value_type;
	typedef std::ptrdiff_t					difference_type;
	typedef value_type*						pointer;
	typedef const value_type*				const_pointer;
	typedef value_type&						reference;
	typedef const value_type&				const_reference;
	typedef ft::bidirectional_iterator_tag	iterator_category;

protected:
	treeNode<value_type>*	m_node;

public:
	treeIterator(): m_node(0) {}
	treeIterator(treeNode<value_type>* n): m_node(n) {}
	treeIterator(treeIterator const & other): m_node(other.node()) {}
	treeIterator&	operator=(treeIterator const & rhs)
	{
		if (&rhs != this) this->m_node = rhs.node();
		return *this;
	}
	~treeIterator() {}

	treeIterator&	operator++()
	{
		if (this->node() == this->lastNode())
			this->m_node = this->node()->right;
		else if (this->node()->right)
		{
			this->m_node = this->node()->right;
			this->m_node = this->leftEnd(this->node());
		}
		else
		{
			treeNode<value_type>*	prev(this->node());
			this->m_node = this->node()->parent;
			while (this->node()->right == prev)
			{
				prev = this->node();
				this->m_node = this->node()->parent;
			}
		}
		return *this;
	}

	treeIterator&	operator++(int)
	{
		treeIterator	it(*this);
		++(*this);
		return it;
	}

	treeIterator&	operator--()
	{
		if (this->node() == this->firstNode())
			this->m_node = this->node()->left;
		else if (this->node()->left)
		{
			this->m_node = this->node()->left;
			this->m_node = this->rightEnd(this->node());
		}
		else
		{
			treeNode<value_type>*	prev(this->node());
			this->m_node = this->node()->parent;
			while (this->node()->left == prev)
			{
				prev = this->node();
				this->m_node = this->node()->parent;
			}
		}
		return *this;
	}

	treeIterator&	operator--(int)
	{
		treeIterator	it(*this);
		--(*this);
		return it;
	}

	pointer		operator->() const { return this->node()->value; }
	reference	operator*() const { return *this->node()->value; }
	bool 		operator==(treeIterator const & rhs) const { return this->node() == rhs.node(); }
	bool 		operator!=(treeIterator const & rhs) const { return !(*this == rhs); }

	treeNode<value_type>*	node() const { return this->m_node; }

private:
	treeNode<value_type>*	leftEnd(treeNode<value_type>* node) const
	{
		while (node->left)
			node = node->left;
		return node;
	}

	treeNode<value_type>*	rightEnd(treeNode<value_type>* node) const
	{
		while (node->right)
			node = node->right;
		return node;
	}

	treeNode<value_type>*	findRoot() const
	{
		treeNode<value_type>*	root(this->node());
		while (root->parent)
			root = root->parent;
		return root;
	}

	treeNode<value_type>*	firstNode() const { return this->leftEnd(this->findRoot()); }
	treeNode<value_type>*	lastNode() const { return this->rightEnd(this->findRoot()); }
};

template <class T>
class constTreeIterator : public treeIterator<T>
{
public:
	typedef T								value_type;
	typedef std::ptrdiff_t					difference_type;
	typedef value_type*						pointer;
	typedef const value_type*				const_pointer;
	typedef value_type&						reference;
	typedef const value_type&				const_reference;
	typedef ft::bidirectional_iterator_tag	iterator_category;

	constTreeIterator(): treeIterator<value_type>() {}
	constTreeIterator(treeNode<value_type>* n): treeIterator<value_type>(n) {}
	constTreeIterator(treeIterator<value_type> const & other): treeIterator<value_type>(other) {}
	constTreeIterator(constTreeIterator const & other): treeIterator<value_type>(other.node()) {}
	constTreeIterator&	operator=(treeIterator<value_type> const & rhs)
	{
		if (&rhs != this) this->m_node = rhs.node();
		return *this;
	}
	constTreeIterator&	operator=(constTreeIterator const & rhs)
	{
		if (&rhs != this) this->m_node = rhs.node();
		return *this;
	}
	virtual ~constTreeIterator() {}

	const_pointer	operator->() const { return this->node()->value; }
	const_reference	operator*() const { return *this->node()->value; }
};

}; //end of namespace ft

#endif

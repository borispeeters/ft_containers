#ifndef SETITERATOR_HPP
# define SETITERATOR_HPP

# include "iterator.hpp"
# include "setNode.hpp"

namespace ft
{

template <class T>
class setIterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
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
	setNode<value_type>*	m_node;

public:
	setIterator(): m_node(0) {}
	setIterator(setNode<value_type>* n): m_node(n) {}
	setIterator(setIterator const & other): m_node(other.node()) {}
	setIterator&	operator=(setIterator const & rhs)
	{
		if (&rhs != this) this->m_node = rhs.node();
		return *this;
	}
	~setIterator() {}

	setIterator&	operator++()
	{
		if (this->node() == this->lastNode())
			this->m_node = this->node()->right;
		else if (this->node()->right)
		{
			this->m_node = this->node()->right;
			this->m_node() = this->leftEnd(this->node());
		}
		else
		{
			setNode<value_type>*	prev(this->node());
			this->m_node = this->node()->parent;
			while (this->node()->right == prev)
			{
				prev = this->node();
				this->m_node = this->node()->parent;
			}
		}
		return *this;
	}

	setIterator&	operator++(int)
	{
		setIterator	it(*this);
		++(*this);
		return it;
	}

	setIterator&	operator--()
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
			setNode<value_type>*	prev(this->node());
			this->m_node = this->node()->parent;
			while (this->node()->left == prev)
			{
				prev = this->node();
				this->m_node = this->node()->parent;
			}
		}
		return *this;
	}

	setIterator&	operator--(int)
	{
		setIterator	it(*this);
		--(*this);
		return it;
	}

	pointer 	operator->() const { return this->node()->value; }
	reference	operator*() const { return *this->node()->value; }
	bool 		operator==(setIterator const & rhs) const { return this->node() == rhs.node(); }
	bool 		operator!=(setIterator const & rhs) const { return !(*this == rhs); }

	setNode<value_type>*	node() const { return this->m_node; }

private:
	setNode<value_type>*	leftEnd(setNode<value_type>* node) const
	{
		while (node->left)
			node = node->left;
		return node;
	}

	setNode<value_type>*	rightEnd(setNode<value_type>* node) const
	{
		while (node->right)
			node = node->right;
		return node;
	}

	setNode<value_type>*	findRoot() const
	{
		setNode<value_type>*	root(this->node());
		while (root->parent)
			root = root->parent;
		return root;
	}

	setNode<value_type>*	firstNode() const { return this->leftEnd(this->findRoot()); }
	setNode<value_type>*	lastNode() const { return this->rightEnd(this->findRoot()); }
};

template <class T>
class constSetIterator : public setIterator<T>
{
public:
	typedef	T								value_type;
	typedef std::ptrdiff_t					difference_type;
	typedef value_type*						pointer;
	typedef const value_type*				const_pointer;
	typedef value_type&						reference;
	typedef const value_type&				const_reference;
	typedef ft::bidirectional_iterator_tag	iterator_category;

	constSetIterator(): setIterator<value_type>() {}
	constSetIterator(setNode<value_type>* n): setIterator<value_type>(n) {}
	constSetIterator(setIterator<value_type> const & other): setIterator<value_type>(other) {}
	constSetIterator(constSetIterator const & other): setIterator<value_type>(other.node()) {}
	constSetIterator&	operator=(setIterator<value_type> const & rhs)
	{
		if (&rhs != this) this->m_node = rhs.node();
		return *this;
	}
	constSetIterator&	operator=(constSetIterator const & rhs)
	{
		if (&rhs != this) this->m_node = rhs.node();
		return *this;
	}
	virtual ~constSetIterator() {}

	const_pointer	operator->() const { return this->node()->value; }
	const_reference	operator*() const { return *this->node()->value; }
};

}; //end of namespace ft

#endif

#ifdef _FT_TREE

#ifndef _FT_TREEITERATOR_HPP
# define _FT_TREEITERATOR_HPP

# include <cstddef>
# include "iterator.hpp"
# include "_tree.hpp"

namespace ft
{

template <class T>
class treeIterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
{

	template <class, class, class, class> friend class mapBase;
	template <class, class, class, class> friend class map;
	template <class, class, class, class> friend class multimap;
	template <class, class, class> friend class setBase;
	template <class, class, class> friend class set;
	template <class, class, class> friend class multiset;

public:
	typedef T								value_type;
	typedef std::ptrdiff_t					difference_type;
	typedef value_type*						pointer;
	typedef const value_type*				const_pointer;
	typedef value_type&						reference;
	typedef const value_type&				const_reference;
	typedef ft::bidirectional_iterator_tag	iterator_category;

protected:
	RBTree<value_type>*		m_tree;
	treeNode<value_type>*	m_node;

public:
	treeIterator(): m_tree(NULL), m_node(NULL) {}
	treeIterator(RBTree<value_type>* t, treeNode<value_type>* n): m_tree(t), m_node(n) {}
	treeIterator(treeIterator const & other): m_tree(other.tree()), m_node(other.node()) {}
	treeIterator&	operator=(treeIterator const & rhs)
	{
		if (&rhs != this)
		{
			this->m_tree = rhs.tree();
			this->m_node = rhs.node();
		}
		return *this;
	}
	virtual ~treeIterator() {}

	treeIterator&	operator++()
	{
		if (this->node()->right != this->tree()->NIL)
		{
			this->m_node = this->node()->right;
			this->m_node = this->leftEnd(this->node());
		}
		else
		{
			treeNode<value_type>*	prev = this->node();
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
		if (this->node()->left != this->tree()->NIL)
		{
			this->m_node = this->node()->left;
			this->m_node = this->rightEnd(this->node());
		}
		else
		{
			treeNode<value_type>*	prev = this->node();
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

	friend bool operator==(treeIterator const & lhs, treeIterator const & rhs) { return lhs.node() == rhs.node(); }
	friend bool operator!=(treeIterator const & lhs, treeIterator const & rhs) { return !(lhs == rhs); }

protected:
	RBTree<value_type>*		tree() const { return this->m_tree; }

	treeNode<value_type>*	node() const { return this->m_node; }

	treeNode<value_type>*	leftEnd(treeNode<value_type>* node) const
	{
		while (node->left != this->tree()->NIL)
			node = node->left;
		return node;
	}

	treeNode<value_type>*	rightEnd(treeNode<value_type>* node) const
	{
		while (node->right != this->tree()->NIL)
			node = node->right;
		return node;
	}

	treeNode<value_type>*	root() const
	{
		if (this->tree())
			return this->tree()->m_root;
		return NULL;
	}

	treeNode<value_type>*	firstNode() const
	{
		if (this->tree())
			return this->tree()->m_first;
		return NULL;
	}
	treeNode<value_type>*	lastNode() const
	{
		if (this->tree())
			return this->tree()->m_last;
		return NULL;
	}
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
	constTreeIterator(RBTree<value_type>* t, treeNode<value_type>* n): treeIterator<value_type>(t, n) {}
	constTreeIterator(treeIterator<value_type> const & other): treeIterator<value_type>(other) {}
	constTreeIterator(constTreeIterator const & other): treeIterator<value_type>(other.tree(), other.node()) {}

	constTreeIterator&	operator=(treeIterator<value_type> const & rhs)
	{
		if (&rhs != this)
		{
			this->m_tree = rhs.tree();
			this->m_node = rhs.node();
		}
		return *this;
	}

	constTreeIterator&	operator=(constTreeIterator const & rhs)
	{
		if (&rhs != this)
		{
			this->m_tree = rhs.tree();
			this->m_node = rhs.node();
		}
		return *this;
	}

	virtual ~constTreeIterator() {}

	const_pointer	operator->() const { return this->node()->value; }
	const_reference	operator*() const { return *this->node()->value; }
};

} //end of namespace ft

#endif

# else
# error "Please include the appropriate associative container in the ft namespace to access its iterator."
#endif

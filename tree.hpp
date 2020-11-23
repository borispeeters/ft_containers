#ifdef _FT_TREE

#ifndef _FT_TREE_HPP
# define _FT_TREE_HPP

# include <cstddef>

namespace ft
{

enum Colour { RED, BLACK };

template <class T>
struct treeNode
{
	T			*value;
	treeNode	*left;
	treeNode	*right;
	treeNode	*parent;
	enum Colour	colour;

	treeNode(): value(new T), left(NULL), right(NULL), parent(NULL), colour(RED) {}
	treeNode(T const & val): value(new T(val)), left(NULL), right(NULL), parent(NULL), colour (RED) {}
	treeNode(treeNode const & other): value(NULL) { *this = other; }
	treeNode(enum Colour col): value(new T), left(NULL), right(NULL), parent(NULL), colour(col) {}
	~treeNode() { delete this->value; }
	treeNode&	operator=(treeNode const & rhs)
	{
		if (&rhs != this)
		{
			delete this->value;
			this->value = new T(rhs.value);
			this->left = rhs.left;
			this->right = rhs.right;
			this->parent = rhs.parent;
			this->colour = rhs.colour;
		}
		return *this;
	}
};

template <class T>
struct	RBTree
{
	treeNode<T>*	NIL;
	treeNode<T>*	m_root;
	treeNode<T>*	m_first;
	treeNode<T>*	m_last;

	RBTree():
		NIL(new treeNode<T>(BLACK)),
		m_root(NIL),
		m_first(new treeNode<T>(BLACK)),
		m_last(new treeNode<T>(BLACK))
	{
		this->linkOuter();
	}

	RBTree(RBTree const & other):
		NIL(NULL),
		m_root(NULL),
		m_first(NULL),
		m_last(NULL)
	{
		*this = other;
		this->linkOuter();
	}

	~RBTree()
	{
		delete this->NIL;
		delete this->m_first;
		delete this->m_last;
	}

	RBTree&	operator=(RBTree const & rhs)
	{
		if (&rhs != this)
		{
			delete this->NIL;
			delete this->m_first;
			delete this->m_last;
			this->NIL = new treeNode<T>(rhs.NIL);
			this->m_root = rhs.m_root;
			this->m_first = new treeNode<T>(rhs.m_first);
			this->m_last = new treeNode<T>(rhs.m_last);
		}
		return *this;
	}

private:
	void linkOuter()
	{
		this->m_root->parent = this->NIL;
		this->m_first->left = this->NIL;
		this->m_first->right = this->NIL;
		this->m_last->left = this->NIL;
		this->m_last->right = this->NIL;
	}
};

}; //end of namespace ft

#endif

# else
# error "This is an internal binary tree used by the associative containers in the ft namespace and is not intended to be included directly."
#endif

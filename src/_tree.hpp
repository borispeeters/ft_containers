#ifdef _FT_TREE

#ifndef _FT_TREE_HPP
# define _FT_TREE_HPP

# include <cstddef>
# include "algorithm.hpp"

namespace ft
{

enum Colour { RED, BLACK };

template <class T>
struct treeNode
{
	T			value;
	enum Colour	colour;
	treeNode	*left;
	treeNode	*right;
	treeNode	*parent;

	treeNode(T const & val = T()): value(val), colour(RED), left(NULL), right(NULL), parent(NULL) {}
	treeNode(treeNode const & other): value(other.value), colour(other.colour), left(other.left), right(other.right), parent(other.parent) {}
	treeNode(enum Colour col): value(T()), colour(col), left(NULL), right(NULL), parent(NULL) {}
	~treeNode() {}

	treeNode&	operator=(treeNode const & rhs) {
		if (&rhs != this) {
			this->value = rhs.value;
			this->left = rhs.left;
			this->right = rhs.right;
			this->parent = rhs.parent;
			this->colour = rhs.colour;
		}
		return *this;
	}
};

template <class T, class Alloc>
struct	RBTree
{
	treeNode<T>*	NIL;
	treeNode<T>*	m_root;
	treeNode<T>*	m_first;
	treeNode<T>*	m_last;
	Alloc			m_alloc;

	RBTree():
		NIL(NULL),
		m_root(NIL),
		m_first(NULL),
		m_last(NULL),
		m_alloc() {
		this->treeInit();
	}

	RBTree(RBTree const &):
		NIL(NULL),
		m_root(NIL),
		m_first(NULL),
		m_last(NULL),
		m_alloc() {
		this->treeInit();
	}

	~RBTree() {
		this->treeTerminate();
	}

	RBTree&	operator=(RBTree const & rhs) {
		if (&rhs != this) {
			this->m_alloc = rhs.m_alloc;
		}
		return *this;
	}

	void swap(RBTree & rhs) {
		ft::swap(this->NIL, rhs.NIL);
		ft::swap(this->m_root, rhs.m_root);
		ft::swap(this->m_first, rhs.m_first);
		ft::swap(this->m_last, rhs.m_last);
		ft::swap(this->m_alloc, rhs.m_alloc);
	}

private:
	void treeInit() {
		this->NIL = this->m_alloc.allocate(1);
		this->m_first = this->m_alloc.allocate(1);
		this->m_last = this->m_alloc.allocate(1);

		this->m_alloc.construct(this->NIL, BLACK);
		this->m_alloc.construct(this->m_first, BLACK);
		this->m_alloc.construct(this->m_last, BLACK);

		this->NIL->parent = this->NIL;
		this->NIL->left = this->NIL;
		this->NIL->right = this->NIL;
		this->m_first->left = this->NIL;
		this->m_first->right = this->NIL;
		this->m_last->left = this->NIL;
		this->m_last->right = this->NIL;

		this->m_root = this->NIL;
	}

	void treeTerminate() {
		this->m_alloc.destroy(this->NIL);
		this->m_alloc.destroy(this->m_first);
		this->m_alloc.destroy(this->m_last);
		this->m_alloc.deallocate(this->NIL, 1);
		this->m_alloc.deallocate(this->m_first, 1);
		this->m_alloc.deallocate(this->m_last, 1);
	}
};

} //end of namespace ft

#endif

#else
# error "This is an internal binary tree used by the associative containers in the ft namespace and is not intended to be included directly."
#endif

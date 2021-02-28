#ifdef _FT_TREE

#ifndef _FT_TREEBASE_HPP
# define _FT_TREEBASE_HPP

# include <cstddef>
# include "_tree.hpp"
# include "_treeIterator.hpp"
# include "algorithm.hpp"
# include "functional.hpp"
# include "iterator.hpp"
# include "memory.hpp"
# include "type_traits.hpp"

namespace ft
{

template <class Key,
        class T,
        class Val,
        class Compare,
        class Alloc
        >
class treeBase
{
	typedef typename Alloc::template rebind<treeNode<Val> >::other	node_allocator;

public:
	typedef Key														key_type;
	typedef T														mapped_type;
	typedef Val														value_type;
	typedef Compare													key_compare;
	typedef Alloc													allocator_type;
	typedef typename allocator_type::reference						reference;
	typedef typename allocator_type::const_reference				const_reference;
	typedef typename allocator_type::pointer						pointer;
	typedef typename allocator_type::const_pointer					const_pointer;
	typedef ft::treeIterator<value_type, node_allocator>			iterator;
	typedef ft::constTreeIterator<value_type, node_allocator>		const_iterator;
	typedef ft::reverse_iterator<iterator>							reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
	typedef std::ptrdiff_t											difference_type;
	typedef typename allocator_type::size_type						size_type;

protected:
	typedef treeNode<value_type>									node;
	typedef RBTree<value_type, node_allocator>						rbtree;

	rbtree			m_tree;
	size_type		m_size;
	key_compare		m_comp;
	node_allocator	m_alloc;

public:
	// default constructor
	explicit treeBase(key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type()):
	m_tree(rbtree()),
	m_size(0),
	m_comp(comp),
	m_alloc(alloc) {
		this->treeInit();
	}

	// copy constructor
	treeBase(treeBase const & other):
	m_tree(rbtree()),
	m_size(0),
	m_comp(other.m_comp),
	m_alloc(other.get_allocator()) {
		this->treeInit();
	}

	// destructor
	virtual ~treeBase() {}

	// assignment operator overload
	treeBase&	operator=(treeBase const & rhs) {
		if (&rhs != this) {
			this->m_alloc = rhs.m_alloc;
			this->m_comp = rhs.m_comp;
		}
		return *this;
	}

	iterator		begin() { return iterator(this->m_tree, this->firstNode()->parent); }
	const_iterator	begin() const { return const_iterator(this->m_tree, this->firstNode()->parent); }
	iterator		end() { return iterator(this->m_tree, this->lastNode()); }
	const_iterator	end() const { return const_iterator(this->m_tree, this->lastNode()); }

	reverse_iterator 		rbegin() { return reverse_iterator(this->end()); }
	const_reverse_iterator	rbegin() const { return const_reverse_iterator(this->end()); }
	reverse_iterator 		rend() { return reverse_iterator(this->begin()); }
	const_reverse_iterator	rend() const { const_reverse_iterator(this->begin()); }

	bool 		empty() const { return this->size() == 0; }
	size_type	size() const { return this->m_size; }

	size_type	max_size() const {
		return ft::min<size_type>(this->m_alloc.max_size(),
								  std::numeric_limits<difference_type>::max());
	}

	void	swap(treeBase & x) {
		this->m_tree.swap(x.m_tree);
		ft::swap(this->m_size, x.m_size);
		ft::swap(this->m_comp, x.m_comp);
		ft::swap(this->m_alloc, x.m_alloc);
	}

	virtual size_type	count(key_type const & k) const = 0;

	allocator_type	get_allocator() const { return this->m_alloc; }

protected:
	void	treeInit() {
		this->m_tree.m_root = this->NIL();
		this->firstNode()->parent = this->lastNode();
		this->lastNode()->parent = this->firstNode();
	}

	void 	detach() {
		this->firstNode()->parent->left = this->NIL();
		this->lastNode()->parent->right = this->NIL();
	}

	void 	attach() {
		node*	f = this->root();
		node*	l = this->root();

		while (f->left != this->NIL() && f->left != this->firstNode()) {
			f = f->left;
		}

		f->left = this->firstNode();
		this->firstNode()->parent = f;

		while (l->right != this->NIL() && l->right != this->lastNode()) {
			l = l->right;
		}

		l->right = this->lastNode();
		this->lastNode()->parent = l;
	}

	bool	validNode(node* n) const {
		return (n != NULL && n != this->NIL() && n != this->firstNode() && n != this->lastNode());
	}

	node*	root() const { return this->m_tree.m_root; }
	node*	firstNode() const { return this->m_tree.m_first; }
	node*	lastNode() const { return this->m_tree.m_last; }
	node*	NIL() const { return this->m_tree.NIL; }

	void	BSTerase(iterator position) {
		this->detach();

		node*	z = position.node();
		node*	y = z;
		node*	x = NULL;
		enum Colour	origYColour = y->colour;

		if (z->left == this->NIL()) { // z has only right child or no children
			x = z->right;
			this->transplant(z, z->right);
		}
		else if (z->right == this->NIL()) { // z has only left child
			x = z->left;
			this->transplant(z, z->left);
		}
		else { // z has two children
			iterator temp = position;
			++temp;
			y = temp.node();

			origYColour = y->colour;
			x = y->right;
			if (y->parent == z)
				x->parent = y;
			else {
				this->transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			this->transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->colour = z->colour;
		}

		this->m_alloc.destroy(z);
		this->m_alloc.deallocate(z, 1);

		if (origYColour == BLACK) {
			this->fixEraseViolation(x);
		}

		this->attach();
	}

	void	transplant(node* u, node* v)
	{
		if (u == this->root())
			this->m_tree.m_root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else if (u == u->parent->right)
			u->parent->right = v;
		v->parent = u->parent;
	}

/*
**		Left rotation on x
**     --------------------
**
**           4              4              4                 4
**          / \            / \            / \               / \
**         /   \          /   \          /   \             /   \
**        /     \        /     \        /     \           /     \
**       X       5      X       5      Y       5         Y       5
**      / \            / \              \               / \
**     /   \          /   \              3     X       X   3
**    1     Y        1     2    Y             / \     / \
**         / \                   \           1   2   1   2
**        2   3                   3
**
*/

	void rotateLeft(node* x)
	{
		node*	y = x->right;

		x->right = y->left;
		if (y->left != this->NIL())
			y->left->parent = x;
		y->parent = x->parent;
		if (x == this->root())
			this->m_tree.m_root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else if (x == x->parent->right)
			x->parent->right = y;
		y->left = x;
		x->parent = y;
	}

	void rotateRight(node* x)
	{
		node*	y = x->left;

		x->left = y->right;
		if (y->right != this->NIL())
			y->right->parent = x;
		y->parent = x->parent;
		if (x == this->root())
			this->m_tree.m_root = y;
		else if (x == x->parent->right)
			x->parent->right = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		y->right = x;
		x->parent = y;
	}

	void fixInsertViolation(node* z)
	{
		while (z != this->root() && z->colour != BLACK && z->parent->colour == RED)
		{
			// parent is left child of grandparent
			if (z->parent == z->parent->parent->left)
			{
				node*	y = z->parent->parent->right;
				if (y->colour == RED)
				{
					z->parent->colour = BLACK;
					y->colour = BLACK;
					z->parent->parent->colour = RED;
					z = z->parent->parent;
				}
				else
				{
					// node is right child of parent, rotate left
					if (z == z->parent->right)
					{
						z = z->parent;
						rotateLeft(z);
					}
					// node is left child of parent, swap parent and grandparent colour and rotate right
					z->parent->colour = BLACK;
					z->parent->parent->colour = RED;
					rotateRight(z->parent->parent);
				}
			}
				// parent is right child of grandparent
			else if (z->parent == z->parent->parent->right)
			{
				node*	y = z->parent->parent->left;
				if (y->colour == RED)
				{
					z->parent->colour = BLACK;
					y->colour = BLACK;
					z->parent->parent->colour = RED;
					z = z->parent->parent;
				}
				else
				{
					// node is left child of parent, rotate right
					if (z == z->parent->left)
					{
						z = z->parent;
						rotateRight(z);
					}
					// node is right child of parent, swap parent and grandparent colour and rotate left
					z->parent->colour = BLACK;
					z->parent->parent->colour = RED;
					rotateLeft(z->parent->parent);
				}
			}
		}
		this->root()->colour = BLACK;
	}

	void	fixEraseViolation(node* x)
	{
		while (x != this->root() && x->colour == BLACK)
		{
			if (x == x->parent->left)
			{
				node*	w = x->parent->right;
				if (w->colour == RED)
				{
					w->colour = BLACK;
					x->parent->colour = RED;
					this->rotateLeft(x->parent);
					w = x->parent->right;
				}
				if (w->left->colour == BLACK && w->right->colour == BLACK)
				{
					w->colour = RED;
					x = x->parent;
				}
				else
				{
					if (w->right->colour == BLACK)
					{
						w->left->colour = BLACK;
						w->colour = RED;
						this->rotateRight(w);
						w = x->parent->right;
					}
					w->colour = x->parent->colour;
					x->parent->colour = BLACK;
					w->right->colour = BLACK;
					this->rotateLeft(x->parent);
					x = this->root();
				}
			}
			else if (x == x->parent->right)
			{
				node*	w = x->parent->left;
				if (w->colour == RED)
				{
					w->colour = BLACK;
					x->parent->colour = RED;
					this->rotateRight(x->parent);
					w = x->parent->left;
				}
				if (w->right->colour == BLACK && w->left->colour == BLACK)
				{
					w->colour = RED;
					x = x->parent;
				}
				else
				{
					if (w->left->colour == BLACK)
					{
						w->right->colour = BLACK;
						w->colour = RED;
						this->rotateLeft(w);
						w = x->parent->left;
					}
					w->colour = x->parent->colour;
					x->parent->colour = BLACK;
					w->left->colour = BLACK;
					this->rotateRight(x->parent);
					x = this->root();
				}
			}
		}
		x->colour = BLACK;
	}
};

} //end of namespace ft

#endif

# else
# error "This is an internal binary tree used by the associative containers in the ft namespace and is not intended to be included directly."
#endif

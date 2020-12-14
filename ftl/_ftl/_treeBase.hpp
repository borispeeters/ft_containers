#ifdef _FT_TREE

#ifndef _FT_TREEBASE_HPP
# define _FT_TREEBASE_HPP

# include <cstddef>
# include "_tree.hpp"
# include "_treeIterator.hpp"
# include "../algorithm.hpp"
# include "../functional.hpp"
# include "../iterator.hpp"
# include "../memory.hpp"
# include "../type_traits.hpp"

namespace ft
{

template <class Key,
        class T,
        class Val,
        class Compare = ft::less<Key>,
        class Alloc = ft::allocator<Val>
        >
class treeBase
{
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
	typedef ft::treeIterator<value_type>							iterator;
	typedef ft::constTreeIterator<value_type>						const_iterator;
	typedef ft::reverse_iterator<iterator>							reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
	typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
	typedef typename allocator_type::size_type						size_type;

protected:
	typedef treeNode<value_type>									node;
	typedef RBTree<value_type>										rbtree;

	rbtree*			m_tree;
	size_type		m_size;
	key_compare		m_comp;
	allocator_type	m_alloc;

public:
	// default constructor
	explicit treeBase(key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type()):
	m_tree(new rbtree()),
	m_size(0),
	m_comp(comp),
	m_alloc(alloc) {
		this->treeInit();
	}

	// copy constructor
	treeBase(treeBase const & other):
	m_tree(new rbtree(other.m_tree)),
	m_size(0),
	m_comp(other.key_comp()),
	m_alloc(other.get_allocator()) {
		this->treeInit();
	}

	// destructor
	virtual ~treeBase() {
		delete this->m_tree;
	}

	// assignment operator overload
	treeBase&	operator=(treeBase const & rhs)
	{
		if (&rhs != this)
		{
			this->m_alloc = this->get_allocator();
			this->m_comp = this->key_comp();
		}
		return *this;
	}


	iterator		begin() { return iterator(this->tree(), this->firstNode()->parent); }
	const_iterator	begin() const { return const_iterator(this->tree(), this->firstNode()->parent); }
	iterator		end() { return iterator(this->tree(), this->lastNode()); }
	const_iterator	end() const { return const_iterator(this->tree(), this->lastNode()); }

	reverse_iterator 		rbegin() { return reverse_iterator(this->end()); }
	const_reverse_iterator	rbegin() const { return const_reverse_iterator(this->end()); }
	reverse_iterator 		rend() { return reverse_iterator(this->begin()); }
	const_reverse_iterator	rend() const { const_reverse_iterator(this->begin()); }

	bool 		empty() const { return this->size() == 0; }
	size_type	size() const { return this->m_size; }
	size_type	max_size() const { return this->get_allocator().max_size(); }

	void	swap(treeBase & x)
	{
		ft::swap(this->m_tree, x.m_tree);
		ft::swap(this->m_size, x.m_size);
		ft::swap(this->m_comp, x.m_comp);
		ft::swap(this->m_alloc, x.m_alloc);
	}

	virtual size_type	count(key_type const & k) const = 0;

	allocator_type	get_allocator() const {
		return this->m_alloc;
	}

protected:
	void	treeInit() {
		this->tree()->m_root = this->NIL();
		this->firstNode()->parent = this->lastNode();
	}

	bool	validNode(treeNode<value_type>* node) const {
		return (node != NULL && node != this->NIL() && node != this->firstNode() && node != this->lastNode());
	}

	rbtree*		tree() const { return this->m_tree; }

	node*	root() const
	{
		if (this->tree())
			return this->tree()->m_root;
		return NULL;
	}

	node*	firstNode() const
	{
		if (this->tree())
			return this->tree()->m_first;
		return NULL;
	}

	node*	lastNode() const
	{
		if (this->tree())
			return this->tree()->m_last;
		return NULL;
	}

	node*	NIL() const
	{
		if (this->tree())
			return this->tree()->NIL;
		return NULL;
	}

		void	BSTerase(iterator position)
	{
		node*	z = position.node();
		node*	y = z;
		node*	x = NULL;
		enum Colour	origYColour = y->colour;

		if (z->left == this->NIL()) // z has only right child or no children
		{
			x = z->right;
			this->transplant(z, z->right);
		}
		else if (z->right == this->NIL()) // z has only left child
		{
			x = z->left;
			this->transplant(z, z->left);
		}
		else // z has two children
		{
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

		delete z;
		z = NULL;

		if (origYColour == BLACK)
			this->fixEraseViolation(x);
	}

	void	transplant(node* u, node* v)
	{
		if (u == this->root())
			this->tree()->m_root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else if (u == u->parent->right)
			u->parent->right = v;
		v->parent = u->parent;
	}

/*
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
		if (y->left)
			y->left->parent = x;
		y->parent = x->parent;
		if (x == this->root())
			this->tree()->m_root = y;
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
		if (y->right)
			y->right->parent = x;
		y->parent = x->parent;
		if (x == this->root())
			this->tree()->m_root = y;
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

#ifndef MAP_HPP
# define MAP_HPP

# include <cstddef>
# include <memory>
# include "algorithm.hpp"
# include "functional.hpp"
# include "iterator.hpp"
# include "treeIterator.hpp"
# include "treeNode.hpp"
# include "type_traits.hpp"
# include "utility.hpp"

namespace ft
{

template <class Key,											// mapBase::key_type
		class T,												// mapBase::mapped_type
		class Compare = ft::less<Key>,							// mapBase::key_compare
		class Alloc = std::allocator<ft::pair<const Key, T> >	// mapBase::allocator_type
		>
class mapBase
{
public:
	typedef Key														key_type;
	typedef T														mapped_type;
	typedef ft::pair<const key_type, mapped_type>					value_type;
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

	struct value_compare : public ft::binary_function<value_type, value_type, bool>
	{
		friend class mapBase;
	protected:
		Compare	comp;
		value_compare(Compare c): comp(c) {}
	public:
		typedef bool		result_type;
		typedef value_type	first_argument_type;
		typedef value_type	second_argument_type;
		bool operator()(value_type const & x, value_type const & y) const { return comp(x.first, y.first); }
	};

protected:
	RBTree<value_type>*	m_tree;
	size_type			m_size;
	key_compare			m_comp;
	allocator_type		m_alloc;

public:
	// default constructor
	explicit mapBase(key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type()):
	m_tree(new RBTree<value_type>),
	m_size(0),
	m_comp(comp),
	m_alloc(alloc) {
		this->mapInit();
	}

	// copy constructor
	mapBase(mapBase const & other):
	m_tree(new RBTree<value_type>(other.m_tree)),
	m_size(0),
	m_comp(other.key_comp()),
	m_alloc(other.get_allocator()) {
		this->mapInit();
	}

	// destructor
	virtual ~mapBase() { delete this->m_tree; }

	// assignment operator overload
	mapBase&	operator=(mapBase const & rhs)
	{
		if (&rhs != this)
		{
			this->clear();
			this->m_alloc = rhs.get_allocator();
			this->m_comp = rhs.key_comp();
			this->insert(rhs.begin(), rhs.end());
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

	void	swap(mapBase & x)
	{
		ft::swap(this->m_tree, x.m_tree);
		ft::swap(this->m_size, x.m_size);
		ft::swap(this->m_comp, x.m_comp);
		ft::swap(this->m_alloc, x.m_alloc);
	}

	key_compare		key_comp() const { return this->m_comp; }
	value_compare	value_comp() const { return value_compare(this->m_comp); }

	iterator		find(key_type const & k)
	{
		treeNode<value_type>*	node(this->root());
		while (this->validNode(node))
		{
			if (this->equal(node->value->first, k)) return iterator(this->tree(), node);
			else if (this->key_comp()(node->value->first, k)) node = node->right;
			else if (this->key_comp()(k, node->value->first)) node = node->left;
		}
		return this->end();
	}

	const_iterator	find(key_type const & k) const
	{
		treeNode<value_type>*	node(this->root());
		while (this->validNode(node))
		{
			if (this->equal(node->value->first, k)) return const_iterator(this->tree(), node);
			else if (this->key_comp()(node->value->first, k)) node = node->right;
			else if (this->key_comp()(k, node->value->first)) node = node->left;
		}
		return this->end();
	}

	virtual size_type	count(key_type const & k) const = 0;

	iterator		lower_bound(key_type const & k)
	{
		for (iterator it = this->begin(); it != this->end(); ++it)
		{
			if (!this->key_comp()(it->first, k)) return it;
		}
		return this->end();
	}

	const_iterator	lower_bound(key_type const & k) const
	{
		for (const_iterator it = this->begin(); it != this->end(); ++it)
		{
			if (!this->key_comp()(it->first, k)) return it;
		}
		return this->end();
	}

	iterator		upper_bound(key_type const & k)
	{
		for (iterator it = this->begin(); it != this->end(); ++it)
		{
			if (this->key_comp()(k, it->first)) return it;
		}
		return this->end();
	}

	const_iterator	upper_bound(key_type const & k) const
	{
		for (iterator it = this->begin(); it != this->end(); ++it)
		{
			if (this->key_comp()(k, it->first)) return it;
		}
		return this->end();
	}

	ft::pair<iterator, iterator>				equal_range(key_type const & k) {
		return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
	}

	ft::pair<const_iterator, const_iterator>	equal_range(key_type const & k) const {
		return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
	}

	allocator_type	get_allocator() const {
		return this->m_alloc;
	}

protected:
	void mapInit() {
		this->tree()->m_root = this->NIL();
		this->firstNode()->parent = this->lastNode();
	}

	bool	equal(value_type const & x, value_type const & y) const {
		return (!this->value_comp()(x, y) && !this->value_comp()(y, x));
	}

	bool	equal(key_type const & x, key_type const & y) const {
		return (!this->key_comp()(x, y) && !this->key_comp()(y, x));
	}

	bool	validNode(treeNode<value_type>* node) const {
		return (node != NULL && node != this->NIL() && node != this->firstNode() && node != this->lastNode());
	}

	RBTree<value_type>*		tree() const { return this->m_tree; }

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

	treeNode<value_type>*	NIL() const
	{
		if (this->tree())
			return this->tree()->NIL;
		return NULL;
	}

	void	BSTerase(iterator position)
	{
		treeNode<value_type>*	z = position.node();
		treeNode<value_type>*	y = z;
		treeNode<value_type>*	x = NULL;
		enum Colour				origYColour = y->colour;

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
			iterator	temp = position;
			++temp;
			y = temp.node();

			origYColour = y->colour;
			x = y->right;
			if (y->parent == z)
				x->parent = y;
			else
			{
				this->transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			this->transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->colour = z->colour;

			delete z;
			z = NULL;

			if (origYColour == BLACK)
				this->fixEraseViolation(x);
		}
	}

	void	transplant(treeNode<value_type>* u, treeNode<value_type>* v)
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

	void rotateLeft(treeNode<value_type>* x)
	{
		treeNode<value_type>*	y = x->right;

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

	void rotateRight(treeNode<value_type>* x)
	{
		treeNode<value_type>*	y = x->left;

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

	void fixInsertViolation(treeNode<value_type> * z)
	{
		while (z != this->root() && z->colour != BLACK && z->parent->colour == RED)
		{
			// parent is left child of grandparent
			if (z->parent == z->parent->parent->left)
			{
				treeNode<value_type>*	y = z->parent->parent->right;
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
				treeNode<value_type>*	y = z->parent->parent->left;
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

	void	fixEraseViolation(treeNode<value_type>* x)
	{
		while (x != this->root() && x->colour == BLACK)
		{
			if (x == x->parent->left)
			{
				treeNode<value_type>*	w = x->parent->right;
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
				treeNode<value_type>*	w = x->parent->left;
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

template <class Key, class T, class Compare, class Alloc>
bool operator==(mapBase<Key, T, Compare, Alloc> const & lhs, mapBase<Key, T, Compare, Alloc> const & rhs) {
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(mapBase<Key, T, Compare, Alloc> const & lhs, mapBase<Key, T, Compare, Alloc> const & rhs) {
	return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator<(mapBase<Key, T, Compare, Alloc> const & lhs, mapBase<Key, T, Compare, Alloc> const & rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Key, class T, class Compare, class Alloc>
bool operator<=(mapBase<Key, T, Compare, Alloc> const & lhs, mapBase<Key, T, Compare, Alloc> const & rhs) {
	return !(rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>(mapBase<Key, T, Compare, Alloc> const & lhs, mapBase<Key, T, Compare, Alloc> const & rhs) {
	return rhs < lhs;
}

template <class Key, class T, class Compare, class Alloc>
bool operator>=(mapBase<Key, T, Compare, Alloc> const & lhs, mapBase<Key, T, Compare, Alloc> const & rhs) {
	return !(lhs < rhs);
}

template <class Key, class T, class Compare, class Alloc>
void swap(mapBase<Key, T, Compare, Alloc> const & x, mapBase<Key, T, Compare, Alloc> const & y) {
	x.swap(y);
}

template <class Key,											// map::key_type
		class T,												// map::mapped_type
		class Compare = ft::less<Key>,							// map::key_compare
		class Alloc = std::allocator<ft::pair<const Key, T> >	// map::allocator_type
		>
class map : public ft::mapBase<Key, T, Compare, Alloc>
{
public:
	typedef Key														key_type;
	typedef T														mapped_type;
	typedef ft::pair<const key_type, mapped_type>					value_type;
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

private:
	typedef	ft::mapBase<Key, T, Compare, Alloc>						base;

public:
	// 1. empty constructor
	explicit map(key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type()):
		base(comp, alloc) {}

	// 2. range constructor
	template <class Iterator>
	map(Iterator first, Iterator last,
		key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type(),
		typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0):
		base(comp, alloc) {
		this->insert(first, last);
	}

	// 3. copy constructor
	map(map const & other):
		base(other) {
		this->insert(other.begin(), other.end());
	}

	// destructor
	~map() {}

	// assignment operator overload
	map&	operator=(map const & rhs)
	{
		base::operator=(rhs);
		return *this;
	}

	mapped_type&	operator[](key_type const & k) {
		return this->insert(ft::make_pair(k, mapped_type())).first->second;
	}

	// 1. single element insertion
	ft::pair<iterator, bool>	insert(value_type const & val)
	{
		ft::pair<treeNode<value_type>*, bool>	ret = this->BSTinsert(this->root(), val);

		if (ret.second)
		{
			this->fixInsertViolation(ret.first);
			++this->m_size;
		}
		return ft::make_pair(iterator(this->tree(), ret.first), ret.second);
	}

	// 2. insertion with hint
	iterator	insert(iterator position, value_type const & val)
	{
		if (position != this->end() && this->equal(position->first, val.first)) return position;

		ft::pair<treeNode<value_type>*, bool>	ret;

		if (this->empty())
			ret = this->BSTinsert(this->root(), val);
		else if (position == this->end())
		{
			--position;
			if (position->first < val.first)
				ret = this->BSTinsert(position.node(), val);
			else
				ret = this->BSTinsert(this->root(), val);
		}
		else if (position->first < val.first)
		{
			iterator	tmp(position);
			++tmp;
			if (tmp == this->end() || tmp->first > val.first)
				ret = this->BSTinsert(position.node(), val);
			else
				ret = this->BSTinsert(this->root(), val);
		}
		else if (position->first > val.first)
		{
			iterator	tmp(position);
			--tmp;
			if (position == this->begin() || tmp->first < val.first)
				ret = this->BSTinsert(position.node(), val);
			else
				ret = this->BSTinsert(this->root(), val);
		}
		if (ret.second)
		{
			this->fixInsertViolation(ret.first);
			++this->m_size;
		}
		return iterator(this->tree(), ret.first);
	}

	// 3. range insertion
	template <class Iterator>
	void	insert(Iterator first, Iterator last,
			 		typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0)
	{
		while (first != last)
		{
			this->insert(*first);
			++first;
		}
	}

	// 1. erase by iterator
	void	erase(iterator position)
	{
		this->BSTerase(position);

		--this->m_size;
		if (this->empty())
			this->mapInit();
	}

	// 2. erase by key
	size_type	erase(key_type const & k)
	{
		iterator	it = this->find(k);
		if (it == this->end())
			return 0;
		this->erase(it);
		return 1;
	}

	// 3. erase range
	void	erase(iterator first, iterator last)
	{
		while (first != last)
		{
			iterator	tmp(first);
			++first;
			this->erase(tmp);
		}
	}

	void clear() {
		this->erase(this->begin(), this->end());
	}

	size_type	count(key_type const & k) const {
		return this->find(k) != this->end();
	}

private:
	ft::pair<treeNode<value_type>*, bool>	BSTinsert(treeNode<value_type>* curr, value_type const & val)
	{
		treeNode<value_type>*	newNode = new treeNode<value_type>(val);

		if (this->root() == this->NIL())
		{
			this->tree()->m_root = newNode;
			this->firstNode()->parent = this->lastNode()->parent = this->root();
			this->root()->left = this->firstNode();
			this->root()->right = this->lastNode();
			return ft::make_pair(this->root(), true);
		}

		while (curr != this->NIL())
		{
			if (this->validNode(curr) && this->equal(*newNode->value, *curr->value))
			{
				delete newNode;
				break ;
			}
			else if (this->value_comp()(*newNode->value, *curr->value))
			{
				if (curr->left == this->firstNode())
				{
					newNode->parent = curr;
					newNode->left = this->firstNode();
					newNode->right = this->NIL();
					curr->left = newNode;
					this->firstNode()->parent = newNode;
					return ft::make_pair(newNode, true);
				}
				else if (curr->left == this->NIL())
				{
					curr->left = newNode;
					newNode->parent = curr;
					newNode->left = this->NIL();
					newNode->right = this->NIL();
					return ft::make_pair(newNode, true);
				}
				curr = curr->left;
			}
			else if (this->value_comp()(*curr->value, *newNode->value))
			{
				if (curr->right == this->lastNode())
				{
					newNode->parent = curr;
					newNode->right = this->lastNode();
					newNode->left = this->NIL();
					curr->right = newNode;
					this->lastNode()->parent = newNode;
					return ft::make_pair(newNode, true);
				}
				else if (curr->right == this->NIL())
				{
					curr->right = newNode;
					newNode->parent = curr;
					newNode->left = this->NIL();
					newNode->right = this->NIL();
					return ft::make_pair(newNode, true);
				}
				curr = curr->right;
			}
		}
		return ft::make_pair(curr, false);
	}
};

template <class Key,											// multimap::key_type
		class T,												// multimap::mapped_type
		class Compare = ft::less<Key>,							// multimap::key_compare
		class Alloc = std::allocator<ft::pair<const Key, T> >	// multimap::allocator_type
		>
class multimap : public ft::mapBase<Key, T, Compare, Alloc>
{
public:
	typedef Key														key_type;
	typedef T														mapped_type;
	typedef ft::pair<const key_type, mapped_type>					value_type;
	typedef Compare													key_compare;
	typedef Alloc													allocator_type;
	typedef	typename allocator_type::reference						reference;
	typedef	typename allocator_type::const_reference				const_reference;
	typedef	typename allocator_type::pointer						pointer;
	typedef	typename allocator_type::const_pointer					const_pointer;
	typedef ft::treeIterator<value_type>							iterator;
	typedef ft::constTreeIterator<value_type>						const_iterator;
	typedef ft::reverse_iterator<iterator>							reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
	typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
	typedef typename allocator_type::size_type						size_type;

private:
	typedef	ft::mapBase<Key, T, Compare, Alloc>						base;

public:
	// 1. empty constructor
	explicit multimap(key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type()):
		base(comp, alloc) {}

	// 2. range constructor
	template <class Iterator>
	multimap(Iterator first, Iterator last,
		  key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type(),
		  typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0):
		  base(comp, alloc) {
		this->insert(first, last);
	}

	// 3. copy constructor
	multimap(multimap const & other):
		base(other) {
		this->insert(other.begin(), other.end());
	}

	// destructor
	~multimap() {}

	// assignment operator overload
	multimap&	operator=(multimap const & rhs)
	{
		base::operator=(rhs);
		return *this;
	}

	// 1. single element insertion
	iterator	insert(value_type const & val)
	{
		treeNode<value_type>*	ret = this->BSTinsert(this->root(), val);

		this->fixInsertViolation(ret);
		++this->m_size;
		return iterator(this->tree(), ret);
	}

	// 2. insertion with hint
	iterator	insert(iterator position, value_type const & val)
	{
		treeNode<value_type>*	ret;

		if (this->empty())
			ret = this->BSTinsert(this->root(), val);
		else if (position == this->end())
		{
			--position;
			if (position->first < val.first)
				ret = this->BSTinsert(position.node(), val);
			else
				ret = this->BSTinsert(this->root(), val);
		}
		else if (position->first < val.first)
		{
			iterator	tmp(position);
			++tmp;
			if (tmp == this->end() || tmp->first > val.first)
				ret = this->BSTinsert(position.node(), val);
			else
				ret = this->BSTinsert(this->root(), val);
		}
		else if (position->first > val.first)
		{
			iterator	tmp(position);
			--tmp;
			if (position == this->begin() || tmp->first < val.first)
				ret = this->BSTinsert(position.node(), val);
			else
				ret = this->BSTinsert(this->root(), val);
		}
		fixInsertViolation(ret);
		++this->m_size;
		return iterator(this->tree(), ret);
	}

	// 3. range insertion
	template <class Iterator>
	void	insert(Iterator first, Iterator last,
				   typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0)
	{
		while (first != last)
		{
			this->insert(*first);
			++first;
		}
	}

	// 1. erase by iterator
	void erase(iterator position)
	{
		this->BSTerase(position);

		--this->m_size;
		if (this->empty())
			this->mapInit();
	}

	// 2. erase by key
	size_type	erase(key_type const & k)
	{
		iterator	first = this->lower_bound(k);
		iterator	last = this->upper_bound(k);
		size_type	ret = ft::distance(first, last);

		this->erase(first, last);
		return ret;
	}

	// 3. erase range
	void	erase(iterator first, iterator last)
	{
		while (first != last)
		{
			iterator	tmp(first);
			++first;
			this->erase(tmp);
		}
	}

	void clear() {
		this->erase(this->begin(), this->end());
	}

	size_type	count(key_type const & k) const {
		return ft::distance(this->lower_bound(k), this->upper_bound(k));
	}

private:
	treeNode<value_type>*	BSTinsert(treeNode<value_type>* curr, value_type const & val)
	{
		treeNode<value_type>*	newNode = new treeNode<value_type>(val);

		if (this->root() == this->NIL())
		{
			this->tree()->m_root = newNode;
			this->firstNode()->parent = this->lastNode()->parent = this->root();
			this->root()->left = this->firstNode();
			this->root()->right = this->lastNode();
			return this->root();
		}

		while (curr != this->NIL())
		{
			if (this->value_comp()(*newNode->value, *curr->value))
			{
				if (curr->left == this->firstNode())
				{
					newNode->parent = curr;
					newNode->left = this->firstNode();
					newNode->right = this->NIL();
					curr->left = newNode;
					this->firstNode()->parent = newNode;
					return newNode;
				}
				else if (curr->left == this->NIL())
				{
					curr->left = newNode;
					newNode->parent = curr;
					newNode->left = this->NIL();
					newNode->right = this->NIL();
					return newNode;
				}
				curr = curr->left;
			}
			else if (!this->value_comp()(*newNode->value, *curr->value))
			{
				if (curr->right == this->lastNode())
				{
					newNode->parent = curr;
					newNode->right = this->lastNode();
					newNode->left = this->NIL();
					curr->right = newNode;
					this->lastNode()->parent = newNode;
					return newNode;
				}
				else if (curr->right == this->NIL())
				{
					curr->right = newNode;
					newNode->parent = curr;
					newNode->left = this->NIL();
					newNode->right = this->NIL();
					return newNode;
				}
				curr = curr->right;
			}
		}
		return curr;
	}
};

}; //end of namespace ft

#endif

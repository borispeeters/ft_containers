#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include <memory>
# include <utility>
# include "algorithm.hpp"
# include "iterator.hpp"
# include "mapIterator.hpp"
# include "mapNode.hpp"
# include "type_traits.hpp"

namespace ft
{

template <class Key,											// map::key_type
		class T,												// map::mapped_type
		class Compare = std::less<Key>,							// map::key_compare
		class Alloc = std::allocator<std::pair<const Key, T> >	// map::allocator_type
		>
class map
{
public:
	typedef Key														key_type;
	typedef T														mapped_type;
	typedef std::pair<const key_type, mapped_type>					value_type;
	typedef Compare													key_compare;
//	typedef lolwat													value_compare;
	typedef Alloc													allocator_type;
	typedef typename allocator_type::reference						reference;
	typedef typename allocator_type::const_reference				const_reference;
	typedef typename allocator_type::pointer						pointer;
	typedef typename allocator_type::const_pointer					const_pointer;
	typedef ft::mapIterator<value_type>								iterator;
	typedef ft::constMapIterator<value_type>						const_iterator;
	typedef ft::reverse_iterator<iterator>							reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
	typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
	typedef typename allocator_type::size_type						size_type;

	struct value_compare : public std::binary_function<value_type, value_type, bool>
	{
		friend class map;
	protected:
		Compare	comp;
		value_compare(Compare c): comp(c) {}
	public:
		typedef bool		result_type;
		typedef value_type	first_argument_type;
		typedef value_type	second_argument_type;
		bool operator()(value_type const & x, value_type const & y) const { return comp(x.first, y.first); }
	};

private:
	mapNode<value_type>*	m_root;
	mapNode<value_type>*	m_first;
	mapNode<value_type>*	m_last;
	size_type				m_size;
	key_compare				m_comp;
	allocator_type			m_alloc;

public:
	// 1. empty constructor
	explicit map(key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type()):
		m_root(0),
		m_first(0),
		m_last(0),
		m_size(0),
		m_comp(comp),
		m_alloc(alloc)
	{
		this->mapInit();
	}

	// 2. range constructor
	template <class Iterator>
	map(Iterator first, Iterator last,
		key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type(),
		typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0):
		m_root(0),
		m_first(0),
		m_last(0),
		m_size(0),
		m_comp(comp),
		m_alloc(alloc)
	{
		this->mapInit();
		this->insert(first, last);
	}

	// 3. copy constructor
	map(map const & other):
		m_root(0),
		m_first(0),
		m_last(0),
		m_size(0),
		m_comp(other.key_comp()),
		m_alloc(other.get_allocator())
	{
		this->mapInit();
		this->insert(other.begin(), other.end());
	}

	// destructor
	~map()
	{
		delete this->m_first;
		delete this->m_last;
	}

	// assignment operator overload
	map&	operator=(map const & rhs)
	{
		if (&rhs != this)
		{
			this->clear();
			this->insert(rhs.begin(), rhs.end());
		}
		return *this;
	}

	iterator		begin() { return this->firstNode()->parent; }
	const_iterator	begin() const { return this->firstNode()->parent; }
	iterator		end() { return this->lastNode(); }
	const_iterator	end() const { return this->lastNode(); }

	reverse_iterator 		rbegin() { return reverse_iterator(this->end()); }
	const_reverse_iterator	rbegin() const { return reverse_iterator(this->end()); }
	reverse_iterator 		rend() { return reverse_iterator(this->begin()); }
	const_reverse_iterator	rend() const { reverse_iterator(this->begin()); }

	bool 		empty() const { return this->size() == 0; }
	size_type	size() const { return this->m_size; }
	size_type	max_size() const { return this->get_allocator().max_size(); }

	mapped_type&	operator[](key_type const & k) { return this->insert(std::make_pair(k, mapped_type())).first->second; }

	// 1. single element insertion
	std::pair<iterator, bool>	insert(value_type const & val)
	{
		std::pair<mapNode<value_type>*, bool>	ret(this->BSTinsert(this->root(), val));

		if (ret.second)
		{
			fixInsertViolation(ret.first);
			++this->m_size;
		}
		return ret;
	}

	// 2. insertion with hint
	iterator	insert(iterator position, value_type const & val)
	{
		if (position != this->end() && this->equal(position->first, val.first)) return position;

		std::pair<mapNode<value_type>*, bool>	ret;

		if (this->empty())
		{
			ret = this->BSTinsert(this->root(), val);
		}
		else if (position == this->end())
		{
			--position;
			if (val.first >= position->first)
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
			if (tmp->first < val.first)
				ret = this->BSTinsert(position.node(), val);
			else
				ret = this->BSTinsert(this->root(), val);
		}
		if (ret.second)
		{
			fixInsertViolation(ret.first);
			++this->m_size;
		}
		return ret.first;
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

	// 1. erase iterator
	void erase(iterator position)
	{
		std::pair<mapNode<value_type>*, bool>	ret(this->BSTerase(position));

		if (ret.second)
			this->fixEraseViolation(ret.first);

		--this->m_size;
		if (this->empty())
		{
			this->m_root = 0;
			this->firstNode()->parent = this->lastNode();
		}
	}

	// 2. erase key
	size_type	erase(key_type const & k)
	{
		iterator	it = this->find(k);
		if (it == this->end())
			return 0;
		this->erase(it);
		return 1;
	}

	// 3. erase range
	void erase(iterator first, iterator last)
	{
		while (first != last)
		{
			iterator	tmp(first);
			++first;
			this->erase(tmp);
		}
	}

	void swap(map & x)
	{
		ft::swap(this->m_first, x.m_first);
		ft::swap(this->m_last, x.m_last);
		ft::swap(this->m_root, x.m_root);
		ft::swap(this->m_size, x.m_size);
		ft::swap(this->m_comp, x.m_comp);
		ft::swap(this->m_alloc, x.m_alloc);
	}

	void clear() { this->erase(this->begin(), this->end()); }

	key_compare		key_comp() const { return this->m_comp; }
	value_compare	value_comp() const { return value_compare(this->m_comp); }

	iterator		find(key_type const & k)
	{
		mapNode<value_type>*	node(this->root());
		while (node && node != this->firstNode() && node != this->lastNode())
		{
			if (this->equal(node->value->first, k)) return iterator(node);
			else if (this->key_comp()(node->value->first, k)) node = node->right;
			else if (this->key_comp()(k, node->value->first)) node = node->left;
		}
		return this->end();
	}

	const_iterator	find(key_type const & k) const
	{
		mapNode<value_type>*	node(this->root());
		while (this->validNode(node))
		{
			if (this->equal(node->value->first, k)) return const_iterator(node);
			else if (this->key_comp()(node->value->first, k)) node = node->right;
			else if (this->key_comp()(k, node->value->first)) node = node->left;
		}
		return this->end();
	}

	size_type		count(key_type const & k) const { return this->find(k) != this->end(); }

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
		for (iterator it = this->begin(); it != this->end(); ++it)
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

	std::pair<iterator, iterator>				equal_range(key_type const & k) { return std::make_pair(this->lower_bound(k), this->upper_bound(k)); }
	std::pair<const_iterator, const_iterator>	equal_range(key_type const & k) const { return std::make_pair(this->lower_bound(k), this->upper_bound(k)); }

	allocator_type	get_allocator() const { return this->m_alloc; }

	void printBT() const
	{
		this->printBT("", this->root(), false);
		std::cout << std::endl;
	}

private:
	void printBT(std::string const & prefix, mapNode<value_type>* trav, bool isLeft) const
	{
		if (this->validNode(trav))
		{
			std::cout << prefix;
			std::cout << (isLeft ? "├──" : "└──" );
			// print the value of the node
			if (trav->colour == RED)
				std::cout << "\033[1;31m";
			std::cout << trav->value->first << std::endl;
			std::cout << "\033[0m";
			// enter the next tree level - left and right branch
			printBT( prefix + (isLeft ? "│   " : "    "), trav->left, true);
			printBT( prefix + (isLeft ? "│   " : "    "), trav->right, false);
		}
	}
	void mapInit()
	{
		this->m_first = new mapNode<value_type>(BLACK);
		this->m_last = new mapNode<value_type>(BLACK);
		this->firstNode()->parent = this->lastNode();
	}

	std::pair<mapNode<value_type>*, bool>	BSTinsert(mapNode<value_type>* curr, value_type const & val)
	{
		mapNode<value_type>*	newNode = new mapNode<value_type>(val);

		if (this->root() == 0)
		{
			this->m_root = newNode;
			this->root()->left = this->firstNode();
			this->firstNode()->parent = this->root();
			this->root()->right = this->lastNode();
			this->lastNode()->parent = this->root();
			return std::make_pair(this->root(), true);
		}

		while (curr)
		{
			if (curr != firstNode() && curr != lastNode() && this->equal(*newNode->value, *curr->value))
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
					curr->left = newNode;
					this->firstNode()->parent = newNode;
					return std::make_pair(newNode, true);
				}
				else if (curr->left == 0)
				{
					curr->left = newNode;
					newNode->parent = curr;
					return std::make_pair(newNode, true);
				}
				curr = curr->left;
			}
			else if (this->value_comp()(*curr->value, *newNode->value))
			{
				if (curr->right == this->lastNode())
				{
					newNode->parent = curr;
					newNode->right = this->lastNode();
					curr->right = newNode;
					this->lastNode()->parent = newNode;
					return std::make_pair(newNode, true);
				}
				else if (curr->right == 0)
				{
					curr->right = newNode;
					newNode->parent = curr;
					return std::make_pair(newNode, true);
				}
				curr = curr->right;
			}
		}
		return std::make_pair(curr, false);
	}

	bool 	BSTerase(iterator position)
	{
		mapNode<value_type>*	z(position.node());
		mapNode<value_type>*	y(z);
		mapNode<value_type>*	x(0);
		enum Colour				origYColour(y->colour);

		if (!this->validNode(z->left)) // z has only right child or no children
		{
			x = z->right;
			this->transplant(z, z->right);
		}
		else if (!this->validNode(z->right)) // z has only left child
		{
			x = z->left;
			this->transplant(z, z->left);
		}
		else // z has two children
		{
			++position;
			y = position.node();

			origYColour = y->colour;
			x = y->right;
			if (y->parent == z && x) // y is direct child of z
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
		}
		return std::make_pair(x, origYColour == BLACK);
	}

	void	transplant(mapNode<value_type>* u, mapNode<value_type>* v)
	{
		if (u == this->root())
			this->m_root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else if (u == u->parent->right)
			u->parent->right = v;
		if (v) v->parent = u->parent;
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

	void rotateLeft(mapNode<value_type>*& x)
	{
		mapNode<value_type>*	y(x->right);

		x->right = y->left;
		if (y->left)
			y->left->parent = x;
		y->parent = x->parent;
		if (x == this->root())
			this->m_root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else if (x == x->parent->right)
			x->parent->right = y;
		y->left = x;
		x->parent = y;
	}

	void rotateRight(mapNode<value_type>*& x)
	{
		mapNode<value_type>*	y(x->left);

		x->left = y->right;
		if (y->right)
			y->right->parent = x;
		y->parent = x->parent;
		if (x == this->root())
			this->m_root = y;
		else if (x == x->parent->right)
			x->parent->right = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		y->right = x;
		x->parent = y;
	}

	void recolour(mapNode<value_type>* node)
	{
		if (node->colour == BLACK) node->colour = RED;
		else if (node->colour == RED) node->colour = BLACK;
	}

	void fixInsertViolation(mapNode<value_type> *& node)
	{
		mapNode<value_type>*	parent(0);
		mapNode<value_type>*	grandParent(0);
		mapNode<value_type>*	uncle(0);

		while (node != this->root() && node->colour != BLACK && node->parent->colour == RED)
		{
			parent = node->parent;
			grandParent = parent->parent;
			// parent is left child of grandparent
			if (parent == grandParent->left)
			{
				uncle = grandParent->right;
				if (uncle && uncle->colour == RED)
				{
					this->recolour(grandParent);
					this->recolour(parent);
					this->recolour(uncle);
					node = grandParent;
				}
				else
				{
					// node is right child of parent, rotate left
					if (node == parent->right)
					{
						node = parent;
						parent = node;
						rotateLeft(node);
					}
					// node is left child of parent, swap parent and grandparent colour and rotate right
					ft::swap(parent->colour, grandParent->colour);
					rotateRight(grandParent);
				}
			}
			// parent is right child of grandparent
			else if (parent == grandParent->right)
			{
				uncle = grandParent->left;
				if (uncle && uncle->colour == RED)
				{
					this->recolour(grandParent);
					this->recolour(parent);
					this->recolour(uncle);
					node = grandParent;
				}
				else
				{
					// node is left child of parent, rotate right
					if (node == parent->left)
					{
						node = parent;
						parent = node;
						rotateRight(node);
					}
					// node is right child of parent, swap parent and grandparent colour and rotate left
					rotateLeft(grandParent);
					ft::swap(parent->colour, grandParent->colour);
				}
			}
		}
		this->root()->colour = BLACK;
	}

	void	fixEraseViolation(mapNode<value_type> *& x)
	{
		while (x != this->root() && x->colour == BLACK)
		{
			if (x == x->parent->left)
			{
				mapNode<value_type>*	w(x->parent->right);
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
				mapNode<value_type>*	w(x->parent->left);
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

	bool	equal(value_type const & x, value_type const & y) const {
		return (!this->value_comp()(x, y) && !this->value_comp()(y, x));
	}
	bool	equal(key_type const & x, key_type const & y) const {
		return (!this->key_comp()(x, y) && !this->key_comp()(y, x));
	}
	bool	validNode(mapNode<value_type>* node) const {
		return (node != 0 && node != this->firstNode() && node != this->lastNode());
	}

	mapNode<value_type>*	root() const { return this->m_root; }
	mapNode<value_type>*	firstNode() const { return this->m_first; }
	mapNode<value_type>*	lastNode() const { return this->m_last; }

};

template <class Key, class T, class Compare, class Alloc>
bool operator==(map<Key, T, Compare, Alloc> const & lhs, map<Key, T, Compare, Alloc> const & rhs)
{ return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }

template <class Key, class T, class Compare, class Alloc>
bool operator!=(map<Key, T, Compare, Alloc> const & lhs, map<Key, T, Compare, Alloc> const & rhs) { return !(lhs == rhs); }

template <class Key, class T, class Compare, class Alloc>
bool operator<(map<Key, T, Compare, Alloc> const & lhs, map<Key, T, Compare, Alloc> const & rhs)
{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

template <class Key, class T, class Compare, class Alloc>
bool operator<=(map<Key, T, Compare, Alloc> const & lhs, map<Key, T, Compare, Alloc> const & rhs) { return !(rhs < lhs); }

template <class Key, class T, class Compare, class Alloc>
bool operator>(map<Key, T, Compare, Alloc> const & lhs, map<Key, T, Compare, Alloc> const & rhs) { return rhs < lhs; }

template <class Key, class T, class Compare, class Alloc>
bool operator>=(map<Key, T, Compare, Alloc> const & lhs, map<Key, T, Compare, Alloc> const & rhs) { return !(lhs < rhs); }


template <class Key, class T, class Compare, class Alloc>
void swap(map<Key, T, Compare, Alloc> const & x, map<Key, T, Compare, Alloc> const & y) { x.swap(y); }

}; //end of namespace ft

#endif

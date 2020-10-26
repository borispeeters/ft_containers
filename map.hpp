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


# include <iostream>

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
	map&	operator=(map const & other)
	{
		if (&other != this)
		{
			this->erase(this->begin(), this->end());
			this->insert(other.begin(), other.end());
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
	std::pair<iterator, bool> insert(value_type const & val)
	{
		std::pair<mapNode<value_type>*, bool>	ret = this->BSTInsert(this->root(), val);

		if (ret.second)
		{
//			fixViolation(this->m_root, ret.first);
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
			ret = this->BSTInsert(this->root(), val);
		}
		else if (position == this->end())
		{
			--position;
			if (val.first >= position->first)
				ret = this->BSTInsert(position.node(), val);
			else
				ret = this->BSTInsert(this->root(), val);
		}
		else if (position->first < val.first)
		{
			iterator	tmp(position);
			++tmp;
			if (tmp == this->end() || tmp->first > val.first)
				ret = this->BSTInsert(position.node(), val);
			else
				ret = this->BSTInsert(this->root(), val);
		}
		else if (position->first > val.first)
		{
			iterator	tmp(position);
			--tmp;
			if (tmp->first < val.first)
				ret = this->BSTInsert(position.node(), val);
			else
				ret = this->BSTInsert(this->root(), val);
		}
		if (ret.second)
		{
//			fixViolation(this->m_root, ret.first);
			++this->m_size;
		}
		return ret.first;
	}

	// 3. range insertion
	template <class Iterator>
	void		insert(Iterator first, Iterator last,
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
		mapNode<value_type>*	node(position.node());

		if (!this->validNode(node->left) && !this->validNode(node->right)) this->erase_no_children(node);
		else if (this->validNode(node->left) && this->validNode(node->right))
		{
			mapNode<value_type>*	successor((++position).node());
			std::cout << "BEFORE" << std::endl;
			std::cout << "node: " << node->value->first << ", successor: " << successor->value->first << std::endl;

			ft::swap(node->value, successor->value);
			std::cout << std::endl;

			std::cout << "AFTER" << std::endl;
			std::cout << "node: " << node->value->first << ", successor: " << successor->value->first << std::endl;
			if ((successor->left == 0 || successor->left == this->firstNode()) &&
				(successor->right == 0 || successor->right == this->lastNode()))
				this->erase_no_children(successor);
			else this->erase_one_child(node);
		}
		else this->erase_one_child(node);

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
		while (node && node != this->firstNode() && node != this->lastNode())
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

	void printBT() const {
		this->printBT("", this->root(), false);
		std::cout << std::endl;
	}
private:
	void printBT(const std::string& prefix, mapNode<value_type>* trav, bool isLeft) const {
		if (trav && trav != this->firstNode() && trav != this->lastNode()) {
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

	std::pair<mapNode<value_type>*, bool>	BSTInsert(mapNode<value_type>* curr, value_type const & val)
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

	void erase_no_children(mapNode<value_type> *& node)
	{
		if (node != this->root())
		{
			if (node == node->parent->right)
			{
				if (node == this->lastNode()->parent)
				{
					node->parent->right = this->lastNode();
					this->lastNode()->parent = node->parent;
				}
				else node->parent->right = 0;
			}
			else if (node == node->parent->left)
			{
				if (node == this->firstNode()->parent)
				{
					node->parent->left = this->firstNode();
					this->firstNode()->parent = node->parent;
				}
				else node->parent->left = 0;
			}
		}
		else this->firstNode()->parent = this->lastNode();

		delete node;
		node = 0;
	}

	void erase_one_child(mapNode<value_type> *& node)
	{
		mapNode<value_type>*	child;
		if (node->left && node->left != this->firstNode())
			child = node->left;
		else if (node->right && node->right != this->lastNode())
			child = node->right;
		if (node == this->root())
		{
			this->m_root = child;
			if (child == node->left)
			{
				this->lastNode()->parent = this->root();
				this->root()->right = this->lastNode();
			}
			else if (child == node->right)
			{
				this->root()->left = this->firstNode();
				this->firstNode()->parent = this->root();
			}
		}
		else if (node == node->parent->left)
		{
			if (node->left == this->firstNode())
			{
				child->left = this->firstNode();
				this->firstNode()->parent = child;
			}
			node->parent->left = child;
		}
		else if (node == node->parent->right)
		{
			if (node->right == this->lastNode())
			{
				child->right = this->lastNode();
				this->lastNode()->parent = child;
			}
			node->parent->right = child;
		}
		child->parent = node->parent;
		delete node;
		node = 0;
	}

	void rotateLeft(mapNode<value_type>*& root, mapNode<value_type>*& node)
	{
		mapNode<value_type>*	tmp(node->right);

		node->right = tmp->left;
		if (node->right)
			node->right->parent = node;
		tmp->parent = node->parent;
		if (!node->parent)
			root = tmp;
		else if (node == node->parent->left)
			node->parent->left = tmp;
		else
			node->parent->right = tmp;
		tmp->left = node;
		node->parent = tmp;
	}

	void rotateRight(mapNode<value_type>*& root, mapNode<value_type>*& node)
	{
		mapNode<value_type>*	tmp(node->left);

		node->left = tmp->right;
		if (node->left)
			node->left->parent = node;
		tmp->parent = node->parent;
		if (!node->parent)
			root = tmp;
		else if (node == node->parent->right)
			node->parent->right = tmp;
		else
			node->parent->left = tmp;
		tmp->right = node;
		node->parent = tmp;
	}

	void fixViolation(mapNode<value_type>*& root, mapNode<value_type>*& node)
	{
		mapNode<value_type>*	parent(0);
		mapNode<value_type>*	grandParent(0);
		mapNode<value_type>*	uncle(0);

		while (node != root && node->colour != BLACK && node->parent->colour == RED)
		{
			parent = node->parent;
			grandParent = parent->parent;

			// Case A
			// Parent is left child of GrandParent
			if (parent == grandParent->left)
			{
				uncle = grandParent->right;
				// Case 1: uncle is red, recolour
				if (uncle && uncle->colour == RED)
				{
					grandParent->colour = RED;
					parent->colour = BLACK;
					uncle->colour = BLACK;
					node = grandParent;
				}
				else
				{
					// Case 2: node is right child of Parent, left-rotation required
					if (node == parent->right)
					{
						rotateLeft(root, parent);
						node = parent;
						parent = node->parent;
					}
					// Case 3: node is left child of Parent, right-rotation required
					rotateRight(root, grandParent);
					ft::swap(parent->colour, grandParent->colour);
					node = parent;
				}
			}
			// Case B
			// Parent is right child of grandParent
			else if (parent == grandParent->right)
			{
				uncle = grandParent->left;
				// Case 1: uncle is red, recolour
				if (uncle && uncle->colour == RED)
				{
					grandParent->colour = RED;
					parent->colour = BLACK;
					uncle->colour = BLACK;
					node = grandParent;
				}
				else
				{
					// Case 2: node is left child of Parent, right-rotation required
					if (node == parent->left)
					{
						rotateRight(root, parent);
						node = parent;
						parent = node->parent;
					}
					// Case 3: node is right child of Parent, left-rotation required
					rotateLeft(root, grandParent);
					ft::swap(parent->colour, grandParent->colour);
					node = parent;
				}
			}
		}
		root->colour = BLACK;
	}

	mapNode<value_type>*	findNode(iterator position)
	{
		mapNode<value_type>*	node(this->root());
		while (node && node != this->firstNode() && node != this->lastNode())
		{
			if (this->key_comp()(position->first, node->value->first)) node = node->left;
			else if (this->key_comp()(node->value->first, position->first)) node = node->right;
			else return (node);
		}
		return this->lastNode();
	}

	bool	equal(value_type const & x, value_type const & y) const { return (!this->value_comp()(x, y) && !this->value_comp()(y, x)); }
	bool	equal(key_type const & x, key_type const & y) const { return (!this->key_comp()(x, y) && !this->key_comp()(y, x)); }
	bool	validNode(mapNode<value_type>* node) { return (node != 0 && node != this->firstNode() && node != this->lastNode()); }

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

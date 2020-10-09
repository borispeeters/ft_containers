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
	typedef Key												key_type;
	typedef T												mapped_type;
	typedef std::pair<const key_type, mapped_type>			value_type;
	typedef Compare											key_compare;
//	typedef lolwat											value_compare;
	typedef Alloc											allocator_type;
	typedef typename allocator_type::reference				reference;
	typedef typename allocator_type::const_reference		const_reference;
	typedef typename allocator_type::pointer				pointer;
	typedef typename allocator_type::const_pointer			const_pointer;
	typedef ft::mapIterator<value_type>						iterator;
	typedef ft::mapIterator<const value_type>				const_iterator;
//	typedef std::reverse_iterator<iterator>					reverse_iterator;
//	typedef std::reverse_iterator<const_iterator>			const_reverse_iterator;
//	typedef ft::iterator_traits<iterator>::difference_type	difference_type;
	typedef typename allocator_type::size_type				size_type;



private:
	mapNode<value_type>*	m_root;
	mapNode<value_type>*	m_first;
	mapNode<value_type>*	m_last;
	size_type				m_size;
	allocator_type			m_alloc;

public:
	// 1. empty constructor
	explicit map(key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type()):
		m_root(0),
		m_first(0),
		m_last(0),
		m_size(0),
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
		m_alloc(alloc)
	{
		this->mapInit();
	}

	// 3. copy constructor
	map(map const & other):
		m_root(0),
		m_first(0),
		m_last(0),
		m_size(0),
		m_alloc(other.get_allocator())
	{
		this->mapInit();
	}

	// destructor
	~map() {}

	// assignment operator overload
	map&	operator=(map const & other)
	{
		if (&other != this)
		{

		}
		return *this;
	}

	iterator		begin() { return this->firstNode()->parent; }
	const_iterator	begin() const { return this->firstNode()->parent; }
	iterator		end() { return this->lastNode(); }
	const_iterator	end() const { return this->lastNode(); }
//
//	reverse_iterator 		rbegin();
//	const_reverse_iterator	rbegin() const;
//	reverse_iterator 		rend();
//	const_reverse_iterator	rend() const;

	bool 		empty() const { return this->size() == 0; }
	size_type	size() const { return this->m_size; }
	size_type	max_size() const { return this->get_allocator().max_size(); }

	mapped_type&	operator[](key_type const & k)
	{
		mapNode<value_type>*	node;
		node = this->search(this->m_root, k);
		if (node)
		{
			return node->value->second;
		}
		this->insert(std::make_pair(k, mapped_type()));
		return this->search(this->m_root, k)->value->second;
	}

	void insert(value_type const & val)
	{
		mapNode<value_type>*	node = new mapNode<value_type>(val);

		node = BSTInsert(node);

		fixViolation(this->m_root, node);

		++this->m_size;
	}

//	// 1. single element insertion
//	std::pair<iterator, bool>	insert(value_type const & val)
//	{
//		mapNode<value_type>*	node = new mapNode<value_type>(val);
//
//		this->m_root = BSTInsert(this->m_root, node);
//
//		fixViolation(this->m_root, node);
//	}
//
//	// 2. insertion with hint
//	iterator	insert(iterator position, value_type const & val);
//
//	// 3. range insertion
//	template <class Iterator>
//	void		insert(Iterator first, Iterator last,
//					   typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0);


//	// 1. erase iterator
//	void erase(iterator position);
//
//	// 2. erase key
//	size_type	erase(key_type const & k);
//
//	// 3. erase range
//	void erase(iterator first, iterator, last);

	void swap(map & x)
	{
		map	tmp(x);
		x = *this;
		*this = tmp;
	}

	void clear();

//	key_compare		key_comp() const;
//	value_compare	value_comp() const;
//
//	iterator		find(key_type const & k);
//	const_iterator	find(key_type const & k);
//
//	size_type	count(key_type const & k) const;
//
//	iterator		lower_bound(key_type const & k);
//	const_iterator	lower_bound(key_type const & k) const;
//
//	iterator		upper_bound(key_type const & k);
//	const_iterator	upper_bound(key_type const & k) const;

//	std::pair<iterator, iterator>				equal_range(key_type const & k);
//	std::pair<const_iterator, const_iterator>	equal_range(key_type const & k) const;

	allocator_type	get_allocator() const { return this->m_alloc; }

private:
	void mapInit()
	{
		this->m_root = new mapNode<value_type>(BLACK);
		this->m_first = new mapNode<value_type>(BLACK);
		this->m_last = new mapNode<value_type>(BLACK);
		this->firstNode()->parent = this->lastNode();
//		this->lastNode()->left = this->firstNode();
	}

	mapNode<value_type>*	BSTInsert(mapNode<value_type>* newNode)
	{

		if (this->root() == 0)
		{
			this->m_root = newNode;
			this->root()->left = this->firstNode();
			this->firstNode()->parent = this->root();
			this->root()->right = this->lastNode();
			this->lastNode()->parent = this->root();
			return this->root();
		}

		mapNode<value_type>*	curr(this->root());
		while (curr)
		{
			if (newNode->value->first == curr->value->first)
			{
				delete newNode;
				return curr;
			}
			else if (newNode->value->first < curr->value->first)
			{
				if (curr->left == firstNode())
				{
					newNode->parent = curr;
					newNode->left = firstNode();
					curr->left = newNode;
					firstNode()->parent = newNode;
					return newNode;
				}
				else if (curr->left == 0)
				{
					curr->left = newNode;
					newNode->parent = curr;
					return newNode;
				}
				curr = curr->left;
			}
			else if (newNode->value->first > curr->value->first)
			{
				if (curr->right == lastNode())
				{
					newNode->parent = curr;
					newNode->right = lastNode();
					curr->right = newNode;
					lastNode()->parent = newNode;
					return newNode;
				}
				else if (curr->right == 0)
				{
					curr->right = newNode;
					newNode->parent = curr;
					return newNode;
				}
				curr = curr->right;
			}
		}
		return 0;
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

	mapNode<value_type>*	search(mapNode<value_type>* root, key_type const & key)
	{
		if (!root || key == root->value->first)
			return root;
		if (key > root->value->first)
			return search(root->right, key);
		return search(root->left, key);
	}

	mapNode<value_type>*	root() const { return this->m_root; }
	mapNode<value_type>*	firstNode() const { return this->m_first; }
	mapNode<value_type>*	lastNode() const { return this->m_last; }

};

}; //end of namespace ft

#endif

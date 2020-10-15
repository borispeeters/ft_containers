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

	// yoinked from the cplusplus site
	struct value_compare : public std::binary_function<value_type, value_type, bool>
	{
		friend class map;
	protected:
		Compare	comp;
		value_compare (Compare c) : comp(c) {}
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

	mapped_type&	operator[](key_type const & k) { return this->insert(std::make_pair(k, mapped_type())).first->second; }

	// 1. single element insertion
	std::pair<iterator, bool> insert(value_type const & val)
	{
		mapNode<value_type>*	newNode = new mapNode<value_type>(val);

		std::pair<mapNode<value_type>*, bool>	ret = this->BSTInsert(this->root(), newNode);

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
//		if (position->first == val.first)
//			return position;
//		mapNode<value_type>*	newNode = new mapNode<value_type>(val);
//		std::pair<mapNode<value_type>*, bool>	ret;
//		if (position == this->begin())
//		{
//			if ()
//		}
//		else if (position == this->end())
//		{
//			asd;
//		}
//		else if (position->first < val.first)
//		{
//			iterator	tmp(position);
//			++tmp;
//			std::cout << "bruh" << std::endl;
//			if (tmp->first > val.first)
//				ret = this->BSTInsert(position.node(), newNode);
//		}
//		else if (position->first > val.first)
//		{
//			iterator	tmp(position);
//			--tmp;
//			if (tmp->first < val.first)
//				ret = this->BSTInsert(position.node(), newNode);
//		}

//		if (ret.second)
//		{
//			++this->m_size;
//		}
//		return ret.first;
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

		if ((node->left == 0 || node->left == this->firstNode()) &&
				(node->right == 0 || node->right == this->lastNode()))
			this->erase_no_children(node);
		else if (node->left && node->right)
		{
			mapNode<value_type>*	successor((++position).node());
			*node->value = *successor->value;
			if ((successor->left == 0 || successor->left == this->firstNode()) &&
				(successor->right == 0 || successor->right == this->lastNode()))
				this->erase_no_children(successor);
			else
				this->erase_one_child(node);
		}
		else
			this->erase_one_child(node);

		--this->m_size;
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
		map	tmp(x);
		x = *this;
		*this = tmp;
	}

	void clear() { this->erase(this->begin(), this->end()); }

	key_compare		key_comp() const { return this->m_comp; }
	value_compare	value_comp() const { return this->value_comp(this->m_comp); }

	iterator		find(key_type const & k)
	{
		for (iterator it = this->begin(); it != this->end(); ++it)
		{
			if (it->first == k)
				return it;
		}
		return this->end();
	}

	const_iterator	find(key_type const & k) const
	{
		for (iterator it = this->begin(); it != this->end(); ++it)
		{
			if (it->first == k)
				return it;
		}
		return this->end();
	}

	size_type		count(key_type const & k) const
	{
		for (iterator it = this->begin(); it != this->end(); ++it)
		{
			if (it->first == k)
				return 1;
		}
		return 0;
	}

	iterator		lower_bound(key_type const & k)
	{
		for (iterator it = this->begin(); it != this->end(); ++it)
		{
			if (!this->key_comp()(it->first, k))
				return it;
		}
		return this->end();
	}

	const_iterator	lower_bound(key_type const & k) const
	{
		for (iterator it = this->begin(); it != this->end(); ++it)
		{
			if (!this->key_comp()(it->first, k))
				return it;
		}
		return this->end();
	}

	iterator		upper_bound(key_type const & k)
	{
		for (iterator it = this->begin(); it != this->end(); ++it)
		{
			if (this->key_comp()(it->first, k))
				return it;
		}
		return this->end();
	}

	const_iterator	upper_bound(key_type const & k) const
	{
		for (iterator it = this->begin(); it != this->end(); ++it)
		{
			if (this->key_comp()(it->first, k))
				return it;
		}
		return this->end();
	}

	std::pair<iterator, iterator>				equal_range(key_type const & k) { return std::make_pair(this->lower_bound(k), this->upper_bound(k)); }
	std::pair<const_iterator, const_iterator>	equal_range(key_type const & k) const { return std::make_pair(this->lower_bound(k), this->upper_bound(k)); }

	allocator_type	get_allocator() const { return this->m_alloc; }

private:
	void mapInit()
	{
		this->m_first = new mapNode<value_type>(BLACK);
		this->m_last = new mapNode<value_type>(BLACK);
		this->firstNode()->parent = this->lastNode();
	}

	std::pair<mapNode<value_type>*, bool>	BSTInsert(mapNode<value_type>* curr, mapNode<value_type>* newNode)
	{
		if (this->root() == 0)
		{
			this->m_root = newNode;
			this->root()->left = this->firstNode();
			this->firstNode()->parent = this->root();
			this->root()->right = this->lastNode();
			this->lastNode()->parent = this->root();
			std::cout << "root inserted" << std::endl;
			return std::make_pair(this->root(), true);
		}

		while (curr)
		{
			if (curr != firstNode() && curr != lastNode() && newNode->value->first == curr->value->first)
			{
				delete newNode;
				std::cout << "element already existed" << std::endl;
				return std::make_pair(curr, false);
			}
			else if (newNode->value->first < curr->value->first)
			{
				if (curr->left == this->firstNode() || curr == this->firstNode())
				{
					newNode->parent = curr;
					newNode->left = this->firstNode();
					curr->left = newNode;
					this->firstNode()->parent = newNode;
					std::cout << "element inserted at the begin" << std::endl;
					return std::make_pair(newNode, true);
				}
				else if (curr->left == 0)
				{
					curr->left = newNode;
					newNode->parent = curr;
					std::cout << "element inserted to the left" << std::endl;
					return std::make_pair(newNode, true);
				}
				curr = curr->left;
			}
			else if (newNode->value->first > curr->value->first)
			{
				if (curr->right == this->lastNode() || curr == this->lastNode())
				{
					newNode->parent = curr;
					newNode->right = this->lastNode();
					curr->right = newNode;
					this->lastNode()->parent = newNode;
					std::cout << "element inserted at the end" << std::endl;
					return std::make_pair(newNode, true);
				}
				else if (curr->right == 0)
				{
					curr->right = newNode;
					newNode->parent = curr;
					std::cout << "element inserted to the right" << std::endl;
					return std::make_pair(newNode, true);
				}
				curr = curr->right;
			}
		}
		std::cout << "LOLOL THIS WILL NEVER PRINT LOLOLOL AT LEAST I HOPE SO LOL" << std::endl;
		return std::pair<mapNode<value_type>*, bool>(0, false);
	}

	void erase_no_children(mapNode<value_type> *& node)
	{
		if (node != this->root())
		{
			if (node == node->parent->right)
				node->parent->right = 0;
			else if (node == node->parent->left)
				node->parent->left = 0;
		}
		delete node;
		node = 0;
	}
	void erase_one_child(mapNode<value_type> *& node)
	{
		mapNode<value_type>*	child;
		child = (node->left) ? node->left : node->right;
		if (node == this->root())
			this->m_root = child;
		else if (node == node->parent->left)
			node->parent->left = child;
		else if (node == node->parent->right)
			node->parent->right = child;
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

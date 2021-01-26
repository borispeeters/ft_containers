#ifndef _FT_MAP_HPP
# define _FT_MAP_HPP

# define _FT_TREE

# include <cstddef>
# include "_ftl/_tree.hpp"
# include "_ftl/_treeBase.hpp"
# include "_ftl/_treeIterator.hpp"
# include "algorithm.hpp"
# include "functional.hpp"
# include "iterator.hpp"
# include "memory.hpp"
# include "type_traits.hpp"
# include "utility.hpp"

namespace ft
{

template <class Key,											// mapBase::key_type
		class T,												// mapBase::mapped_type
		class Compare = ft::less<Key>,							// mapBase::key_compare
		class Alloc = ft::allocator<ft::pair<const Key, T> >	// mapBase::allocator_type
		>
class mapBase : public ft::treeBase<Key, T, ft::pair<const Key, T>, Compare, Alloc>
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
	typedef std::ptrdiff_t											difference_type;
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
	typedef ft::treeBase<Key, T, ft::pair<const Key, T>, Compare, Alloc>	base;
	typedef typename base::node												node;

public:
	// default constructor
	explicit mapBase(key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type()):
	base(comp, alloc) {}

	// copy constructor
	mapBase(mapBase const & other):
	base(other) {}

	// destructor
	virtual ~mapBase() {}

	// assignment operator overload
	mapBase&	operator=(mapBase const & rhs)
	{
		base::operator=(rhs);
		return *this;
	}

	key_compare		key_comp() const { return this->m_comp; }
	value_compare	value_comp() const { return value_compare(this->m_comp); }

	iterator		find(key_type const & k)
	{
		node*	node(this->root());
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
		node*	node(this->root());
		while (this->validNode(node))
		{
			if (this->equal(node->value->first, k)) return const_iterator(this->tree(), node);
			else if (this->key_comp()(node->value->first, k)) node = node->right;
			else if (this->key_comp()(k, node->value->first)) node = node->left;
		}
		return this->end();
	}

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

protected:
	bool	equal(value_type const & x, value_type const & y) const {
		return (!this->value_comp()(x, y) && !this->value_comp()(y, x));
	}

	bool	equal(key_type const & x, key_type const & y) const {
		return (!this->key_comp()(x, y) && !this->key_comp()(y, x));
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
		class Alloc = ft::allocator<ft::pair<const Key, T> >	// map::allocator_type
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
	typedef std::ptrdiff_t											difference_type;
	typedef typename allocator_type::size_type						size_type;

private:
	typedef	ft::mapBase<Key, T, Compare, Alloc>						base;
	typedef typename base::node										node;

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
	~map() {
		this->clear();
	}

	// assignment operator overload
	map&	operator=(map const & rhs)
	{
		if (&rhs != this)
		{
			this->clear();
			base::operator=(rhs);
			this->insert(rhs.begin(), rhs.end());
		}
		return *this;
	}

	mapped_type&	operator[](key_type const & k) {
		return this->insert(ft::make_pair(k, mapped_type())).first->second;
	}

	// 1. single element insertion
	ft::pair<iterator, bool>	insert(value_type const & val)
	{
		ft::pair<node*, bool>	ret = this->BSTinsert(this->root(), val);

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

		ft::pair<node*, bool>	ret;

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
			this->treeInit();
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
	ft::pair<node*, bool>	BSTinsert(node* curr, value_type const & val)
	{
		node*	newNode = new node(val);

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
		class Alloc = ft::allocator<ft::pair<const Key, T> >	// multimap::allocator_type
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
	typedef std::ptrdiff_t											difference_type;
	typedef typename allocator_type::size_type						size_type;

private:
	typedef	ft::mapBase<Key, T, Compare, Alloc>						base;
	typedef typename base::node										node;

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
	~multimap() {
		this->clear();
	}

	// assignment operator overload
	multimap&	operator=(multimap const & rhs)
	{
		this->clear();
		base::operator=(rhs);
		this->insert(rhs.begin(), rhs.end());
		return *this;
	}

	// 1. single element insertion
	iterator	insert(value_type const & val)
	{
		node*	ret = this->BSTinsert(this->root(), val);

		this->fixInsertViolation(ret);
		++this->m_size;
		return iterator(this->tree(), ret);
	}

	// 2. insertion with hint
	iterator	insert(iterator position, value_type const & val)
	{
		node*	ret;

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
			this->treeInit();
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
	node*	BSTinsert(node* curr, value_type const & val)
	{
		node*	newNode = new node(val);

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

} //end of namespace ft

#endif

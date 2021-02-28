#ifndef _FT_SET_HPP
# define _FT_SET_HPP

# define _FT_TREE

# include <cstddef>
# include "../src/_treeIterator.hpp"
# include "../src/_tree.hpp"
# include "../src/_treeBase.hpp"
# include "algorithm.hpp"
# include "functional.hpp"
# include "iterator.hpp"
# include "memory.hpp"
# include "type_traits.hpp"
# include "utility.hpp"

namespace ft
{

template <class T,		// setBase::key_type/value_type
		class Compare,	// setBase::key_compare/value_compare
		class Alloc		// setBase::allocator_type
        >
class setBase : public ft::treeBase<T, T, T, Compare, Alloc>
{
	typedef typename Alloc::template rebind<treeNode<T> >::other	node_allocator;

public:
	typedef T														key_type;
	typedef T														value_type;
	typedef Compare													key_compare;
	typedef Compare													value_compare;
	typedef Alloc													allocator_type;
	typedef typename allocator_type::reference						reference;
	typedef typename allocator_type::const_reference				const_reference;
	typedef typename allocator_type::pointer						pointer;
	typedef typename allocator_type::const_pointer					const_pointer;
	typedef ft::treeIterator<value_type, node_allocator>			iterator;
	typedef ft::constTreeIterator<value_type, node_allocator>		const_iterator;
	typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	typedef std::ptrdiff_t											difference_type;
	typedef typename allocator_type::size_type						size_type;

protected:
	typedef ft::treeBase<T, T, T, Compare, Alloc>					base;
	typedef typename base::node										node;

public:
	// default constructor
	explicit setBase(key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type()):
	base(comp, alloc) {}

	// copy constructor
	setBase(setBase const & other):
	base(other) {}

	// destructor
	virtual ~setBase() {}

	// assignment operator overload
	setBase&	operator=(setBase const & rhs)
	{
		base::operator=(rhs);
		return *this;
	}

	key_compare		key_comp() const { return this->m_comp; }
	value_compare	value_comp() const { return this->m_comp; }

	iterator		find(key_type const & k)
	{
		node*	node(this->root());
		while (this->validNode(node))
		{
			if (this->equal(node->value, k)) return iterator(this->m_tree, node);
			else if (this->key_comp()(node->value, k)) node = node->right;
			else if (this->key_comp()(k, node->value)) node = node->left;
		}
		return this->end();
	}

	const_iterator		find(key_type const & k) const
	{
		node*	node(this->root());
		while (this->validNode(node))
		{
			if (this->equal(node->value, k)) return const_iterator(this->m_tree, node);
			else if (this->key_comp()(node->value, k)) node = node->right;
			else if (this->key_comp()(k, node->value)) node = node->left;
		}
		return this->end();
	}

	iterator		lower_bound(key_type const & k)
	{
		for (iterator it = this->begin(); it != this->end(); ++it)
		{
			if (!this->key_comp()(*it, k)) return it;
		}
		return this->end();
	}

	const_iterator	lower_bound(key_type const & k) const
	{
		for (const_iterator it = this->begin(); it != this->end(); ++it)
		{
			if (!this->key_comp()(*it, k)) return it;
		}
		return this->end();
	}

	iterator		upper_bound(key_type const & k)
	{
		for (iterator it = this->begin(); it != this->end(); ++it)
		{
			if (this->key_comp()(k, *it)) return it;
		}
		return this->end();
	}

	const_iterator	upper_bound(key_type const & k) const
	{
		for (iterator it = this->begin(); it != this->end(); ++it)
		{
			if (this->key_comp()(k, *it)) return it;
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
	bool	equal(key_type const & x, key_type const & y) const {
		return (!this->key_comp()(x, y) && !this->key_comp()(y, x));
	}
};

template <class T,						// set::key_type/value_type
		class Compare = ft::less<T>,	// set::key_compare/value_compare
		class Alloc = ft::allocator<T>	// set::allocator_type
		>
class set : public ft::setBase<T, Compare, Alloc>
{
	typedef typename Alloc::template rebind<treeNode<T> >::other	node_allocator;

public:
	typedef T														key_type;
	typedef T														value_type;
	typedef Compare													key_compare;
	typedef Compare													value_compare;
	typedef Alloc													allocator_type;
	typedef typename allocator_type::reference						reference;
	typedef typename allocator_type::const_reference				const_reference;
	typedef typename allocator_type::pointer						pointer;
	typedef typename allocator_type::const_pointer					const_pointer;
	typedef ft::treeIterator<value_type, node_allocator>			iterator;
	typedef ft::constTreeIterator<value_type, node_allocator>		const_iterator;
	typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	typedef std::ptrdiff_t											difference_type;
	typedef typename allocator_type::size_type						size_type;

private:
	typedef	ft::setBase<T, Compare, Alloc>							base;
	typedef typename base::node										node;

public:
	// 1. empty constructor
	explicit set(key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type()):
		base(comp, alloc) {}

	// 2. range constructor
	template <class Iterator>
	set(Iterator first, Iterator last,
	 	key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type(),
	 	typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0):
	 	base(comp, alloc) {
		this->insert(first, last);
	}

	// 3. copy constructor
	set(set const & other):
		base(other) {
		this->insert(other.begin(), other.end());
	}

	// destructor
	~set() {
		this->clear();
	}

	// assignment operator overload
	set&	operator=(set const & rhs)
	{
		this->clear();
		base::operator=(rhs);
		this->insert(rhs.begin(), rhs.end());
		return *this;
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
		return ft::make_pair(iterator(this->m_tree, ret.first), ret.second);
	}

	// 2. insertion with hint
	iterator	insert(iterator position, value_type const & val)
	{
		if (position != this->end() && this->equal(*position, val)) return position;

		ft::pair<node*, bool>	ret;

		if (this->empty())
			ret = this->BSTinsert(this->root(), val);
		else if (position == this->end())
		{
			--position;
			if (this->key_comp()(*position, val))
				ret = this->BSTinsert(position.node(), val);
			else
				ret = this->BSTinsert(this->root(), val);
		}
		else if (this->key_comp()(*position, val))
		{
			iterator	tmp(position);
			++tmp;
			if (tmp == this->end() || this->key_comp()(val, *tmp))
				ret = this->BSTinsert(position.node(), val);
			else
				ret = this->BSTinsert(this->root(), val);
		}
		else
		{
			iterator	tmp(position);
			--tmp;
			if (position == this->begin() || this->key_comp()(*tmp, val))
				ret = this->BSTinsert(position.node(), val);
			else
				ret = this->BSTinsert(this->root(), val);
		}
		if (ret.second)
		{
			this->fixInsertViolation(ret.first);
			++this->m_size;
		}
		return iterator(this->m_tree, ret.first);
	}

	// 3. range insertion
	template <class Iterator>
	void 	insert(Iterator first, Iterator last,
			  		typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0)
	{
		while (first != last)
		{
			this->insert(*first);
			++first;
		}
	}

	// 1. erase iterator
	void	erase(iterator position)
	{
		this->BSTerase(position);
		--this->m_size;
		if (this->empty()) {
			this->treeInit();
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
	void	erase(iterator first, iterator last)
	{
		while (first != last)
		{
			iterator	tmp = first;
			++first;
			this->erase(tmp);
		}
	}

	void clear() {
		this->erase(this->begin(), this->end());
	}

	size_type	count(value_type const & val) const {
		return this->find(val) != this->end();
	}

private:
	ft::pair<node*, bool>	BSTinsert(node* curr, value_type const & val) {
		this->detach();

		node*	p = this->NIL();

		while (curr != this->NIL()) {
			p = curr;
			if (this->equal(val, curr->value)) {
				this->attach();
				return ft::make_pair(curr, false);
			}
			else if (this->key_comp()(val, curr->value))
				curr = curr->left;
			else
				curr = curr->right;
		}

		node*	newNode = this->m_alloc.allocate(1);
		this->m_alloc.construct(newNode, val);

		newNode->parent = p;

		if (p == this->NIL())
			this->m_tree.m_root = newNode;
		else if (this->key_comp()(newNode->value, p->value))
			p->left = newNode;
		else
			p->right = newNode;

		newNode->left = this->NIL();
		newNode->right = this->NIL();

		this->attach();

		return ft::make_pair(newNode, true);
	}
};

template <class T, class Compare, class Alloc>
bool operator==(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs) {
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Compare, class Alloc>
bool operator!=(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs) {
	return !(lhs == rhs);
}

template <class T, class Compare, class Alloc>
bool operator<(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Compare, class Alloc>
bool operator<=(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs) {
	return !(rhs < lhs);
}

template <class T, class Compare, class Alloc>
bool operator>(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs) {
	return rhs < lhs;
}

template <class T, class Compare, class Alloc>
bool operator>=(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs) {
	return !(lhs < rhs);
}

template <class T, class Compare, class Alloc>
void swap(set<T, Compare, Alloc> & x, set<T, Compare, Alloc> & y) {
	x.swap(y);
}

template <class T,						// multiset::key_type/value_type
		class Compare = ft::less<T>,	// multiset::key_compare/value_compare
		class Alloc = ft::allocator<T>	// multiset::allocator_type
		>
class multiset : public ft::setBase<T, Compare, Alloc>
{
	typedef typename Alloc::template rebind<treeNode<T> >::other	node_allocator;

public:
	typedef T														key_type;
	typedef T														value_type;
	typedef Compare													key_compare;
	typedef Compare													value_compare;
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

private:
	typedef ft::setBase<T, Compare, Alloc>							base;
	typedef typename base::node										node;

public:
	// 1. empty constructor
	explicit multiset(key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type()):
		base(comp, alloc) {}

	// 2. range constructor
	template <class Iterator>
	multiset(Iterator first, Iterator last,
			 key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type(),
			 typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0):
			 base(comp, alloc) {
		this->insert(first, last);
	}

	// 3. copy constructor
	multiset(multiset const & other):
		base(other) {
		this->insert(other.begin(), other.end());
	}

	// destructor
	~multiset() {
		this->clear();
	}

	// assignment operator overload
	multiset&	operator=(multiset const & rhs) {
		this->clear();
		base::operator=(rhs);
		this->insert(rhs.begin(), rhs.end());
		return *this;
	}

	// 1. single element insertion
	iterator	insert(value_type const & val) {
		node*	ret = this->BSTinsert(this->root(), val);

		this->fixInsertViolation(ret);
		++this->m_size;
		return iterator(this->m_tree, ret);
	}

	// 2. insertion with hint
	iterator	insert(iterator position, value_type const & val) {
		node*	ret;

		if (this->empty())
			ret = this->BSTinsert(this->root(), val);
		else if (position == this->end()) {
			--position;
			if (this->key_comp()(*position, val))
				ret = this->BSTinsert(position.node(), val);
			else
				ret = this->BSTinsert(this->root(), val);
		}
		else if (this->key_comp()(*position, val)) {
			iterator	tmp(position);
			++tmp;
			if (tmp == this->end() || this->key_comp()(val, *tmp))
				ret = this->BSTinsert(position.node(), val);
			else
				ret = this->BSTinsert(this->root(), val);
		}
		else {
			iterator	tmp(position);
			--tmp;
			if (position == this->begin() || this->key_comp()(*tmp, val))
				ret = this->BSTinsert(position.node(), val);
			else
				ret = this->BSTinsert(this->root(), val);
		}
		this->fixInsertViolation(ret);
		++this->m_size;
		return iterator(this->m_tree, ret);
	}

	// 3. range insertion
	template <class Iterator>
	void	insert(Iterator first, Iterator last,
				   typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0) {
		while (first != last)
		{
			this->insert(*first);
			++first;
		}
	}

	// 1. erase by iterator
	void erase(iterator position) {
		this->BSTerase(position);

		--this->m_size;
		if (this->empty()) {
			this->treeInit();
		}
	}

	// 2. erase by key
	size_type	erase(key_type const & k) {
		ft::pair<iterator, iterator>	p = this->equal_range(k);
		size_type	ret = ft::distance(p.first, p.second);

		this->erase(p.first, p.second);
		return ret;
	}

	// 3. erase range
	void	erase(iterator first, iterator last) {
		while (first != last) {
			iterator	tmp = first;
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
	node*	BSTinsert(node* curr, value_type const & val) {
		this->detach();

		node*	p = this->NIL();

		while (curr != this->NIL()) {
			p = curr;
			if (this->key_comp()(val, curr->value))
				curr = curr->left;
			else
				curr = curr->right;
		}

		node*	newNode = this->m_alloc.allocate(1);
		this->m_alloc.construct(newNode, val);

		newNode->parent = p;

		if (p == this->NIL())
			this->m_tree.m_root = newNode;
		else if (this->key_comp()(newNode->value, p->value))
			p->left = newNode;
		else
			p->right = newNode;

		newNode->left = this->NIL();
		newNode->right = this->NIL();

		this->attach();

		return newNode;
	}
};

template <class T, class Compare, class Alloc>
bool operator==(multiset<T, Compare, Alloc> const & lhs, multiset<T, Compare, Alloc> const & rhs) {
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Compare, class Alloc>
bool operator!=(multiset<T, Compare, Alloc> const & lhs, multiset<T, Compare, Alloc> const & rhs) {
	return !(lhs == rhs);
}

template <class T, class Compare, class Alloc>
bool operator<(multiset<T, Compare, Alloc> const & lhs, multiset<T, Compare, Alloc> const & rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Compare, class Alloc>
bool operator<=(multiset<T, Compare, Alloc> const & lhs, multiset<T, Compare, Alloc> const & rhs) {
	return !(rhs < lhs);
}

template <class T, class Compare, class Alloc>
bool operator>(multiset<T, Compare, Alloc> const & lhs, multiset<T, Compare, Alloc> const & rhs) {
	return rhs < lhs;
}

template <class T, class Compare, class Alloc>
bool operator>=(multiset<T, Compare, Alloc> const & lhs, multiset<T, Compare, Alloc> const & rhs) {
	return !(lhs < rhs);
}

template <class T, class Compare, class Alloc>
void swap(multiset<T, Compare, Alloc> & x, multiset<T, Compare, Alloc> & y) {
	x.swap(y);
}

} //end of namespace ft

#endif

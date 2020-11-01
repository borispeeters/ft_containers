#ifndef SET_HPP
# define SET_HPP

# include <functional>
# include <memory>
# include <utility>
# include "algorithm.hpp"
# include "iterator.hpp"
# include "treeIterator.hpp"
# include "treeNode.hpp"
# include "type_traits.hpp"

namespace ft
{

template <class T,						// set::key_type/value_type
		class Compare = std::less<T>,	// set::key_compare/value_compare
		class Alloc = std::allocator<T>	// set::allocator_type
		>
class set
{
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
	typedef ft::treeIterator<value_type>							iterator;
	typedef ft::constTreeIterator<value_type>						const_iterator;
	typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
	typedef typename allocator_type::size_type						size_type;

private:
	treeNode<value_type>*	m_root;
	treeNode<value_type>*	m_first;
	treeNode<value_type>*	m_last;
	size_type				m_size;
	key_compare				m_comp;
	allocator_type			m_alloc;

public:
	// 1. empty constructor
	explicit set(key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type()):
		m_root(0),
		m_first(0),
		m_last(0),
		m_size(0),
		m_comp(comp),
		m_alloc(alloc)
	{
		this->setInit();
	}

	// 2. range constructor
	template <class Iterator>
	set(Iterator first, Iterator last,
	 	key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type(),
	 	typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0):
	 	m_root(0),
	 	m_first(0),
	 	m_last(0),
	 	m_size(0),
	 	m_comp(comp),
	 	m_alloc(alloc)
	{
		this->setInit();
		this->insert(first, last);
	}

	// 3. copy constructor
	set(set const & other):
		m_root(0),
		m_first(0),
		m_last(0),
		m_size(0),
		m_comp(other.key_comp),
		m_alloc(other.get_allocator())
	{
		this->setInit();
		this->insert(other.begin(), other.end());
	}

	// destructor
	~set()
	{
		delete this->m_first;
		delete this->m_last;
	}

	// assignment operator overload
	set&	operator=(set const & rhs)
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

	// 1. single element insertion
	std::pair<iterator, bool>	insert(value_type const & val)
	{
		std::pair<treeNode<value_type>*, bool>	ret(this->BSTInsert(this->root(), val));

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
		if (position != this->end() && this->equal(*position, val)) return position;

		std::pair<treeNode<value_type>*, bool>	ret;

		if (this->empty())
			ret = this->BSTinsert(this->root(), val);
		else if (position == this->end())
		{
			--position;
			if (*position < val)
				ret = this->BSTinsert(position.node(), val);
			else
				ret = this->BSTinsert(this->root(), val);
		}
		else if (*position < val)
		{
			iterator	tmp(position);
			++tmp;
			if (tmp == this->end() || *tmp > val)
				ret = this->BSTinsert(position.node(), val);
			else
				ret = this->BSTinsert(this->root(), val);
		}
		else if (*position > val)
		{
			iterator	tmp(position);
			--tmp;
			if (position == this->begin() || *tmp < val)
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

	// 2. erase key

	// 3. erase range

	void swap(set & x)
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
	value_compare	value_comp() const { return this->m_comp; }

	iterator		find(value_type const & val)
	{
		treeNode<value_type>*	node(this->root());
		while (this->validNode(node))
		{
			if (this->equal(node->value, val)) return iterator(node);
			else if (this->value_comp()(node->value, val)) node = node->right;
			else if (this->value_comp()(val, node->value)) node = node->left;
		}
		return this->end();
	}

	const_iterator	find(value_type const & val) const
	{
		treeNode<value_type>*	node(this->root());
		while (this->validNode(node))
		{
			if (this->equal(node->value, val)) return const_iterator(node);
			else if (this->value_comp()(node->value, val)) node = node->right;
			else if (this->value_comp()(val, node->value)) node = node->left;
		}
		return this->end();
	}

	size_type		count(value_type const & val) const { return this->find(val) != this->end(); }

	iterator		lower_bound(value_type const & val)
	{
		for (iterator it(this->begin()); it != this->end(); ++it)
		{
			if (!this->key_comp()(it->first, val)) return it;
		}
		return this->end();
	}

	const_iterator	lower_bound(value_type const & val) const
	{
		for (const_iterator it(this->begin()); it != this->end(); ++it)
		{
			if (!this->key_comp()(it->first, val)) return it;
		}
		return this->end();
	}

	iterator		upper_bound(value_type const & val)
	{
		for (iterator it(this->begin()); it != this->end(); ++it)
		{
			if (this->key_comp()(val, it->first)) return it;
		}
		return this->end();
	}

	const_iterator	upper_bound(value_type const & val) const
	{
		for (const_iterator it(this->begin()); it != this->end(); ++it)
		{
			if (this->key_comp()(val, it->first)) return it;
		}
		return this->end();
	}

	std::pair<iterator, iterator>				equal_range(value_type const & val) {
		return std::make_pair(this->lower_bound(val), this->upper_bound(val));
	}
	std::pair<const_iterator, const_iterator>	equal_range(value_type const & val) const {
		return std::make_pair(this->lower_bound(val), this->upper_bound(val));
	}

	allocator_type	get_allocator() const { return this->m_alloc; }

	void printBT() const
	{
		this->printBT("", this->root(), false);
		std::cout << std::endl;
	}

private:
//	void printBT(std::str)

private:
	void printBT(std::string const & prefix, treeNode<value_type>* trav, bool isLeft) const
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

	void setInit()
	{
		this->m_first = new treeNode<value_type>(BLACK);
		this->m_last = new treeNode<value_type>(BLACK);
		this->m_firstNode()->parent = this->lastNode();
	}

	std::pair<treeNode<value_type>*, bool>	BSTinsert(treeNode<value_type>* curr, value_type const & val);

	std::pair<treeNode<value_type>*, bool>	BSTerase(iterator position);

	void transplant(treeNode<value_type>* u, treeNode<value_type>* v);

	void rotateLeft(treeNode<value_type>* x);

	void rotateRight(treeNode<value_type>* x);

	void recolour(treeNode<value_type>* node)
	{
		if (node->colour == BLACK) node->colour = RED;
		else if (node->colour == RED) node->colour = BLACK;
	}

	void fixInsertViolation(treeNode<value_type> *& node);

	void fixEraseViolation(treeNode<value_type> *& x);

	bool equal(value_type const & x, value_type const & y) const {
		return (!this->value_comp()(x, y) && !this->value_comp()(y, x));
	}
	bool validNode(treeNode<value_type>* node) const {
		return (node != 0 && node != this->firstNode() && node != this->lastNode());
	}
};

template <class Key, class Compare, class Alloc>
bool operator==(set<Key, Compare, Alloc> const & lhs, set<Key, Compare, Alloc> const & rhs) {
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class Key, class Compare, class Alloc>
bool operator!=(set<Key, Compare, Alloc> const & lhs, set<Key, Compare, Alloc> const & rhs) {
	return !(lhs == rhs);
}

template <class Key, class Compare, class Alloc>
bool operator<(set<Key, Compare, Alloc> const & lhs, set<Key, Compare, Alloc> const & rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Key, class Compare, class Alloc>
bool operator<=(set<Key, Compare, Alloc> const & lhs, set<Key, Compare, Alloc> const & rhs) {
	return !(rhs < lhs);
}

template <class Key, class Compare, class Alloc>
bool operator>(set<Key, Compare, Alloc> const & lhs, set<Key, Compare, Alloc> const & rhs) {
	return rhs < lhs;
}

template <class Key, class Compare, class Alloc>
bool operator >=(set<Key, Compare, Alloc> const & lhs, set<Key, Compare, Alloc> const & rhs) {
	return !(lhs < rhs);
}

template <class Key, class Compare, class Alloc>
void swap(set<Key, Compare, Alloc> const & x, set<Key, Compare, Alloc> const & y) {
	x.swap(y);
}

}; //end of namespace ft

#endif

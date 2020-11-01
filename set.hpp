#ifndef SET_HPP
# define SET_HPP

# include <functional>
# include <memory>
# include <utility>
# include "algorithm.hpp"
# include "iterator.hpp"
# include "setIterator.hpp"
# include "setNode.hpp"
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
	typedef ft::setIterator<value_type>								iterator;
	typedef ft::constSetIterator<value_type>						const_iterator;
	typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
	typedef typename allocator_type::size_type						size_type;

private:
	setNode<value_type>*	m_root;
	setNode<value_type>*	m_first;
	setNode<value_type>*	m_last;
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
		std::pair<setNode<value_type>*, bool>	ret(this->BSTInsert(this->root(), val));

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
		asd;
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
		setNode<value_type>*	node(this->root())
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
		setNode<value_type>*	node(this->root())
		while (this->validNode(node))
		{
			if (this->equal(node->value, val)) return const_iterator(node);
			else if (this->value_comp()(node->value, val)) node = node->right;
			else if (this->value_comp()(val, node->value)) node = node->left;
		}
		return this->end();
	}

	size_type	count(value_type const & val) const { return this->find(val) != this->end(); }

	iterator	lower_bound()

private:
	void setInit()
	{
		this->m_first = new setNode<value_type>(BLACK);
		this->m_last = new setNode<value_type>(BLACK);
		this->m_firstNode()->parent = this->lastNode();
	}
};

}; //end of namespace ft

#endif

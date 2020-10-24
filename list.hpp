#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include "algorithm.hpp"
# include "listIterator.hpp"
# include "listNode.hpp"

namespace ft
{

template <class T, class Alloc = std::allocator<T> >
class list
{
public:
	typedef	T															value_type;
	typedef	Alloc														allocator_type;
	typedef	typename allocator_type::reference							reference;
	typedef	typename allocator_type::const_reference					const_reference;
	typedef	typename allocator_type::pointer							pointer;
	typedef	typename allocator_type::const_pointer						const_pointer;
	typedef ft::listIterator<value_type>								iterator;
	typedef ft::constListIterator<value_type>							const_iterator;
	typedef ft::reverse_iterator<iterator>								reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
	typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
	typedef	typename allocator_type::size_type							size_type;

private:
	listNode<value_type>	*m_head;
	listNode<value_type>	*m_tail;
	size_type				m_size;
	allocator_type			m_alloc;

public:
	// 1. default constructor
	explicit list(allocator_type const & alloc = allocator_type()):
		m_head(0),
		m_tail(0),
		m_size(0),
		m_alloc(alloc)
	{
		this->listInit();
	}

	// 2. fill constructor
	explicit list(size_type n, value_type const & val = value_type(),
			   allocator_type const & alloc = allocator_type()):
		m_head(0),
		m_tail(0),
		m_size(0),
		m_alloc(alloc)
	{
		this->listInit();
		this->assign(n, val);
	}

	// 3. range constructor
	template <class Iterator>
	list(Iterator first, Iterator last,
	  allocator_type const & alloc = allocator_type()):
	 	m_head(0),
	 	m_tail(0),
	 	m_size(0),
	 	m_alloc(alloc)
	{
		this->listInit();
		this->assign(first, last);
	}

	// 4. copy constructor
	list(list const & other):
		m_head(0),
		m_tail(0),
		m_size(0),
		m_alloc(other.get_allocator())
	{
		this->listInit();
		this->assign(other.begin(), other.end());
	}

	// destructor
	~list()
	{
		delete this->m_head;
		delete this->m_tail;
	}

	// assignment operator overload
	list&	operator=(list const & rhs)
	{
		if (&rhs != this)
		{
			this->m_alloc = rhs.get_allocator();
			this->assign(rhs.begin(), rhs.end());
		}
		return *this;
	}

	iterator		begin() { return this->head()->next; }
	const_iterator	begin() const { return this->head()->next; }
	iterator		end() { return this->tail(); }
	const_iterator	end() const { return this->tail(); }

	reverse_iterator		rbegin() { return reverse_iterator(this->end()); }
	const_reverse_iterator	rbegin() const { return const_reverse_iterator(this->end()); }
	reverse_iterator		rend() { return reverse_iterator(this->begin()); }
	const_reverse_iterator	rend() const { return const_reverse_iterator(this->begin()); }

	bool 		empty() const { return this->size() == 0; }
	size_type	size() const { return this->m_size; }
	size_type	max_size() const { return this->get_allocator().max_size(); }

	reference 		front() { return *(this->head()->next->data); }
	const_reference	front() const { return *(this->head()->next->data); }
	reference 		back() { return *(this->tail()->prev->data); }
	const_reference	back() const { return *(this->tail()->prev->data); }

	// 1. range assign
	template <class Iterator>
	void assign(Iterator first, Iterator last,
				typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0)
	{
		this->clear();
		while (first != last)
		{
			this->push_back(*first);
			++first;
		}
	}

	// 2. fill assign
	void assign(size_type n, value_type const & val)
	{
		this->clear();
		for (size_type i = 0; i < n; ++i)
			this->push_back(val);
	}

	void push_front(value_type const & val)
	{
		listNode<value_type>*	newNode = new listNode<value_type>(val);
		newNode->next = this->head()->next;
		newNode->next->prev = newNode;
		newNode->prev = this->head();
		this->head()->next = newNode;
		++this->m_size;
	}
	void pop_front()
	{
		listNode<value_type>*	delNode = this->head()->next;
		this->head()->next = delNode->next;
		this->head()->next->prev = this->head();
		delete delNode;
		--this->m_size;
	}
	void push_back(value_type const & val)
	{
		listNode<value_type>*	newNode = new listNode<value_type>(val);
		newNode->prev = this->tail()->prev;
		newNode->prev->next = newNode;
		newNode->next = this->tail();
		this->tail()->prev = newNode;
		++this->m_size;
	}
	void pop_back()
	{
		listNode<value_type>*	delNode = this->tail()->prev;
		this->tail()->prev = delNode->prev;
		this->tail()->prev->next = this->tail();
		delete delNode;
		--this->m_size;
	}

	// 1. single element insertion
	iterator	insert(iterator position, value_type const & val)
	{
		listNode<value_type>*	newNode = new listNode<value_type>(val);
		newNode->next = position.node();
		newNode->prev = position.node()->prev;
		newNode->prev->next = newNode;
		newNode->next->prev = newNode;
		++this->m_size;
		return iterator(newNode);
	}

	// 2. fill insertion
	void 		insert(iterator position, size_type n, value_type const & val)
	{
		for (size_type i = 0; i < n; ++i)
			this->insert(position, val);
	}

	// 3. range insertion
	template <class Iterator>
	void 		insert(iterator position, Iterator first, Iterator last,
					   typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0)
	{
		while (first != last)
		{
			this->insert(position, *first);
			++first;
		}
	}

	// 1. erase single element
	iterator	erase(iterator position)
	{
		listNode<value_type>*	delNode = position.node();
		position.node()->prev->next = position.node()->next;
		position.node()->next->prev = position.node()->prev;
		++position;
		delete delNode;
		--this->m_size;
		return position;
	}

	// 2. erase range of elements
	iterator	erase(iterator first, iterator last)
	{
		while (first != last)
		{
			erase(first);
			++first;
		}
		return first;
	}

	void 	swap(list & x)
	{
		ft::swap(this->m_head, x.m_head);
		ft::swap(this->m_tail, x.m_tail);
		ft::swap(this->m_size, x.m_size);
		ft::swap(this->m_alloc, x.m_alloc);
	}

	void resize(size_type n, value_type val = value_type())
	{
		while (this->size() > n)
			this->pop_back();
		while (this->size < n)
			this->push_back(val);
	}

	void clear() { while (this->size() > 0) this->pop_back(); }

	// 1. splice entire list
	void splice(iterator position, list & x)
	{
		if (this != &x && !x.empty())
		{
			position.node()->prev->next = x.head()->next;
			position.node()->prev = x.tail()->prev;
			x.head()->next->prev = position.node()->prev;
			x.tail()->prev->next = position.node();
			x.head()->next = x.tail();
			x.tail()->prev = x.head();
			this->m_size += x.size();
			x.m_size = 0;
		}
	}

	// 2. splice single element
	void splice(iterator position, list & x, iterator i)
	{
		if (!x.empty())
		{
			i.node()->prev->next = i.node()->next;
			i.node()->next->prev = i.node()->prev;
			i.node()->prev = position.node()->prev;
			i.node()->next = position.node();
			position.node()->prev->next = i.node();
			position.node()->prev = i.node();
			++this->m_size;
			--x.m_size;
		}
	}

	// 3. splice range of elements
	void splice(iterator position, list & x, iterator first, iterator last)
	{
		while (first != last)
		{
			iterator	tmp(first);
			++first;
			this->splice(position, x, tmp);
		}
	}

	void remove(value_type const & val)
	{
		iterator	it = this->begin();
		while (it != this->end())
		{
			if (*it == val)
				it = this->erase(it);
			else
				++it;
		}
	}

	template <class Predicate>
	void remove_if(Predicate pred)
	{
		iterator	it = this->begin();
		while (it != this->end())
		{
			if (pred(*it))
				it = this->erase(it);
			else
				++it;
		}
	}

	void unique()
	{
		if (this->size() <= 1)
			return ;
		iterator	it = this->begin();
		++it;
		while (it != this->end())
		{
			iterator	prev = it;
			--prev;
			if (*it == *prev)
				it = this->erase(it);
			else
				++it;
		}
	}

	template <class BinaryPredicate>
	void unique(BinaryPredicate binary_pred)
	{
		if (this->size() <= 1)
			return ;
		iterator	it = this->begin();
		++it;
		while (it != this->end())
		{
			iterator	prev = it;
			--prev;
			if (binary_pred(*it, *prev))
				it = this->erase(it);
			else
				++it;
		}
	}

	void merge(list & x)
	{
		if (this != &x)
		{
			iterator	it = this->begin();
			while (!x.empty())
			{
				if (it == this->end() || *(x.begin()) < *it) this->splice(it, x, x.begin());
				else ++it;
			}
		}
	}

	template <class Compare>
	void merge(list & x, Compare comp)
	{
		if (this != &x)
		{
			iterator	it = this->begin();
			while (!x.empty())
			{
				if (it == this->end() || comp(*(x.begin()), *it)) this->splice(it, x, x.begin());
				else ++it;
			}
		}
	}

	void sort()
	{
		if (this->size() <= 1) return ;

		iterator	it = this->begin();
	}

	template <class Compare>
	void sort(Compare comp)
	{
		if (this->size() <= 1) return ;
		list	tmp(this->begin(), this->end());
		this->clear();

		while (tmp.size() > 0)
		{
			iterator	min = ft::min_element(tmp.begin(), tmp.end(), comp);
			this->push_back(*min);
			tmp.erase(min);
		}
	}

	void reverse()
	{
		if (this->size() <= 1)
			return ;
		list	tmp(this->begin(), this->end());
		this->clear();
		for (iterator it = tmp.begin(); it != tmp.end(); ++it)
			this->push_front(*it);
		tmp.clear();
	}

	allocator_type	get_allocator() const { return this->m_alloc; }
private:
	void listInit()
	{
		this->m_head = new listNode<value_type>();
		this->m_tail = new listNode<value_type>();
		this->head()->next = this->tail();
		this->tail()->prev = this->head();
	}

	listNode<value_type>*	head() const { return this->m_head; }
	listNode<value_type>*	tail() const { return this->m_tail; }
};

template <class T, class Alloc>
bool operator==(list<T, Alloc> const & lhs, list<T, Alloc> const & rhs)
{ return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }

template <class T, class Alloc>
bool operator!=(list<T, Alloc> const & lhs, list<T, Alloc> const & rhs) { return !(lhs == rhs); }

template <class T, class Alloc>
bool operator<(list<T, Alloc> const & lhs, list<T, Alloc> const & rhs)
{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

template <class T, class Alloc>
bool operator<=(list<T, Alloc> const & lhs, list<T, Alloc> const & rhs) { return !(rhs < lhs); }

template <class T, class Alloc>
bool operator>(list<T, Alloc> const & lhs, list<T, Alloc> const & rhs) { return rhs < lhs; }

template <class T, class Alloc>
bool operator>=(list<T, Alloc> const & lhs, list<T, Alloc> const & rhs) { return !(lhs < rhs); }

template <class T, class Alloc>
void swap(list<T, Alloc> & x, list<T, Alloc> & y) { x.swap(y); }

}; //end of namespace ft

#endif

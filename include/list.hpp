#ifndef _FT_LIST_HPP
# define _FT_LIST_HPP

# include "../src/_listIterator.hpp"
# include "../src/_listNode.hpp"
# include "algorithm.hpp"
# include "functional.hpp"
# include "memory.hpp"

namespace ft
{

template <class T, class Alloc = ft::allocator<T> >
class list
{
public:
	typedef	T														value_type;
	typedef	Alloc													allocator_type;
	typedef	typename allocator_type::reference						reference;
	typedef	typename allocator_type::const_reference				const_reference;
	typedef	typename allocator_type::pointer						pointer;
	typedef	typename allocator_type::const_pointer					const_pointer;
	typedef ft::listIterator<value_type>							iterator;
	typedef ft::constListIterator<value_type>						const_iterator;
	typedef ft::reverse_iterator<iterator>							reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
	typedef std::ptrdiff_t											difference_type;
	typedef	typename allocator_type::size_type						size_type;

private:
	typedef listNode<value_type>									node;
	typedef typename allocator_type::template rebind<node>::other	node_allocator;

	node			*m_head;
	node			*m_tail;
	size_type		m_size;
	node_allocator	m_alloc;

public:
	// 1. default constructor
	explicit list(allocator_type const & alloc = allocator_type()):
		m_head(NULL),
		m_tail(NULL),
		m_size(0),
		m_alloc(alloc) {
		this->listInit();
	}

	// 2. fill constructor
	explicit list(size_type n, value_type const & val = value_type(),
			   allocator_type const & alloc = allocator_type()):
		m_head(NULL),
		m_tail(NULL),
		m_size(0),
		m_alloc(alloc) {
		this->listInit();
		this->assign(n, val);
	}

	// 3. range constructor
	template <class Iterator>
	list(Iterator first, Iterator last,
	  allocator_type const & alloc = allocator_type()):
	 	m_head(NULL),
	 	m_tail(NULL),
	 	m_size(0),
	 	m_alloc(alloc) {
		this->listInit();
		this->assign(first, last);
	}

	// 4. copy constructor
	list(list const & other):
		m_head(NULL),
		m_tail(NULL),
		m_size(0),
		m_alloc(other.get_allocator()) {
		this->listInit();
		this->assign(other.begin(), other.end());
	}

	// destructor
	~list() {
		this->clear();
		this->listTerminate();
	}

	// assignment operator overload
	list&	operator=(list const & rhs) {
		if (&rhs != this) {
			this->m_alloc = rhs.get_allocator();
			this->assign(rhs.begin(), rhs.end());
		}
		return *this;
	}

	iterator		begin() { return iterator(this->head()->next); }
	const_iterator	begin() const { return const_iterator(this->head()->next); }
	iterator		end() { return iterator(this->tail()); }
	const_iterator	end() const { return const_iterator(this->tail()); }

	reverse_iterator		rbegin() { return reverse_iterator(this->end()); }
	const_reverse_iterator	rbegin() const { return const_reverse_iterator(this->end()); }
	reverse_iterator		rend() { return reverse_iterator(this->begin()); }
	const_reverse_iterator	rend() const { return const_reverse_iterator(this->begin()); }

	bool 		empty() const { return this->size() == 0; }
	size_type	size() const { return this->m_size; }

	size_type	max_size() const {
		return ft::min<size_type>(this->m_alloc.max_size(),
								  std::numeric_limits<difference_type>::max());
	}

	reference 		front() { return this->head()->next->data; }
	const_reference	front() const { return this->head()->next->data; }
	reference 		back() { return this->tail()->prev->data; }
	const_reference	back() const { return this->tail()->prev->data; }

	// 1. range assign
	template <class Iterator>
	void assign(Iterator first, Iterator last,
				typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0) {
		this->clear();
		while (first != last) {
			this->push_back(*first);
			++first;
		}
	}

	// 2. fill assign
	void assign(size_type n, value_type const & val) {
		this->clear();
		for (size_type i = 0; i < n; ++i)
			this->push_back(val);
	}

	void push_front(value_type const & val) {
		node*	newNode = this->m_alloc.allocate(1);
		this->m_alloc.construct(newNode, val);
		newNode->next = this->head()->next;
		newNode->next->prev = newNode;
		newNode->prev = this->head();
		this->head()->next = newNode;
		++this->m_size;
	}

	void pop_front() {
		node*	delNode = this->head()->next;
		this->head()->next = delNode->next;
		this->head()->next->prev = this->head();
		this->m_alloc.destroy(delNode);
		this->m_alloc.deallocate(delNode, 1);
		--this->m_size;
	}

	void push_back(value_type const & val) {
		node*	newNode = this->m_alloc.allocate(1);
		this->m_alloc.construct(newNode, val);
		newNode->prev = this->tail()->prev;
		newNode->prev->next = newNode;
		newNode->next = this->tail();
		this->tail()->prev = newNode;
		++this->m_size;
	}

	void pop_back() {
		node*	delNode = this->tail()->prev;
		this->tail()->prev = delNode->prev;
		this->tail()->prev->next = this->tail();
		this->m_alloc.destroy(delNode);
		this->m_alloc.deallocate(delNode, 1);
		--this->m_size;
	}

	// 1. single element insertion
	iterator	insert(iterator position, value_type const & val) {
		node*	newNode = this->m_alloc.allocate(1);
		this->m_alloc.construct(newNode, val);
		newNode->next = position.node();
		newNode->prev = position.node()->prev;
		newNode->prev->next = newNode;
		newNode->next->prev = newNode;
		++this->m_size;
		return iterator(newNode);
	}

	// 2. fill insertion
	void 		insert(iterator position, size_type n, value_type const & val) {
		for (size_type i = 0; i < n; ++i)
			this->insert(position, val);
	}

	// 3. range insertion
	template <class Iterator>
	void 		insert(iterator position, Iterator first, Iterator last,
					   typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0) {
		while (first != last) {
			this->insert(position, *first);
			++first;
		}
	}

	// 1. erase single element
	iterator	erase(iterator position) {
		node*	delNode = position.node();
		position.node()->prev->next = position.node()->next;
		position.node()->next->prev = position.node()->prev;
		++position;
		this->m_alloc.destroy(delNode);
		this->m_alloc.deallocate(delNode, 1);
		--this->m_size;
		return position;
	}

	// 2. erase range of elements
	iterator	erase(iterator first, iterator last) {
		while (first != last)
			first = erase(first);
		return first;
	}

	void 	swap(list & x) {
		ft::swap(this->m_head, x.m_head);
		ft::swap(this->m_tail, x.m_tail);
		ft::swap(this->m_size, x.m_size);
		ft::swap(this->m_alloc, x.m_alloc);
	}

	void resize(size_type n, value_type val = value_type()) {
		while (this->size() > n)
			this->pop_back();
		while (this->size() < n)
			this->push_back(val);
	}

	void clear() { while (!this->empty()) this->pop_back(); }

	// 1. splice entire list
	void splice(iterator position, list & x) {
		if (this != &x && !x.empty()) {
			node*	first = x.head()->next;
			node*	last = x.tail()->prev;
			this->unlinkNodes(first, last);
			this->linkNodes(position.node(), first, last);
			this->m_size += x.size();
			x.m_size = 0;
		}
	}

	// 2. splice single element
	void splice(iterator position, list & x, iterator i) {
		if (position.node() != i.node() && position.node() != i.node()->next) {
			node*	first = i.node();
			this->unlinkNodes(first, first);
			this->linkNodes(position.node(), first, first);
			++this->m_size;
			--x.m_size;
		}
	}

	// 3. splice range of elements
	void splice(iterator position, list & x, iterator first, iterator last) {
		if (first != last) {
			node*	firstNode = first.node();
			--last;
			node*	lastNode = last.node();
			if (this != &x) {
				size_type	s = ft::distance(first, last) + 1;
				x.m_size -= s;
				this->m_size += s;
			}
			this->unlinkNodes(firstNode, lastNode);
			this->linkNodes(position.node(), firstNode, lastNode);
		}
	}

	void remove(value_type const & val) {
		iterator	it = this->begin();
		while (it != this->end()) {
			if (*it == val)
				it = this->erase(it);
			else
				++it;
		}
	}

	template <class Predicate>
	void remove_if(Predicate pred) {
		iterator	it = this->begin();
		while (it != this->end()) {
			if (pred(*it))
				it = this->erase(it);
			else
				++it;
		}
	}

	void unique() { this->unique(ft::equal_to<value_type>()); }

	template <class BinaryPredicate>
	void unique(BinaryPredicate binary_pred) {
		if (this->size() <= 1)
			return ;
		iterator	it = this->begin();
		++it;
		while (it != this->end()) {
			iterator	prev = it;
			--prev;
			if (binary_pred(*it, *prev))
				it = this->erase(it);
			else
				++it;
		}
	}

	void merge(list & x) { this->merge(x, ft::less<value_type>()); }

	template <class Compare>
	void merge(list & x, Compare comp) {
		if (this != &x) {
			iterator	it = this->begin();
			while (!x.empty()) {
				if (it == this->end() || comp(*(x.begin()), *it)) this->splice(it, x, x.begin());
				else ++it;
			}
		}
	}

	void sort() { this->mergeSort(*this, ft::less<value_type>()); }

	template <class Compare>
	void sort(Compare comp) { this->mergeSort(*this, comp); }

	void reverse() {
		if (this->size() > 1) {
			for (iterator it = this->begin(); it != this->end(); --it)
				ft::swap(it.node()->prev, it.node()->next);
			ft::swap(this->m_head, this->m_tail);
			ft::swap(this->head()->prev, this->head()->next);
			ft::swap(this->tail()->prev, this->tail()->next);
		}
	}

	allocator_type	get_allocator() const { return this->m_alloc; }

private:
	void listInit() {
		this->m_head = this->m_alloc.allocate(1);
		this->m_tail = this->m_alloc.allocate(1);
		this->m_alloc.construct(this->m_head, node());
		this->m_alloc.construct(this->m_tail, node());
		this->head()->next = this->tail();
		this->tail()->prev = this->head();
	}

	void listTerminate() {
		this->m_alloc.destroy(this->m_head);
		this->m_alloc.destroy(this->m_tail);
		this->m_alloc.deallocate(this->m_head, 1);
		this->m_alloc.deallocate(this->m_tail, 1);
	}

	void unlinkNodes(node* first, node* last) {
		first->prev->next = last->next;
		last->next->prev = first->prev;
	}

	void linkNodes(node* Node, node* first, node* last) {
		Node->prev->next = first;
		first->prev = Node->prev;
		Node->prev = last;
		last->next = Node;
	}

	template <class Compare>
	void mergeSort(list & first, Compare comp) {
		if (first.size() > 1) {
			list	second;
			this->split(first, second);

			this->mergeSort(first, comp);
			this->mergeSort(second, comp);

			first.merge(second, comp);
		}
	}

	void split(list & first, list & second) {
		iterator	it(first.begin());
		for (size_type i = 0; i < first.size() / 2; ++i)
			++it;
		second.splice(second.begin(), first, it, first.end());
	}

	node*	head() const { return this->m_head; }
	node*	tail() const { return this->m_tail; }
};

template <class T, class Alloc>
bool operator==(list<T, Alloc> const & lhs, list<T, Alloc> const & rhs) {
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Alloc>
bool operator!=(list<T, Alloc> const & lhs, list<T, Alloc> const & rhs) {
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<(list<T, Alloc> const & lhs, list<T, Alloc> const & rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Alloc>
bool operator<=(list<T, Alloc> const & lhs, list<T, Alloc> const & rhs) {
	return !(rhs < lhs);
}

template <class T, class Alloc>
bool operator>(list<T, Alloc> const & lhs, list<T, Alloc> const & rhs) {
	return rhs < lhs;
}

template <class T, class Alloc>
bool operator>=(list<T, Alloc> const & lhs, list<T, Alloc> const & rhs) {
	return !(lhs < rhs);
}

template <class T, class Alloc>
void swap(list<T, Alloc> & x, list<T, Alloc> & y) {
	std::cout << "list swap" << std::endl;
	x.swap(y);
}

} //end of namespace ft

#endif

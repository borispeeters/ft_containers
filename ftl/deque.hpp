#ifndef _FT_DEQUE_HPP
# define _FT_DEQUE_HPP

# include <cstddef>
# include <stdexcept>
# include "_ftl/_dequeIterator.hpp"
# include "algorithm.hpp"
# include "memory.hpp"


# include <iostream>

namespace ft
{

template <class T, class Alloc = ft::allocator<T> >
class deque
{
public:
	typedef T														value_type;
	typedef Alloc													allocator_type;
	typedef typename allocator_type::reference						reference;
	typedef typename allocator_type::const_reference				const_reference;
	typedef typename allocator_type::pointer						pointer;
	typedef typename allocator_type::const_pointer					const_pointer;
	typedef ft::dequeIterator<value_type>							iterator;
//	typedef ft::constDequeIterator<value_type>						const_iterator;
	typedef ft::reverse_iterator<iterator>							reverse_iterator;
//	typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
	typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
	typedef typename allocator_type::size_type						size_type;

private:
	typedef pointer*												map_pointer;

	iterator		m_start;		// iterator to the first element
	iterator		m_finish;		// iterator to one element past the end

	map_pointer		m_map;			// pointer to the array of chunks
	size_type		m_map_size;		// size of the array of chunks
	size_type		m_chunks;		// amount of chunks allocated
	size_type		m_chunk_size;	// size of the chunks
	size_type		m_size;			// number of elements

	allocator_type	m_alloc;


public:
	// 1. default constructor
	explicit deque(allocator_type const & alloc = allocator_type()):
		m_map(NULL),
		m_map_size(0),
		m_size(0),
		m_chunks(0),
		m_alloc(alloc) {
		this->dequeInit();
	}

	// 2. fill constructor
	explicit deque(size_type n, value_type const & val = value_type(), allocator_type const & alloc = allocator_type()):
		m_map(NULL),
		m_map_size(0),
		m_size(n),
		m_chunks(0),
		m_alloc(alloc) {
		this->dequeInit();
	}

	// 3. range constructor
	template <class Iterator>
	deque(Iterator first, Iterator last, allocator_type const & alloc = allocator_type(),
		  typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0):
		m_map(NULL),
		m_map_size(0),
		m_size(ft::distance(first, last)),
		m_chunks(0),
		m_alloc(alloc) {
		this->dequeInit(ft::distance(first, last));
	}

	// 4. copy constructor
	deque(deque const & other):
		m_map(NULL),
		m_map_size(0),
		m_size(other.size()),
		m_chunks(0),
		m_alloc(other.get_allocator()) {
		this->dequeInit(other.size());
	}

	// destructor
	~deque() {}

	// assignment operator overload
	deque&	operator=(deque const & rhs)
	{
		if (&rhs != this)
		{
			//lol
		}
		return *this;
	}

	iterator		begin() { return iterator(this->m_first); }
//	const_iterator	begin() const { return const_iterator(this->m_first); }
	iterator		end() { return iterator(this->m_last); }
//	const_iterator	end() const { return const_iterator(this->m_last); }

	reverse_iterator		rbegin() { return reverse_iterator(this->end()); }
//	const_reverse_iterator  rbegin() const { return const_reverse_iterator(this->end()); }
	reverse_iterator 		rend() { return reverse_iterator(this->begin()); }
//	const_reverse_iterator 	rend() const { return const_reverse_iterator(this->begin()); }

	size_type	size() const { return this->m_size; }
	size_type	max_size() const { return this->get_allocator().max_size(); }

	void resize(size_type n, value_type val = value_type())
	{
		//lol
	}

	bool empty() const { return this->size() == 0; }

	reference 		operator[](size_type n) { return this->m_start[n]; }
	const_reference	operator[](size_type n) const { return this->m_start[n]; }

	reference 		at(size_type n)
	{
		if (n >= this->size()) throw std::out_of_range("deque");
		return this->m_start[n];
	}

	const_reference	at(size_type n) const
	{
		if (n >= this->size()) throw std::out_of_range("deque");
		return this->m_start[n];
	}

	reference 		front() { return *this->m_start; }
	const_reference	front() const { return *this->m_start; }

	reference 		back()
	{
		iterator	tmp = this->m_finish;
		--tmp;
		return *tmp;
	}

	const_reference	back() const
	{
		iterator	tmp = this->m_finish;
		--tmp;
		return *tmp;
	}

	// 1. range assign
	template <class Iterator>
	void assign(Iterator first, Iterator last,
				typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0)
	{
		//lol
	}

	// 2. fill assign
	void assign(size_type n, value_type const & val)
	{
		//lol
	}

	void push_back(value_type const & val)
	{
		this->m_finish;
	}

	void push_front(value_type const & val)
	{
		//lol
	}

	void pop_back()
	{
		//lol
	}

	void pop_front()
	{
		//lol
	}

	// 1. single element insertion
	iterator	insert(iterator position, value_type const & val)
	{
		//lol
	}

	// 2. fill insertion
	void insert(iterator position, size_type n, value_type const & val)
	{
		for (size_type i = 0; i < n; ++i)
			this->insert(position, val);
	}

	// 3. range insertion
	template <class Iterator>
	void insert(iterator position, Iterator first, Iterator last,
				typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0)
	{
		while (first != last)
		{
			this->insert(position, *first);
			++first;
		}
	}

	iterator	erase(iterator position)
	{
		//lol
	}

	iterator	erase(iterator first, iterator last)
	{
		//lol
	}

	void swap(deque & x)
	{
		//lol
	}

	void clear() {
		this->erase(this->begin(), this->end());
	}

	allocator_type	get_allocator() const {
		return this->m_alloc;
	}

private:
	void dequeInit()
	{
		this->m_chunk_size = (sizeof(T) <= 4) ? 64 : (sizeof(T) <= 8) ? 32 : (sizeof(T) <= 16) ? 16 : (sizeof(T) <= 32) ? 8 : 4;

		this->m_chunks = (this->size() / this->chunk_size()) + 1;
		this->m_map_size = ft::max<int>(8, this->m_chunks + 2);
		this->m_map = new pointer[this->m_map_size];
		map_pointer	tmp_start = this->m_map + ((this->m_map_size - this->m_chunks) / 2);
		map_pointer	tmp_finish = tmp_start + this->m_chunks - 1;

		for (map_pointer cur = tmp_start; cur <= tmp_finish; ++cur)
			*cur = new value_type[this->chunk_size()];

		this->m_start.setNode(tmp_start);
		this->m_start.m_cur = this->m_start.m_first;

		this->m_finish.setNode(tmp_finish);
		this->m_finish.m_cur = this->m_finish.m_first + (this->size() % this->chunk_size());
	}

	size_type	map_size() const {
		return this->m_map_size;
	}

	size_type	chunk_size() const {
		return this->m_chunk_size;
	}

};

template <class T, class Alloc>
bool operator==(deque<T, Alloc> const & lhs, deque<T, Alloc> const & rhs) {
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Alloc>
bool operator!=(deque<T, Alloc> const & lhs, deque<T, Alloc> const & rhs) {
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<(deque<T, Alloc> const & lhs, deque<T, Alloc> const & rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Alloc>
bool operator<=(deque<T, Alloc> const & lhs, deque<T, Alloc> const & rhs) {
	return !(rhs < lhs);
}

template <class T, class Alloc>
bool operator>(deque<T, Alloc> const & lhs, deque<T, Alloc> const & rhs) {
	return rhs < lhs;
}

template <class T, class Alloc>
bool operator>=(deque<T, Alloc> const & lhs, deque<T, Alloc> const & rhs) {
	return !(lhs < rhs);
}

template <class T, class Alloc>
void swap(deque<T, Alloc> & x, deque<T, Alloc> & y) {
	x.swap(y);
}

} //end of namespace ft

#endif

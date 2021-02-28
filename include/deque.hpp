#ifndef _FT_DEQUE_HPP
# define _FT_DEQUE_HPP

# include <cstddef>
# include <stdexcept>
# include "../src/_dequeIterator.hpp"
# include "algorithm.hpp"
# include "memory.hpp"

# define _FT_DEQUESIZ (sizeof(T) <= 4 ? 64 \
: sizeof(T) <= 8 ? 32                      \
: sizeof(T) <= 16 ? 16                     \
: sizeof(T) <= 32 ? 8 : 4)

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
	typedef ft::dequeIterator<value_type, _FT_DEQUESIZ>				iterator;
	typedef ft::constDequeIterator<value_type, _FT_DEQUESIZ>		const_iterator;
	typedef ft::reverse_iterator<iterator>							reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
	typedef std::ptrdiff_t											difference_type;
	typedef typename allocator_type::size_type						size_type;

private:
	typedef pointer*												map_pointer;
	typedef	typename allocator_type::template rebind<pointer>::other	chunk_allocator;

	iterator		m_start;		// iterator to the first element
	iterator		m_finish;		// iterator to one element past the end

	map_pointer		m_map;			// pointer to the array of chunks
	size_type		m_map_size;		// size of the array of chunks
	size_type		m_chunks;		// amount of chunks allocated
	size_type		m_size;			// number of elements

	allocator_type	m_alloc;

public:
	// 1. default constructor
	explicit deque(allocator_type const & alloc = allocator_type()):
		m_map(NULL),
		m_map_size(0),
		m_chunks(0),
		m_size(0),
		m_alloc(alloc) {
		this->dequeInit(0);
	}

	// 2. fill constructor
	explicit deque(size_type n, value_type const & val = value_type(), allocator_type const & alloc = allocator_type()):
		m_map(NULL),
		m_map_size(0),
		m_chunks(0),
		m_size(0),
		m_alloc(alloc) {
		this->dequeInit(n);
		this->assign(n, val);
	}

	// 3. range constructor
	template <class Iterator>
	deque(Iterator first, Iterator last, allocator_type const & alloc = allocator_type(),
		  typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0):
		m_map(NULL),
		m_map_size(0),
		m_chunks(0),
		m_size(0),
		m_alloc(alloc) {
		this->dequeInit(ft::distance(first, last));
		this->assign(first, last);
	}

	// 4. copy constructor
	deque(deque const & other):
		m_map(NULL),
		m_map_size(0),
		m_chunks(0),
		m_size(0),
		m_alloc(other.get_allocator()) {
		this->dequeInit(other.size());
		this->assign(other.begin(), other.end());
	}

	// destructor
	~deque() {
		chunk_allocator	chunk_alloc;

		for (iterator it = this->m_start; it != this->m_finish; ++it) {
			this->m_alloc.destroy(it.m_cur);
		}
		for (size_type i = 0; i < this->m_map_size; ++i) {
			chunk_alloc.destroy(this->m_map + i);
			this->m_alloc.deallocate(this->m_map[i], this->chunk_size());
		}
		chunk_alloc.deallocate(this->m_map, this->m_map_size);
	}

	// assignment operator overload
	deque&	operator=(deque const & rhs) {
		if (&rhs != this) {
			this->assign(rhs.begin(), rhs.end());
		}
		return *this;
	}

	iterator		begin() { return this->m_start; }
	const_iterator	begin() const { return this->m_start; }
	iterator		end() { return this->m_finish; }
	const_iterator	end() const { return this->m_finish; }

	reverse_iterator		rbegin() { return reverse_iterator(this->end()); }
	const_reverse_iterator  rbegin() const { return const_reverse_iterator(this->end()); }
	reverse_iterator 		rend() { return reverse_iterator(this->begin()); }
	const_reverse_iterator 	rend() const { return const_reverse_iterator(this->begin()); }

	size_type	size() const { return this->m_size; }
	size_type	max_size() const {
		return ft::min<size_type>(this->m_alloc.max_size(),
								  std::numeric_limits<difference_type>::max());
	}

	void resize(size_type n, value_type val = value_type()) {
		while (n < this->size()) this->pop_back();
		while (n > this->size()) this->push_back(val);
	}

	bool empty() const { return this->size() == 0; }

	reference 		operator[](size_type n) { return this->m_start[n]; }
	const_reference	operator[](size_type n) const { return this->m_start[n]; }

	reference 		at(size_type n) {
		if (n >= this->size()) throw std::out_of_range("deque");
		return this->m_start[n];
	}

	const_reference	at(size_type n) const {
		if (n >= this->size()) throw std::out_of_range("deque");
		return this->m_start[n];
	}

	reference 		front() { return *this->m_start; }
	const_reference	front() const { return *this->m_start; }

	reference 		back() {
		iterator	tmp = this->m_finish;
		--tmp;
		return *tmp;
	}

	const_reference	back() const {
		iterator	tmp = this->m_finish;
		--tmp;
		return *tmp;
	}

	// 1. range assign
	template <class Iterator>
	void assign(Iterator first, Iterator last,
				typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0) {
		this->clear();

		Iterator	middle = ft::next(first, ft::distance(first, last) / 2);
		while (middle != last) {
			this->push_back(*middle);
			++middle;
		}

		middle = ft::next(first, ft::distance(first, last) / 2);
		while (middle != first) {
			--middle;
			this->push_front(*middle);
		}
	}

	// 2. fill assign
	void assign(size_type n, value_type const & val) {
		this->clear();
		for (size_type i = 0; i < (n / 2) + (n % 2); ++i)
			this->push_back(val);
		for (size_type i = 0; i < n / 2; ++i)
			this->push_front(val);
	}

	void push_back(value_type const & val) {
		if (this->m_finish.m_cur + 1 == this->m_finish.m_last) {
			if (this->m_finish.m_node == this->m_map + this->m_map_size - 1) {
				this->realloc();
			}
			if (*(this->m_finish.m_node + 1) == NULL) {
				*(this->m_finish.m_node + 1) = this->m_alloc.allocate(this->chunk_size());
				++this->m_chunks;
			}
		}
		this->m_alloc.construct(this->m_finish.m_cur, val);
		++this->m_finish;
		++this->m_size;
	}

	void push_front(value_type const & val) {
		if (this->m_start.m_cur == this->m_start.m_first) {
			if (this->m_start.m_node == this->m_map) {
				this->realloc();
			}
			if (*(this->m_start.m_node - 1) == NULL) {
				*(this->m_start.m_node - 1) = this->m_alloc.allocate(this->chunk_size());
				++this->m_chunks;
			}
		}
		--this->m_start;
		this->m_alloc.construct(this->m_start.m_cur, val);
		++this->m_size;
	}

	void pop_back() {
		--this->m_finish;
		--this->m_size;
	}

	void pop_front() {
		++this->m_start;
		--this->m_size;
	}

	// 1. single element insertion
	iterator	insert(iterator position, value_type const & val) {
		this->insert(position, 1, val);
		return iterator(position);
	}

	// 2. fill insertion
	void insert(iterator position, size_type n, value_type const & val) {
		deque	tmp(position, this->end());
		while (position != this->end())
			this->pop_back();
		for (size_type i = 0; i < n; ++i)
			this->push_back(val);
		for (iterator it = tmp.begin(); it != tmp.end(); ++it)
			this->push_back(*it);
	}

	// 3. range insertion
	template <class Iterator>
	void insert(iterator position, Iterator first, Iterator last,
				typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0) {
		deque	tmp(position, this->end());
		while (position != this->end())
			this->pop_back();
		while (first != last) {
			this->push_back(*first);
			++first;
		}
		for (iterator it = tmp.begin(); it != tmp.end(); ++it)
			this->push_back(*it);
	}

	iterator	erase(iterator position) {
		return this->erase(position, position + 1);
	}

	iterator	erase(iterator first, iterator last) {
		deque	tmp(last, this->end());
		while (first != this->end())
			this->pop_back();
		for (iterator it = tmp.begin(); it != tmp.end(); ++it)
			this->push_back(*it);
		return first;
	}

	void swap(deque & x) {
		ft::swap(this->m_start, x.m_start);
		ft::swap(this->m_finish, x.m_finish);
		ft::swap(this->m_map, x.m_map);
		ft::swap(this->m_map_size, x.m_map_size);
		ft::swap(this->m_chunks, x.m_chunks);
		ft::swap(this->m_size, x.m_size);
		ft::swap(this->m_alloc, x.m_alloc);
	}

	void clear() {
		size_type n = this->size();
		while (n > this->size() / 2) {
			this->pop_back();
			--n;
		}

		while (this->begin() != this->end())
			this->pop_front();
	}

	allocator_type	get_allocator() const {
		return this->m_alloc;
	}

private:
	void dequeInit(size_type n) {
		chunk_allocator	chunk_alloc;

		this->m_chunks = (n / this->chunk_size()) + 1;
		this->m_map_size = ft::max<size_type>(8, this->m_chunks + 2);
		this->m_map = chunk_alloc.allocate(this->m_map_size);

		map_pointer	tmp_start = this->m_map + ((this->m_map_size - this->m_chunks) / 2);
		map_pointer	tmp_finish = tmp_start + this->m_chunks - 1;

		for (size_type i = 0; i < this->m_map_size; ++i) {
			pointer p = NULL;
			if (this->m_map + i >= tmp_start && this->m_map + i <= tmp_finish)
				p = this->m_alloc.allocate(this->chunk_size());
			chunk_alloc.construct(this->m_map + i, p);
		}

		this->m_start.setNode(this->m_map + ((this->m_map_size - 1) / 2));
		this->m_start.m_cur = this->m_start.m_first;
		this->m_finish.setNode(this->m_map + ((this->m_map_size - 1) / 2));
		this->m_finish.m_cur = this->m_finish.m_first;
	}

	void	realloc() {
		chunk_allocator	chunk_alloc;

		size_type	newMapSize = this->m_map_size + 4;
		map_pointer	newMap = chunk_alloc.allocate(newMapSize);

		map_pointer	tmp_start = newMap + ((newMapSize - this->m_chunks) / 2);

		map_pointer	old_start = this->m_start.m_node;
		map_pointer	old_finish = this->m_finish.m_node;

		size_type	offset = old_finish - old_start;

		map_pointer	tmp = old_start;
		for (size_type i = 0; i < newMapSize; ++i) {
			pointer p = NULL;
			if (newMap + i >= tmp_start && newMap + i <= tmp_start + offset) {
				p = *tmp;
				++tmp;
			}
			chunk_alloc.construct(newMap + i, p);
		}

		for (size_type i = 0; i < this->m_map_size; ++i)
			chunk_alloc.destroy(this->m_map + i);
		chunk_alloc.deallocate(this->m_map, this->m_map_size);

		this->m_map = newMap;
		this->m_map_size = newMapSize;

		offset = this->m_start.m_cur - this->m_start.m_first;

		this->m_start.setNode(tmp_start);
		this->m_start.m_cur = this->m_start.m_first + offset;

		this->m_finish = this->m_start + this->size();
	}

	size_type	chunk_size() const {
		return _FT_DEQUESIZ;
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

#ifndef _FT_VECTOR_HPP
# define _FT_VECTOR_HPP

# include <cstddef>
# include <stdexcept>
# include "algorithm.hpp"
# include "iterator.hpp"
# include "memory.hpp"
# include "type_traits.hpp"
# include "_ftl/_vectorIterator.hpp"

namespace ft
{

template <class T, class Alloc = ft::allocator<T> >
class vector
{
public:
	typedef	T															value_type;
	typedef	Alloc														allocator_type;
	typedef	typename allocator_type::reference							reference;
	typedef	typename allocator_type::const_reference					const_reference;
	typedef	typename allocator_type::pointer							pointer;
	typedef	typename allocator_type::const_pointer						const_pointer;
	typedef ft::vectorIterator<value_type>								iterator;
	typedef ft::constVectorIterator<value_type>							const_iterator;
	typedef ft::reverse_iterator<iterator>								reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
	typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
	typedef	typename allocator_type::size_type							size_type;

private:
	pointer	    	m_data;
	size_type		m_size;
	size_type		m_capacity;
	allocator_type	m_alloc;

public:
	// 1. default constructor
	explicit vector(allocator_type const & alloc = allocator_type()):
		m_data(NULL),
		m_size(0),
		m_capacity(0),
		m_alloc(alloc) {}

	// 2. fill constructor
	explicit vector(size_type n, value_type const & val = value_type(),
				 allocator_type const & alloc = allocator_type()):
		m_data(NULL),
		m_size(n),
		m_capacity(n),
		m_alloc(alloc) {
		this->m_data = this->get_allocator().allocate(n);
		for (size_type i = 0; i < this->size(); ++i)
			this->get_allocator().construct(this->m_data + i, val);
	}

	// 3. range constructor
	template <class Iterator>
	vector(Iterator first, Iterator last, allocator_type const & alloc = allocator_type(),
		   typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0):
		m_data(NULL),
		m_size(ft::distance(first, last)),
		m_capacity(ft::distance(first, last)),
		m_alloc(alloc) {
		this->m_data = this->get_allocator().allocate(this->capacity());
		for (size_type i = 0; i < this->size(); ++i)
		{
			this->get_allocator().construct(this->m_data + i, *first);
			++first;
		}
	}

	// 4. copy constructor
	vector(vector const & other):
		m_data(NULL),
		m_size(0),
		m_capacity(0),
		m_alloc(other.get_allocator()) {
		this->reserve(other.capacity());
		this->assign(other.begin(), other.end());
	}

	// destructor
	~vector() {
		for (size_type i = 0; i < this->size(); ++i)
			this->get_allocator().destroy(this->m_data + i);
		this->get_allocator().deallocate(this->m_data, this->capacity());
	}

	// assignment operator overload
	vector&	operator=(vector const & rhs)
	{
		if (&rhs != this)
		{
			this->clear();
			this->m_alloc = rhs.get_allocator();
			this->assign(rhs.begin(), rhs.end());
		}
		return *this;
	}

	iterator        begin() { return iterator(this->m_data); }
	const_iterator 	begin() const { return const_iterator(this->m_data); }
	iterator        end() { return iterator(this->m_data + this->size()); }
	const_iterator 	end() const { return const_iterator(this->m_data + this->size()); }

	reverse_iterator		rbegin() { return reverse_iterator(this->end()); }
	const_reverse_iterator  rbegin() const { return const_reverse_iterator(this->end()); }
	reverse_iterator 		rend() { return reverse_iterator(this->begin()); }
	const_reverse_iterator 	rend() const { return const_reverse_iterator(this->begin()); }

	size_type	size() const { return this->m_size; }
	size_type	max_size() const { return this->get_allocator().max_size(); }

	void		resize(size_type n, value_type val = value_type())
	{
		while (n < this->size())
			this->pop_back();
		while (n > this->size())
			this->push_back(val);
	}

	size_type		capacity() const { return this->m_capacity; }
	bool			empty() const { return (this->size() == 0); }
	void			reserve(size_type n) { if (n > this->capacity()) this->realloc(n); }
	reference		operator[](size_type n) { return *(this->m_data + n); }
	const_reference	operator[](size_type n) const { return *(this->m_data + n); }

	reference		at (size_type n)
	{
		if (n >= this->size()) throw std::out_of_range("vector");
		return *(this->m_data + n);
	}

	const_reference	at (size_type n) const
	{
		if (n >= this->size()) throw std::out_of_range("vector");
		return *(this->m_data + n);
	}

	reference   	front() { return *(this->m_data); }
	const_reference front() const { return *(this->m_data); }
	reference		back() { return *(this->m_data + this->size() - 1); }
	const_reference	back() const { return *(this->m_data + this->size() - 1); }

	// 1. range assign
	template <class Iterator>
	void	assign(Iterator first, Iterator last,
				   typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0)
	{
		this->clear();
		this->reserve(ft::distance(first, last));
		while (first != last)
		{
			this->push_back(*first);
			++first;
		}
	}

	// 2. fill assign
	void	assign(size_type n, value_type const & val)
	{
		this->clear();
		this->reserve(n);
		this->m_size = n;
		for (size_type i = 0; i < this->size(); ++i)
			this->get_allocator().construct(this->m_data + i, val);
	}

	void		push_back(value_type const & val)
	{
		if (this->size() >= this->capacity())
			this->realloc(this->capacity() * 2);
		this->get_allocator().construct(this->m_data + this->size(), val);
		++this->m_size;
	}

	void		pop_back()
	{
		--this->m_size;
		this->get_allocator().destroy(this->m_data + this->size());
	}

	// 1. single element insertion
	iterator    insert(iterator position, value_type const & val)
	{
		difference_type	pos = ft::distance(this->begin(), position);
		this->insert(position, 1, val);
		return iterator(this->m_data + pos);
	}

	// 2. fill insertion
	void        insert(iterator position, size_type n, value_type const & val)
	{
		vector	tmp(position, this->end());
		while (position != this->end())
			this->pop_back();
		for (size_type i = 0; i < n; ++i)
			this->push_back(val);
		for (iterator it = tmp.begin(); it != tmp.end(); ++it)
			this->push_back(*it);
	}

	// 3. range insertion
	template <class Iterator>
	void        insert(iterator position, Iterator first, Iterator last,
					   typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0)
	{
		vector	tmp(position, this->end());
		while (position != this->end())
			this->pop_back();
		while (first != last)
		{
			this->push_back(*first);
			++first;
		}
		for (iterator it = tmp.begin(); it != tmp.end(); ++it)
			this->push_back(*it);
	}

	// 1. erase single element
	iterator    erase(iterator position)
	{
		vector	tmp(position + 1, this->end());
		while (position != this->end())
			this->pop_back();
		for (iterator it = tmp.begin(); it != tmp.end(); ++it)
			this->push_back(*it);
		return position;
	}

	// 2. erase range of elements
	iterator    erase(iterator first, iterator last)
	{
		vector	tmp(last, this->end());
		while (first != this->end())
			this->pop_back();
		for (iterator it = tmp.begin(); it != tmp.end(); ++it)
			this->push_back(*it);
		return first;
	}

	void        swap(vector & x)
	{
		ft::swap(this->m_data, x.m_data);
		ft::swap(this->m_size, x.m_size);
		ft::swap(this->m_capacity, x.m_capacity);
		ft::swap(this->m_alloc, x.m_alloc);
	}

	void        clear()
	{
		iterator it = this->begin();
		while (it != this->end())
			this->pop_back();
	}

	allocator_type	get_allocator() const {
		return this->m_alloc;
	}

private:
	void		realloc(size_type newCapacity)
	{
		if (newCapacity == 0)
			newCapacity = 1;
		pointer	newBlock = this->get_allocator().allocate(newCapacity);
		for (size_type i = 0; i < this->size(); ++i)
		{
			this->get_allocator().construct(newBlock + i, this->m_data[i]);
			this->get_allocator().destroy(this->m_data + i);
		}
		this->get_allocator().deallocate(this->m_data, this->capacity());
		this->m_data = newBlock;
		this->m_capacity = newCapacity;
	}
};

template <class T, class Alloc>
bool operator==(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Alloc>
bool operator!=(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Alloc>
bool operator<=(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
	return !(rhs < lhs);
}

template <class T, class Alloc>
bool operator>(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
	return rhs < lhs;
}

template <class T, class Alloc>
bool operator>=(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
	return !(lhs < rhs);
}

template <class T, class Alloc>
void swap(vector<T,Alloc> & x, vector<T,Alloc> & y) {
	x.swap(y);
}

} //end of namespace ft

#endif

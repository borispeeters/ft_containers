#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <limits>
# include <memory>
# include <stdexcept>
# include "iterator.hpp"
# include "type_traits.hpp"

# include <iterator>

namespace ft
{

template <typename vector>
class vectorIterator : public std::iterator<ft::random_access_iterator_tag, typename vector::value_type>
{
public:
//	typedef typename ft::iterator_traits<vectorIterator<> >::value_type		value_type;
	typedef typename std::iterator_traits<vectorIterator>::difference_type	difference_type;
	typedef typename ft::iterator_traits<vectorIterator>::pointer			pointer;
	typedef typename ft::iterator_traits<vectorIterator>::reference			reference;
	typedef typename ft::iterator_traits<vectorIterator>::iterator_category	iterator_category;

//	typedef	typename vector::value_type		value_type;
//	typedef	std::ptrdiff_t					difference_type;
//	typedef	value_type*						pointer;
//	typedef value_type&						reference;
//	typedef std::random_access_iterator_tag	iterator_category;

private:
	pointer m_ptr;

public:
	vectorIterator(): m_ptr(0) {}
	vectorIterator(pointer ptr): m_ptr(ptr) {}
	vectorIterator(vectorIterator const & other): m_ptr(other.m_ptr) {}
	vectorIterator&	operator=(vectorIterator const & rhs)
	{
		if (&rhs != this)
			this->m_ptr = rhs.m_ptr;
		return *this;
	}
	~vectorIterator() {}

	vectorIterator& operator++()
	{
		++this->m_ptr;
		return *this;
	}
	vectorIterator  operator++(int)
	{
		vectorIterator  iterator = *this;
		++(*this);
		return iterator;
	}
	vectorIterator& operator--()
	{
		--this->m_ptr;
		return *this;
	}
	vectorIterator  operator--(int)
	{
		vectorIterator  iterator = *this;
		--(*this);
		return iterator;
	}
	vectorIterator&	operator+=(difference_type rhs)
	{
		this->m_ptr += rhs;
		return *this;
	}
	vectorIterator&	operator-=(difference_type rhs)
	{
		this->m_ptr -= rhs;
		return *this;
	}
	vectorIterator&	operator+=(vectorIterator const & rhs)
	{
		this->m_ptr += rhs.m_ptr;
		return *this;
	}
	vectorIterator&	operator-=(vectorIterator const & rhs)
	{
		this->m_ptr -= rhs.m_ptr;
		return *this;
	}
	friend	vectorIterator	operator+(vectorIterator const & lhs, vectorIterator const & rhs) { return vectorIterator(lhs.m_ptr + rhs.m_ptr); }
	friend	vectorIterator	operator+(vectorIterator const & lhs, difference_type rhs) { return vectorIterator(lhs.m_ptr + rhs); }
	friend	vectorIterator	operator+(difference_type lhs, vectorIterator const & rhs) { return vectorIterator(lhs + rhs.m_ptr); }
	friend	vectorIterator	operator-(vectorIterator const & lhs, vectorIterator const & rhs) { return vectorIterator(lhs.m_ptr - rhs.m_ptr); }
	friend	vectorIterator	operator-(vectorIterator const & lhs, difference_type rhs) { return vectorIterator(lhs.m_ptr - rhs); }
	friend	vectorIterator	operator-(difference_type lhs, vectorIterator const & rhs) { return vectorIterator(lhs - rhs.m_ptr); }
	reference	operator[](int index) { return *(this->m_ptr + index); }
	pointer		operator->() { return this->m_ptr; }
	reference	operator*() { return *this->m_ptr; }
	bool		operator==(vectorIterator const & rhs) const { return this->m_ptr == rhs.m_ptr; }
	bool 		operator!=(vectorIterator const & rhs) const { return !(*this == rhs); }
	bool 		operator<(vectorIterator const & rhs) { return this->m_ptr < rhs.m_ptr; }
	bool 		operator>(vectorIterator const & rhs) { return rhs < *this; }
	bool 		operator<=(vectorIterator const & rhs) { return !(rhs < *this); }
	bool 		operator>=(vectorIterator const & rhs) { return !(*this < rhs); }
};

template <class T, class Alloc = std::allocator<T> >
class vector
{
public:
	typedef	T															value_type;
	typedef	Alloc														allocator_type;
	typedef	typename allocator_type::reference							reference;
	typedef	typename allocator_type::const_reference					const_reference;
	typedef	typename allocator_type::pointer							pointer;
	typedef	typename allocator_type::const_pointer						const_pointer;
	typedef ft::vectorIterator<vector<T> >								iterator;
	typedef ft::vectorIterator<vector<const T> >						const_iterator;
	typedef std::reverse_iterator<iterator>								reverse_iterator;
	typedef std::reverse_iterator<const_iterator>						const_reverse_iterator;
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
		m_data(0),
		m_size(0),
		m_capacity(0)
	{}
	// 2. fill constructor
	explicit vector(size_type n, value_type const & val = value_type(),
				 allocator_type const & alloc = allocator_type()):
		m_data(0),
		m_size(n),
		m_capacity(n)
	{
		this->m_data = this->get_allocator().allocate(n);
		for (size_type i = 0; i < this->size(); ++i)
			this->get_allocator().construct(this->m_data + i, val);
	}
	// 3. range constructor
	template <class Iterator>
	vector(Iterator first, Iterator last, allocator_type const & alloc = allocator_type(),
		   typename ft::enable_if<ft::is_iterator<typename Iterator::iterator_category>::value, Iterator>::type * = 0):
		m_data(0),
		m_size(ft::distance(first, last)),
		m_capacity(ft::distance(first, last))
	{
		this->m_data = this->get_allocator().allocate(this->capacity());
		for (size_type i = 0; i < this->size(); ++i)
		{
			this->get_allocator().construct(this->m_data + i, *first);
			++first;
		}
	}
	// 4. copy constructor
	vector(vector const & vec):
		m_data(0),
		m_size(vec.size()),
		m_capacity(vec.capacity())
	{
		this->m_data = this->get_allocator().allocate(this->capacity());
		for (size_type i = 0; i < this->size(); ++i)
			this->get_allocator().construct(this->m_data + i, vec.at(i));
	}
	// destructor
	~vector()
	{
		for (size_type i = 0; i < this->size(); ++i)
			this->get_allocator().destroy(this->m_data + i);
		this->get_allocator().deallocate(this->m_data, this->capacity());
	}
	// assignment operator overload
	vector&	operator=(vector const & vec)
	{
		if (&vec != this)
		{
			this->clear();
			this->m_size = vec.size();
			this->m_capacity = vec.capacity();
			for (size_type i = 0; i < this->size(); ++i)
				this->get_allocator().construct(this->m_data + i, vec.at(i));
		}
		return *this;
	}

	iterator        	begin() { return iterator(this->m_data); }
	const_iterator 		begin() const { return const_iterator(this->m_data); }
	iterator        	end() { return iterator(this->m_data + this->size()); }
	const_iterator 		end() const { return const_iterator(this->m_data + this->size()); }

	reverse_iterator		rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator  rbegin() const { return const_reverse_iterator(end()); }
	reverse_iterator 		rend() { return reverse_iterator(begin()); }
	const_reverse_iterator 	rend() const { return const_reverse_iterator(begin()); }

	size_type	size() const { return this->m_size; }
//	size_type	max_size() const { return std::numeric_limits<size_type>::max() / sizeof(value_type); }
	size_type	max_size() const { return m_alloc.max_size(); }
	void		resize(size_type n, value_type val = value_type()) 
	{
		while (this->m_capacity < n)
			this->realloc(this->capacity() * 2);
		if (n > this->size())
		{
			for (size_type i = this->size(); i < n; ++i)
				this->get_allocator().construct(this->m_data + i, val);
		}
		this->m_size = n;
	}
	size_type		capacity() const { return this->m_capacity; }
	bool			empty() const { return (this->size() == 0); }
	void			reserve(size_type n) { if (n > this->capacity()) this->realloc(n); }
	reference		operator[](size_type n) { return *(this->m_data + n); }
	const_reference	operator[](size_type n) const { return *(this->m_data + n); }
	reference		at (size_type n)
	{
		if (n < 0 || n >= this->size())
			throw std::out_of_range("lol");
		return *(this->m_data + n);
	}
	const_reference	at (size_type n) const
	{
		if (n < 0 || n >= this->size())
			throw std::out_of_range("lol");
		return *(this->m_data + n);
	}
	reference   	front() { return *(this->m_data); }
	const_reference front() const { return *(this->m_data); }
	reference		back() { return *(this->m_data + this->size() - 1); }
	const_reference	back() const { return *(this->m_data + this->size() - 1); }
	// 1. range assign
	template <class Iterator>
	void	assign(Iterator first, Iterator last,
			 typename ft::enable_if<ft::is_iterator<typename ft::iterator_traits<Iterator>::iterator_category>::value, Iterator>::type * = 0)
	{
		this->clear();
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
		while (this->capacity() < n)
			this->realloc(this->capacity() * 2);
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
	// 1. insert single element
	iterator    insert(iterator position, value_type const & val)
	{
		if (++this->m_size > this->capacity())
			this->realloc(this->capacity() * 2);
		for (iterator it = this->end(); it != position; --it)
			*it = *(it - 1);
		this->get_allocator().construct(position, val);
		return position;
	}
	// 2. fill
	void        insert(iterator position, size_type n, value_type const & val)
	{
		this->m_size += n;
		while (this->capacity() < this->size())
			this->realloc(this->capacity() * 2);

		iterator it;
		for (it = position + n; it != this->end(); ++it)
		{
			this->get_allocator().construct(it, *(it - n));
			this->get_allocator().destroy(it - n);
		}
		for (it = position; it != position + n; ++it)
			this->get_allocator().construct(it, val);
	}
	// 3. range
//	template <class InputIterator>
//	void        insert(iterator position, InputIterator first, InputIterator last);
	iterator    erase(iterator position)
	{
		this->get_allocator().destroy(position);
		for (iterator it = position; it + 1 != this->end(); ++it)
		{
			this->get_allocator().construct(it, *(it + 1));
			this->get_allocator().destroy(it + 1);
		}
		--this->m_size;
	}
	iterator    erase(iterator first, iterator last)
	{
		for (iterator it = first; it != last; ++it)
			this->get_allocator().destroy(it);
		for (iterator it = first; it + ft::distance(first, last) != this->end(); ++it)
		{
			this->get_allocator().construct(it, *(it + ft::distance(first, last)));
			this->get_allocator().destroy(it + ft::distance(first, last));
		}
		this->m_size -= ft::distance(first, last);
	}
	void        swap(vector & vec)
	{
		vector	tmp(vec);
		vec = *this;
		*this = tmp;
	}
	void        clear()
	{
		for (size_type i = 0; i < this->size(); ++i)
			this->get_allocator().destroy(this->m_data + i);
		this->m_size = 0;
	}
	allocator_type	get_allocator() const { return this->m_alloc; }
private:
	void		realloc(size_type newCapacity)
	{
		if (newCapacity == 0)
			newCapacity = 1;
		pointer	newBlock = this->get_allocator().allocate(newCapacity, this->m_data);

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
void swap(vector<T,Alloc>& x, vector<T,Alloc>& y) {	x.swap(y); }

}; //end of namespace ft

#endif

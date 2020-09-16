#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iterator>
# include <limits>
# include <memory>
# include <stdexcept>

namespace ft
{

//template <typename vector>
//class vectorIterator : public std::iterator<std::random_access_iterator_tag, typename vector::value_type, ptrdiff_t, typename vector::pointer, typename vector::reference>
//{
//public:
//    typedef	typename vector::value_type		value_type;
//    typedef	typename vector::pointer		pointer;
//    typedef typename vector::reference		reference;
////    typedef std::random_access_iterator_tag	iterator_category;
//
//    vectorIterator(pointer ptr): m_ptr(ptr) {}
//
//    vectorIterator& operator++()
//    {
//        ++m_ptr;
//        return *this;
//    }
//    vectorIterator  operator++(int)
//    {
//        vectorIterator  iterator = *this;
//        ++(*this);
//        return iterator;
//    }
//    vectorIterator& operator--()
//    {
//        --m_ptr;
//        return *this;
//    }
//    vectorIterator  operator--(int)
//    {
//    	vectorIterator  iterator = *this;
//        --(*this);
//        return iterator;
//    }
//    reference	operator[](int index) { return *(m_ptr + index); }
//    pointer		operator->() { return m_ptr; }
//    reference	operator*() { return *m_ptr; }
//    bool		operator==(vectorIterator const & other) const { return m_ptr == other.m_ptr; }
//    bool 		operator!=(vectorIterator const & other) const { return !(*this == other); }
//private:
//    pointer m_ptr;
//};

template <class T, class Alloc = std::allocator<T> >
class vector
{
public:
	typedef	T											value_type;
	typedef	Alloc										allocator_type;
	typedef	typename allocator_type::reference			reference;
	typedef	typename allocator_type::const_reference	const_reference;
	typedef	typename allocator_type::pointer			pointer;
	typedef	typename allocator_type::const_pointer		const_pointer;
//	typedef vectorIterator<vector<T> >					iterator;
	typedef pointer										iterator;
  	typedef const_pointer 								const_iterator;
    typedef std::reverse_iterator<iterator>             reverse_iterator;
    typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;
    typedef typename allocator_type::difference_type	difference_type;
	typedef	typename allocator_type::size_type			size_type;

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
//	template <class InputIterator>
//	vector(InputIterator first, InputIterator last, allocator_type const & alloc = allocator_type()) {}
	// 4. copy constructor
	vector(vector const & vec):
	    m_data(vec.m_data),
	    m_size(vec.size()),
	    m_capacity(vec.capacity())
	{}
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
		    this->m_data = vec.m_data;
		    this->m_size = vec.size();
		    this->m_capacity = vec.capacity();
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
    template <class InputIterator>
    void        assign(InputIterator first, InputIterator last)
	{
		this->clear();
		while (first != last)
		{
			this->push_back(*first);
			++first;
		}
	}
    // 2. fill assign
    void        assign(size_type n, value_type const & val)
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
//	// 2. fill
	void        insert(iterator position, size_type n, value_type const & val)
	{
		this->m_size += n;
		while (this->capacity() < this->size())
			this->realloc(this->capacity() * 2);

		iterator it;
		for (it = this->end(); it != position + n; --it)
		{
			std::cout << "*(it - 1): " << *(it - 1) << std::endl;
			*it = *(it - 1);
		}
		for (it = position; it != position + n; ++it)
			this->get_allocator().construct(it, val);
	}
//	// 3. range
//	template <class InputIterator>
//	void        insert(iterator position, InputIterator first, InputIterator last);
//	iterator    erase(iterator position);
//	iterator    erase(iterator first, iterator last);
//	void        swap(vector & vec);
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
	pointer	    	m_data;
	size_type		m_size;
	size_type		m_capacity;
	allocator_type	m_alloc;
};

template <class T, class Alloc>
void swap(vector<T,Alloc>& x, vector<T,Alloc>& y);

}; //end of namespace ft

#endif

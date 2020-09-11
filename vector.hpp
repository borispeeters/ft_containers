#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <limits>
# include <memory>

namespace ft
{

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
	typedef	typename allocator_type::size_type			size_type;

	vector():
		m_data(0),
		m_size(0),
		m_capacity(0)
	{}
	~vector() {}
	vector(vector const & vec):
	    m_data(vec.m_data),
	    m_size(vec.size()),
	    m_capacity(vec.capacity())
	{}
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

	size_type	size() const { return this->m_size; }
	size_type	max_size() const { return std::numeric_limits<size_type>::max() / sizeof(value_type); }
	void		resize(size_type n, value_type val = value_type()) 
	{
		(void)val;
		while (this->m_capacity < n)
			this->realloc(this->m_capacity * 2);
	}
	size_type	capacity() const { return this->m_capacity; }
	bool		empty() const { return (this->size() == 0); }
	void		reserve(size_type n) { (void)n; }
	void		push_back(value_type const & val)
	{
		if (this->m_size >= this->m_capacity)
		{
			if (this->m_capacity == 0) this->realloc(1);
			else this->realloc(this->m_capacity * 2);
		}
		this->m_data[this->m_size++] = val;
	}
	void		pop_back()
	{
		--this->m_size;
	}
	reference	back()
	{
		return this->m_data[this->size() - 1];
	}
	const_reference	back() const
	{
		return this->m_data[this->size() - 1];
	}
	reference	operator[](size_type index)
	{
		return this->m_data[index];
	}
	const_reference	operator[](size_type index) const
	{
		return this->m_data[index];
	}
private:
	void		realloc(size_type newCapacity)
	{
		pointer newBlock = new value_type[newCapacity];

		for (size_type i = 0; i < this->size(); ++i)
			newBlock[i] = this->m_data[i];
		
		delete[] this->m_data;
		this->m_data = newBlock;
		this->m_capacity = newCapacity;
	}
	pointer	    m_data;
	size_type	m_size;
	size_type	m_capacity;
};

}; //end of namespace ft

#endif

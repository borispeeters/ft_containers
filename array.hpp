#ifndef ARRAY
# define ARRAY

# include <cstddef>
# include <stdexcept>

namespace ft
{

template <class T, std::size_t N>
class array
{
public:
	typedef T										value_type;
	typedef value_type&								reference;
	typedef const value_type&						const_reference;
	typedef value_type*								pointer;
	typedef const value_type*						const_pointer;
//	typedef lol										iterator;
//	typedef ft::reverse_iterator<iterator>			reverse_iterator;
//	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
	typedef std::size_t								size_type;
	typedef std::ptrdiff_t							difference_type;

private:
	pointer 	m_array[N];

public:
	// implicitly declared
//	explicit array() {}
//	array(array const & other);
//	array&	operator=(array const & rhs);
//	~array();

	iterator		begin();
	const_iterator	begin() const;
	iterator		end();
	const_iterator	end() const;

	reverse_iterator		rbegin();
	const_reverse_iterator	rbegin() const;
	reverse_iterator		rend();
	const_reverse_iterator	rend() const;

	size_type	size() const { return this->m_size; }
	size_type	max_size() const;
	bool 		empty() const { return this->size() == 0; }

	reference 		operator[](size_type n) { return *(this->m_array + n); }
	const_reference	operator[](size_type n) const { return *(this->m_array + n); }
	reference 		at(size_type n)
	{
		if (n >= N) throw std::out_of_range("array");
		return *(this->m_array + n);
	}
	const_reference	at(size_type n) const
	{
		if (n >= N) throw std::out_of_range("array");
		return *(this->m_array + n);
	}

	reference		front() { return *(this->m_array); }
	const_reference	front() const { return *(this->m_array); }
	reference 		back() { return *(this->m_array + N - 1); }
	const_reference	back() const { return *(this->m_array + N - 1); }

	pointer 		data();
	const_pointer	data() const;

	void fill(value_type const & val);
};

};

#endif

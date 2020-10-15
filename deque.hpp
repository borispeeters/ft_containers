#ifndef DEQUE_HPP
# define DEQUE_HPP

# include <memory>

namespace ft
{

template <class T, class Alloc = std::allocator<T> >
class deque
{
public:
	typedef T														value_type;
	typedef Alloc													allocator_type;
	typedef typename allocator_type::reference						reference;
	typedef typename allocator_type::const_reference				const_reference;
	typedef typename allocator_type::pointer						pointer;
	typedef typename allocator_type::const_pointer					const_pointer;
//	typedef lol														iterator;
//	typedef const lol												const_iterator;
//	typedef ft::reverse_iterator<iterator>								reverse_iterator;
//	typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
//	typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
	typedef typename allocator_type::size_type						size_type;

private:
	// variables

public:
	// 1. default constructor
	explicit deque(allocator_type const & alloc = allocator_type());

	// 2. fill constructor
	explicit deque(size_type n, value_type const & val = value_type(), allocator_type const & alloc = allocator_type());

	// 3. range constructor
	template <class Iterator>
	deque(Iterator first, Iterator last, allocator_type const & alloc = allocator_type());

	// 4. copy constructor
	deque(deque const & other);

	// destructor
	~deque();

	// assignment operator overload
	deque&	operator=(deque const & rhs);

	iterator		begin();
	const_iterator	begin() const;
	iterator		end();
	const_iterator	end() const;

	reverse_iterator		rbegin();
	const_reverse_iterator	rbegin() const;
	reverse_iterator		rend();
	const_reverse_iterator	rend() const;

	size_type	size() const;
	size_type	max_size() const;

	void resize(size_type n, value_type val = value_type());

	bool empty() const { return this->size() == 0; }

	reference 		operator[](size_type n);
	const_reference	operator[](size_type n) const;
	reference 		at(size_type n);
	const_reference	at(size_type n) const;

	reference 		front();
	const_reference	front() const;
	reference 		back();
	const_reference	back() const;

	// 1. range assign
	template <class Iterator>
	void assign(Iterator first, Iterator last);

	// 2. fill assign
	void assign(size_type n, value_type const & val);

	void push_back(value_type const & val);
	void push_front(value_type const & val);
	void pop_back();
	void pop_front();

	// 1. single element insertion
	iterator	insert(iterator position, value_type const & val);

	// 2. fill insertion
	void insert(iterator position, size_type n, value_type const & val);

	// 3. range insertion
	template <class Iterator>
	void insert(iterator position, Iterator first, Iterator last);

	iterator	erase(iterator position);
	iterator	erase(iterator first, iterator last);

	void swap(deque & x)
	{
		deque	tmp(x);
		x = *this;
		*this = tmp;
	}

	void clear();

	allocator_type	get_allocator() const;

};

template <class T, class Alloc>
bool operator==(deque<T, Alloc> const & lhs, deque<T, Alloc> const & rhs);

template <class T, class Alloc>
bool operator!=(deque<T, Alloc> const & lhs, deque<T, Alloc> const & rhs) { return !(lhs == rhs); }

template <class T, class Alloc>
bool operator<(deque<T, Alloc> const & lhs, deque<T, Alloc> const & rhs);

template <class T, class Alloc>
bool operator<=(deque<T, Alloc> const & lhs, deque<T, Alloc> const & rhs) { return !(rhs < lhs); }

template <class T, class Alloc>
bool operator>(deque<T, Alloc> const & lhs, deque<T, Alloc> const & rhs) { return rhs < lhs; }

template <class T, class Alloc>
bool operator>=(deque<T, Alloc> const & lhs, deque<T, Alloc> const & rhs) { return !(lhs < rhs); }

template <class T, class Alloc>
void swap(deque<T, Alloc> & x, deque<T, Alloc> & y) { x.swap(y); }

};

#endif

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>

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
//	typedef ft::listIterator<value_type>								iterator;
//	typedef ft::listIterator<const value_type>							const_iterator;
//	typedef std::reverse_iterator<iterator>								reverse_iterator;
//	typedef std::reverse_iterator<const_iterator>						const_reverse_iterator;
//	typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
	typedef	typename allocator_type::size_type							size_type;

private:
	size_type		m_size;
	allocator_type	m_alloc;
public:
	// 1. default constructor
	explicit list(allocator_type const & alloc = allocator_type());
	// 2. fill constructor
	explicit list(size_type n, value_type const & val = value_type(),
			   allocator_type const & alloc = allocator_type());
	// 3. range constructor
	template <class Iterator>
	list(Iterator first, Iterator last,
	  allocator_type const & alloc = allocator_type());
	// 4. copy constructor
	list(list const & other);
	// destructor
	~list();
	// assignment operator overload
	list&	operator=(list const & other);

	iterator		begin();
	const_iterator	begin() const;
	iterator		end();
	const_iterator	end() const;

	reverse_iterator		rbegin();
	const_reverse_iterator	rbegin() const;
	reverse_iterator		rend();
	const_reverse_iterator	rend() const;

	bool 		empty() const;
	size_type	size() const;
	size_type	max_size() const;

	reference 		front();
	const_reference	front() const;
	reference 		back();
	const_reference	back() const;

	// 1. range assign
	template <class Iterator>
	void assign(Iterator first, Iterator last);
	// 2. fill assign
	void assign(size_type n, value_type const & val);

	void push_front(value_type const & val);
	void pop_front();
	void push_back(value_type const & val);
	void pop_back();

	// 1. single element insertion
	iterator	insert(iterator position, value_type const & val);
	// 2. fill insertion
	void 		insert(iterator position, size_type n, value_type const & val);
	// 3. range insertion
	template <class Iterator>
	void 		insert(iterator position, Iterator first, Iterator last);

	// 1. erase single element
	iterator	erase(iterator position);
	// 2. erase range of elements
	iterator	erase(iterator first, iterator last);

	void 	swap(list & other)
	{
		list	tmp(other);
		other = *this;
		*this = tmp;
	}

	void resize(size_type n, value_type val = value_type());
	void clear();

	// 1. splice entire list
	void splice(iterator position, list & other);
	// 2. splice single element
	void splice(iterator position, list & other, iterator i);
	// 3. splice range of elements
	void splice(iterator position, list & other, iterator first, iterator last);

	void remove(value_type const & val);

	template <class Predicate>
	void remove_if(Predicate pred);

	void unique();
	template <class BinaryPredicate>
	void unique(BinaryPredicate binary_pred);

	void merge(list & other);
	template <class Compare>
	void merge(list & other, Compare comp);

	void sort();
	template <class Compare>
	void sort(Compare comp);

	void reverse();

	allocator_type	get_allocator() const { return this->m_alloc; }
};

}; //end of namespace ft

#endif

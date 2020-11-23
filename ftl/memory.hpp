#ifndef _FT_MEMORY_HPP
# define _FT_MEMORY_HPP

# include <cstddef>
# include <limits>
# include <new>

namespace ft
{

template<class T>
class allocator
{
public:
	typedef T	value_type;
	typedef T*	pointer;
	typedef T&	reference;
	typedef const T*	const_pointer;
	typedef const T&	const_reference;
	typedef std::size_t	size_type;
	typedef std::ptrdiff_t	difference_type;

	template <class Type>
	struct rebind {
		typedef ft::allocator<Type>	other;
	};

	// 1. default constructor
	allocator() throw() {}

	// 2. copy constructors
	allocator(allocator const & alloc) throw() {
		(void) alloc;
	}

	template <class U>
	allocator(allocator<U> const & alloc) throw() {
		(void) alloc;
	}

	// destructor
	~allocator() throw() {}

	// assignment operator overload
	allocator&	operator=(allocator const & rhs)
	{
		(void) rhs;
		return *this;
	}

	pointer 		address(reference x) const { return &x; }
	const_pointer	address(const_reference x) const { return &x; }

	pointer allocate(size_type n) {
		return (pointer) ::operator new(sizeof(value_type) * n);
	}

	void deallocate(pointer p, size_type n) {
		(void) n;
		::operator delete(p);
	}

	size_type	max_size() const throw() {
		return std::numeric_limits<size_type>::max() / sizeof(value_type);
	}

	void construct(pointer p, const_reference val) {
		new (p) value_type(val);
	}

	void destroy(pointer p) {
		p->~value_type();
	}
};

template <>
class allocator<void>
{
public:
	typedef void*		pointer;
	typedef const void*	const_pointer;
	typedef void		value_type;

	template <class U>
	struct rebind {
		typedef ft::allocator<U> other;
	};
};

} //end of namespace ft

#endif

#ifndef TREE_HPP
# define TREE_HPP

# include <functional>
# include <memory>

namespace ft
{

template <class Key,
		class T,
		class Compare,
		class Alloc
		>
class tree
{
	typedef Compare										key_compare;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef typename allocator_type::size_type			size_type;
};

}; //end of namespace ft

#endif

#include <cstddef>
#include <iostream>
#include "Example.hpp"

#include <memory>
#include "memory.hpp"

void*	operator new(std::size_t s) throw (std::bad_alloc)
{
	void	*ptr = malloc(s);

	if (!ptr)
		throw std::bad_alloc();

	std::cout << "allocated " << s << " bytes to " << ptr << std::endl;

	return ptr;
}

void 	operator delete(void *ptr) throw()
{
	std::cout << "deallocating " << ptr << std::endl;
	free(ptr);
}

int main()
{
	Example	*x;

	ft::allocator<Example>	alloc;

	x = alloc.allocate(1);

	alloc.construct(x, Example());

	alloc.destroy(x);

	alloc.deallocate(x, 1);

	return 0;
}




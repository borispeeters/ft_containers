#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <new>

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

#include <cstddef>
#include <iostream>
//#include <new>
#include "Example.hpp"

#include <memory>

void*	operator new(std::size_t s) throw (std::bad_alloc)
{

	void	*ptr = malloc(s);

	std::cout << "allocated " << s << " bytes to " << ptr << std::endl;

	if (!ptr)
		throw std::bad_alloc();

	return ptr;
}

//void* operator new (std::size_t size, void* ptr) throw()
//{
//
//}

void 	operator delete(void *ptr) throw()
{
	std::cout << "deleting " << ptr << std::endl;
	free(ptr);
}

int main()
{
	std::allocator<Example>	alloc;

	Example	*x = alloc.allocate(1);

	alloc.construct(x, std::move(Example()));

//	alloc.destroy(x);

	return 0;


	Example	*a = new Example;

	Example *b;
	b = (Example*) ::operator new(sizeof(Example) );
	b = new (b) Example;

	Example	*c = new Example(*a);

	delete a;

	::operator delete (b, b);
//	::operator delete(b);

	delete c;

//	a = new Example;
//	b = new Example;
//	c = new Example;

	return 0;
}




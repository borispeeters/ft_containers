#include "Example.hpp"

Example::Example() {
	std::cout << "Constructor"<< std::endl;
}

Example::Example(Example const & other) {
	std::cout << "Copy Constructor" << std::endl;
}

Example::~Example() {
	std::cout << "Destructor" << std::endl;
}

Example&	Example::operator=(Example const & rhs) {
	std::cout << "Assignment Operator" << std::endl;
	return *this;
}

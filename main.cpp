#include <iostream>
#include <vector>
#include "list.hpp"
#include "vector.hpp"

int main()
{
    ft::vector<int> vc;
    ft::list<int> li;

    std::cout << vc.max_size() << std::endl;
    return 0;
}

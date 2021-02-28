cmake_minimum_required(VERSION 3.19.3)

set(CMAKE_CXX_COMPILER "clang++")
set (CMAKE_CXX_FLAGS "-Wall -Werror -Wextra")

project(ft_containers)

add_executable(vector tests/vectorTest.cpp include/vector.hpp)
target_include_directories(vector PRIVATE include)

add_executable(list tests/listTest.cpp include/list.hpp)
target_include_directories(list PRIVATE include)

add_executable(stack tests/stackTest.cpp include/stack.hpp)
target_include_directories(stack PRIVATE include)

add_executable(queue tests/queueTest.cpp include/queue.hpp)
target_include_directories(queue PRIVATE include)

add_executable(set tests/setTest.cpp include/set.hpp)
target_include_directories(set PRIVATE include)

add_executable(multiset tests/multisetTest.cpp include/set.hpp)
target_include_directories(multiset PRIVATE include)

add_executable(map tests/mapTest.cpp include/map.hpp)
target_include_directories(map PRIVATE include)

add_executable(multimap tests/multimapTest.cpp include/map.hpp)
target_include_directories(multimap PRIVATE include)

add_executable(deque tests/dequeTest.cpp include/deque.hpp)
target_include_directories(deque PRIVATE include)

enable_testing()

add_test(NAME vector COMMAND vector)
add_test(NAME list COMMAND list)
add_test(NAME stack COMMAND stack)
add_test(NAME queue COMMAND queue)
add_test(NAME set COMMAND set)
add_test(NAME multiset COMMAND multiset)
add_test(NAME map COMMAND map)
add_test(NAME multimap COMMAND multimap)
add_test(NAME deque COMMAND deque)

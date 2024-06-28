#ifndef _MYALLOCATOR_H_
#define _MYALLOCATOR_H_
#include <vector>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
#include <stdexcept>
#include <new>
#include <cassert>

using namespace std;
template <class T>
class MyAllocator
{
public:
    using value_type = T;
    // Default constructor
    MyAllocator() {}
    ~MyAllocator() {}
    // Copy constructor
    MyAllocator(const MyAllocator &other) noexcept = default;
    // Allocate a space of size n
    T *allocate(size_t n);
    // Deallocate the space of the pointer
    void deallocate(T *p, size_t n);

private:
    static T *alloc_from_memory_pool(size_t size);
    static bool refill_memory_pool();
    // Max size of a mem pool
    static size_t max_size;        
    static vector<void *> memory_pool_table;        
    // Memory pool list
    static void *current_pool;                      
    static size_t pool_size;
    static size_t pool_ptr;
    // The list of freed lists
    static vector<vector<void *>> free_lists; 
};

#endif

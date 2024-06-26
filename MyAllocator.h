#include<vector>
#include<cstdlib>
#include <iostream>

template<class T>
class MyAllocator{
public:
    using value_type = T;

    MyAllocator() = default;
    ~MyAllocator() = default;
    MyAllocator(const MyAllocator& other) noexcept = default;  // rebind
    T* allocate(std::size_t n);               // Allocate a space of size n
    void deallocate(T* p, std::size_t n);     // Deallocate the space of the pointer
private:
    static T* alloc_from_memory_pool(size_t size);
    static bool refill_memory_pool();
    static constexpr size_t max_size = 2048;      // Max size of a mem pool
    static std::vector<void*> memory_pool_table;   // Several memory pool of different size are implemented
    static void* current_pool;                     // Memory pool list
    static constexpr std::size_t pool_size = 4096 * 1024; //4MB
    static std::size_t pool_ptr;
    static std::vector<std::vector<void*>> free_lists;   // The list of freed lists
};







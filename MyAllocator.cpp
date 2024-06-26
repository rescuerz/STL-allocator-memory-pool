#include "MyAllocator.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdexcept>
#include <new>
#include <cassert>


// Static member initialization
template<class T>
void* MyAllocator<T>::current_pool = ::operator new(MyAllocator<T>::pool_size);

// Static member initialization
template<class T>
std::vector<void*> MyAllocator<T>::memory_pool_table = { MyAllocator<T>::current_pool };

// Static member initialization
template<class T>
std::size_t MyAllocator<T>::pool_ptr = 0;

// Static member initialization
template<class T>
typename std::vector<std::vector<void*>> MyAllocator<T>::free_lists{11, std::vector<void*>{}};

/**
 * allocate() : Allocate memory for n objects of type T
 * @tparam T value type
 * @param n size to allocate
 * @return the pointer to the space allocated
 */
template<class T>
T* MyAllocator<T>::allocate(std::size_t n) {
    std::size_t total_size = sizeof(T) * n; // Total size required
    if (total_size > MyAllocator<T>::max_size) {
        return static_cast<T*>(::operator new(total_size));   // If size exceeds max_size, use default new
    }
    size_t list_id = 0;
    size_t size_ = 4;
    while(size_ < total_size){  // Find appropriate free list
        size_ = size_ << 1;
        list_id++;
    }
    if(!free_lists[list_id].empty()){   // Use a block from the free list if available
        auto result = free_lists[list_id].back();
        free_lists[list_id].pop_back();
        return static_cast<T*>(result);
    }
    return MyAllocator<T>::alloc_from_memory_pool(size_);  // Allocate from memory pool if no free block
}

/**
 * alloc_from_memory_pool : Allocate memory from the current memory pool
 * @tparam T value type
 * @param size the size to allocate from the mem pool
 * @return the space
 */
template<class T>
T* MyAllocator<T>::alloc_from_memory_pool(std::size_t size) {
    if (pool_ptr + size <= pool_size) {  // Check if there is enough space in the pool
        char* ptr = static_cast<char*>(current_pool) + pool_ptr;
        pool_ptr += size; // Update pool pointer
        return reinterpret_cast<T*>(ptr);
    } else {
        refill_memory_pool();    // Refill memory pool if not enough space
        return alloc_from_memory_pool(size);   // Try again after refilling
    }
}

/**
 * refill_memory_pool : Refill the memory pool by allocating a new block
 * @tparam T value type
 * @return true - success
 */
template<class T>
bool MyAllocator<T>::refill_memory_pool() {
    current_pool = ::operator new(pool_size);    // Allocate new memory pool
    if (current_pool == nullptr) {
        throw std::bad_alloc();    // Throw exception if allocation fails
    }
    pool_ptr = 0; // Reset pool pointer
    memory_pool_table.push_back(current_pool);    // Add new pool to the table
    return true;
}

/**
 * deallocate():Deallocate memory for n objects of type T
 * @tparam T value type
 * @param p pointer to the victim space
 * @param n size of the victim space
 */
template<class T>
void MyAllocator<T>::deallocate(T* p, std::size_t n) {
    size_t total_size = n * sizeof(T);   // Calculate total size
    if (total_size > max_size) {    // If size exceeds max_size, use default delete
        ::operator delete(p);
    } else if (total_size <= 2048) {    // If size is small, return to the free list
        size_t list_id = 0;
        size_t size_ = 4;
        while(size_ < total_size){    // Find appropriate free list
            size_ <<= 1;
            list_id++;
        }
        free_lists[list_id].push_back(p);    // Add to the free list
    }
}

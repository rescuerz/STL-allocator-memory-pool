#include "MyAllocator.h"

template <class T>
size_t MyAllocator<T>::max_size = 2048;
template <class T>
size_t MyAllocator<T>::pool_size = 4096 * 1024;

// 初始化当前内存池，分配一个 pool_size 大小的块
template <class T>
void *MyAllocator<T>::current_pool = ::operator new(MyAllocator<T>::pool_size);

// 初始化内存池表，包含一个初始分配的内存池
template <class T>
vector<void *> MyAllocator<T>::memory_pool_table = {MyAllocator<T>::current_pool};

// 初始化池指针为 0
template <class T>
size_t MyAllocator<T>::pool_ptr = 0;

// 初始化空闲列表，用于存储不同大小的已释放内存块。这里初始化了 11 个自由列表，每个列表都是一个空向量。
// 由于我们的内存池大小为 4096KB，size 从 4 到 2048，所以我们需要 11 个空闲列表。
template <class T>
typename std::vector<vector<void *>> MyAllocator<T>::free_lists(11);


template <class T>
T *MyAllocator<T>::allocate(size_t n)
{
    // 计算所需的总大小
    size_t total_size = sizeof(T) * n; 
    // 如果所需的总大小超过最大值，则使用默认的 new
    if (total_size > MyAllocator<T>::max_size)
    {
        return static_cast<T *>(::operator new(total_size)); 
    }
    // 找到合适的空闲列表，二倍增长的方式
    int list_id = 0;
    size_t size = 4;
    for(list_id = 0; size < total_size; list_id++)
        size <<= 1;
    // 如果空闲列表不为空，则从空闲列表中取出一个块，并返回
    if (free_lists[list_id].empty() == 0)
    { 
        auto result = free_lists[list_id].back();
        free_lists[list_id].pop_back();
        return static_cast<T *>(result);
    }
    // 如果空闲列表为空，则从内存池中取出一个块，并返回
    return MyAllocator<T>::alloc_from_memory_pool(size);
}
 
// alloc_from_memory_pool : Allocate memory from the current memory pool
template <class T>
T *MyAllocator<T>::alloc_from_memory_pool(size_t size)
{
    // 如果有足够空间，则从当前内存池分配 size 大小的内存。
    if (pool_ptr + size <= pool_size)
    { 
        char *ptr = static_cast<char *>(current_pool) + pool_ptr;
        // 更新内存池指针
        pool_ptr += size; 
        return reinterpret_cast<T *>(ptr);
    }
    else
    {
        // 如果内存池空间不足：调用 refill_memory_pool 重新填充内存池
        refill_memory_pool();                
        return alloc_from_memory_pool(size); 
    }
}


// refill_memory_pool : Refill the memory pool by allocating a new block
template <class T>
bool MyAllocator<T>::refill_memory_pool()
{
    // 分配新的内存池：使用 ::operator new 分配一个新的 pool_size 大小的内存池。
    current_pool = ::operator new(pool_size); 
    if (current_pool == nullptr)
    {
        // 如果分配失败，则抛出异常
        throw bad_alloc(); 
    }
    pool_ptr = 0;   
    // 将新的内存池添加到内存池表中                           
    memory_pool_table.push_back(current_pool); 
    return true;
}


// deallocate():Deallocate memory for n objects of type T
template <class T>
void MyAllocator<T>::deallocate(T *p, size_t n)
{
    size_t total_size = n * sizeof(T); 
    // 检查总大小是否超过最大值：如果超过 max_size，则使用默认的 ::operator delete 释放内存。
    if (total_size > max_size)
    { 
        ::operator delete(p);
    }
    else if (total_size <= 2048)
    { 
        int list_id = 0;
        size_t size = 4;
        for(list_id = 0; size < total_size; list_id++)
            size <<= 1;
        free_lists[list_id].push_back(p); // Add to the free list
    }
}

#pragma once
#include <cstddef>
#include <cstdlib>
class MemoryPool{
public:
    static void* allocate(std::size_t bytes);
    static int deallocate(void* p,std::size_t bytes);
    static void* reallocate(void* p, std::size_t originalSize,std::size_t newSize);

    MemoryPool(){}
    ~MemoryPool(){}
};

static void* MemoryPool::allocate(std::size_t bytes){
    return static_cast<void* >(malloc(bytes));
}
static int MemoryPool::deallocate(void* p,std::size_t bytes){
    free(p);
    return 0;
}
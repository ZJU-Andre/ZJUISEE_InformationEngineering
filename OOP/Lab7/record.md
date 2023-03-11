# 分工
## 理解题目
### Allocator是什么
预留内存空间，提高效率的方法
### Memory Pool 是什么
把分配内存的过程从系统底层提到高层（应用层）
[CSDN: Allocator/Memorypool](https://blog.csdn.net/jcjc918/article/details/44997089)

##需要实现两个类
* Allocator
* **Memory Pool**

## 约定接口
prototype
需要哪些函数

```C++
typedef void _Not_user_specialized;
typedef _Ty value_type;
typedef value_type *pointer;
typedef const value_type *const_pointer;
typedef value_type& reference;
typedef const value_type& const_reference;
typedef size_t size_type;
typedef ptrdiff_t difference_type;
typedef true_type propagate_on_container_move_assignment;
typedef true_type is_always_equal;

pointer address(reference _Val) const _NOEXCEPT
const_pointer address(const_reference _Val) const _NOEXCEPT
void deallocate(pointer _Ptr, size_type _Count)
_DECLSPEC_ALLOCATOR pointer allocate(size_type _Count)
template<class _Uty> void destroy(_Uty *_Ptr)
template<class _Objty, class _Types>
void construct(_Objty *_Ptr, _Types&&... _Args)
```
除了这些还要一些私有的private?

memorypool header
Allocator implementation



## 确定算法


## 实现

### Allocator
### Memory Pool


## 步骤

1. Memory pool 头文件
周五/周六
2. allocator, memory pool
石昊海 allocator,
何柏村 memory pool
下周 二？ 晚上 
如果发现进度跟不上，微信再联系

## GitHub
[@Shaw Haines](https://github.com/ShawHaines)
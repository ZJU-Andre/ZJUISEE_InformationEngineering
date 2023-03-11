#pragma once
#ifndef _HBCALLOC_H
#define _HBCALLOC_H

#include <cstdlib>
#include <cstddef>

#define USE_VOLATILE
// #define USE_MALLOC

#ifdef USE_MALLOC
class MemoryPool_Alloc  //一级空间配置器
{

   private:
    // these funs below are used for "OOM" situations
    // OOM = out of memory
   public:

    static void* allocate(size_t n) {
        void* ret = malloc(n);
        return ret;
    }

    static void deallocate(void* p, size_t n) { free(p); }

    static void* reallocate(void* p, size_t oldSZ, size_t newSZ) {
        void* ret = realloc(p, newSZ);
        return ret;
    }
};
#else

class MemoryPool_Alloc {
	
private:

	enum { __ALIGN = 64 };//小型区块的上调边界
	enum { __MAX_BYTES = 1024 };//小型区块的上界，若调用内存超过256字节，则直接调用malloc,free和realloc
	enum { __NFREELISTS = __MAX_BYTES / __ALIGN };//freelists个数
	union  obj  //freelists的节点
	{
		union obj* Free_List_Link;
		char client_data[1];
	};
	//freelists
	static obj* Free_List[__NFREELISTS];
	//memrypool
	static char *start_free;
	static char *end_free;
	static size_t heap_size;
    //内用函数
    //将bytes上调至8的倍数
	static size_t ROUND_UP(size_t bytes) {  

		if (bytes % 8 != 0)

		{

			bytes = bytes + (8 - (bytes % 8));

		}

		return bytes;

	}

	//根据区块大小，决定使用第n号free_list n从1算起
	static size_t FREELIST_INDEX(size_t bytes) {

		return (((bytes)+__ALIGN - 1) / __ALIGN - 1);

	}

	//返回一个大小为n的对象，并尝试使用大小为n的区块填充free_list
	static void *refill(size_t n);
	//配置一大块空间，并尝试使用大小为n的区块填充free_list
	//nobjs可能会降低，当配置有困难时
	static char *chunk_alloc(size_t size, size_t& nobjs);

public:
	static void *allocate(size_t bytes);
	static void deallocate(void *p, size_t bytes);
	static void *reallocate(void *p, size_t originalSize, size_t newSize);
	MemoryPool_Alloc() {};
	~MemoryPool_Alloc() {};
};
    //定义与初值设定

    char* MemoryPool_Alloc::start_free = 0;
    char* MemoryPool_Alloc::end_free = 0;
    size_t MemoryPool_Alloc::heap_size = 0;
	
    MemoryPool_Alloc::obj *MemoryPool_Alloc::Free_List[MemoryPool_Alloc::__NFREELISTS] = 
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	void *MemoryPool_Alloc::allocate(size_t bytes) {
		
		//若所需内存大于256字节，认为其所需内存块较大，直接调用malloc函数申请内存

		if (bytes > __MAX_BYTES){
			return malloc(bytes);
		}
		else{
			size_t index;

			//寻找free_list中合适的一个管理空间去取内存
			index = FREELIST_INDEX(bytes);
			obj *my_free_list = Free_List[index];

			//如果对应的free_list没有内存，则从内存池中去取
			if (my_free_list == NULL){
				void *r = refill(ROUND_UP(bytes));
		        
				return r;
			}
			Free_List[index] = my_free_list->Free_List_Link;//将内存块使用权交给my_free_list

			return my_free_list;
		}
	}
	void MemoryPool_Alloc::deallocate(void *p, size_t bytes) {

		//如果申请释放的内存大于256字节，则直接调用free

		if (bytes > __MAX_BYTES){
			free(p);
			return;
		}

		//如果小于256字节，则回收至free_list中

		obj* my_free_list;
		size_t index;

		index = FREELIST_INDEX(bytes);
		my_free_list = Free_List[index];
		obj *mynode = static_cast<obj*>(p);
		mynode->Free_List_Link = my_free_list;
		my_free_list = mynode;
		return;
	}
	void *MemoryPool_Alloc::reallocate(void *p, size_t originalSize, size_t newSize) {
		if (originalSize > __MAX_BYTES) {//原内存大小超过256Bytes，则直接使用realloc函数向操作系统heap申请空间
			void *new_p = realloc(p, newSize);

			return new_p;
		}
		else {
			deallocate(p, originalSize);

			return allocate(newSize);
		}
	}
	void *MemoryPool_Alloc::refill(size_t n) {
		size_t nobjs = 20; //每次增加的节点个数，人为固定为20个

		//从内存池中取出nobjs个n bytes容量的区块
		char* chunk = chunk_alloc(n, nobjs);
#ifdef USE_VOLATILE
                obj *  volatile*my_lists;//指向free_list的指针
				#else
				obj** my_lists;
				#endif
		obj *result;
		obj *current_obj, *next_obj;

		size_t i;
		//如果只获得1个区块，则该区块调用给用户使用，free_list没有新节点
		if (1 == nobjs) return(chunk);
		//选择合适的free_list，纳入新节点
		my_lists = Free_List + FREELIST_INDEX(n);
		//第一块内存直接返回给客端使用
		result = (obj*)chunk;
		//剩下的内存块首尾依次相连加入到对应的free_list中去
		*my_lists = next_obj = (obj*)(chunk + n);
		for (i = 1; i<nobjs; i++){
			current_obj = next_obj;
			next_obj = (obj*)((char*)next_obj + n);
			if (nobjs - 1 == i){
				current_obj->Free_List_Link = NULL;
			}
			else{
				current_obj->Free_List_Link = next_obj;
			}
		}

		return result;
    }
	char *MemoryPool_Alloc::chunk_alloc(size_t size, size_t& nobjs) {

		char* result;
		size_t totalsize = size * nobjs;
		size_t bytesleft = end_free - start_free;

		if (bytesleft >= totalsize) {
			//如果内存池剩下的空间大于所需要的内存空间
			result = start_free;
			start_free += totalsize;

			return result;
		}
		else if (bytesleft >= size) {
			//如果内存池剩下的空间至少可以供一个(或以上)的size
			//那么将内存池剩下最大可分配块数给free-list，更新nobjs为最大分配块数x(x < 20)
			nobjs = bytesleft / size;
			totalsize = nobjs * size;
			result = start_free;
			start_free += totalsize;

			return result;
		}

		else {    //内存池剩余空间连一块内存都无法提供
			//将内存池内的剩余内存先分配给合适的free_list
			if (bytesleft > 0) {
				obj **my_free_list;
				my_free_list = Free_List + FREELIST_INDEX(bytesleft);
				((obj*)start_free)->Free_List_Link = *my_free_list;
				*my_free_list = ((obj*)start_free);
			}
			//向系统heap申请内存
			size_t bytesToGet = 2 * totalsize + ROUND_UP(heap_size >> 4);
			start_free = (char*)malloc(bytesToGet);
			if (NULL == start_free) {
				//heap空间不足，malloc失败
				size_t i;

				obj** my_free_list;
				obj* temp;
				//试着搜寻一下freelist中"尚有未用但足够大的内存块"
				for (i = size; i < __MAX_BYTES; i += __ALIGN) {
					my_free_list = Free_List + FREELIST_INDEX(i);
					temp = *my_free_list;
					if (NULL != temp) {
						*my_free_list = temp->Free_List_Link;
						start_free = (char*)temp;
						end_free = start_free + i;
						//递归调用，调整nobjs
						return chunk_alloc(size, nobjs);

					}
				}
				//完全没内存了，放弃吧
				end_free = NULL;
			}
			heap_size += bytesToGet;
			end_free = start_free + bytesToGet;
			
			//递归调用，调整nobjs
			return chunk_alloc(size, nobjs);
		}
	}


#endif
#endif
#if 0
#include <new>
#define _THROW_BAD_ALLOC throw bad_alloc
#elif !defined(_THROW_BAD_ALLOC)
#include <iostream>
#define _THROW_BAD_ALLOC             \
    cerr << "out of memory" << endl; \
    exit(0);
#endif

// malloc-based allocator. 通常比稍後介紹的 default alloc 速度慢，
// 一般而言是 thread-safe，並且對於空間的運用比較高效（efficient）。
// 以㆘是第㆒級配置器。
// 注意，無「template 型別參數」。至於「非型別參數」inst，完全沒派上用場。
template <int inst>
class __malloc_alloc_template
{
private:
    // 以下都是函式指標，所代表的函式將用來處理記憶體不足的情況。
    // oom : out of memory.
    static void *oom_malloc(size_t);
    static void *oom_realloc(void *, size_t);
    static void (*__malloc_alloc_oom_handler)();

public:
    static void *allocate(size_t n)
    {
        void *result = malloc(n); // 第一級配置器直接使用 malloc()
                                  // 以下，無法滿足需求時，改用 oom_malloc()
        if (result == 0)
            result = oom_malloc(n);
        return result;
    }

    static void deallocate(void *p, size_t /* n */)
    {
        free(p); // 第一級配置器直接使用 free()
    }

    static void *reallocate(void *p, size_t /* old _sz */, size_t new_sz)
    {
        void *result = realloc(p, new_sz); // 第一級配置器直接使用 realloc()
        // 以下，無法滿足需求時，改用 oom_realloc()
        if (0 == result)
            result = oom_realloc(p, new_sz);
        return result;
    }

    // 以下模擬 C++ 的 set_new_handler(). 換句話說，你可以透過它，
    // 指定你自己的 out-of-memory handler
    static void (*set_malloc_handler(void (*f)()))()
    {
        void (*old)() = __malloc_alloc_oom_handler;
        __malloc_alloc_oom_handler = f;
        return (old);
    }
};

// malloc_alloc out-of-memory handling
// 初值為 0。有待客端設定。
template <int inst>
void (*__malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;
template <int inst>
void *__malloc_alloc_template<inst>::oom_malloc(size_t n)
{
    void (*my_malloc_handler)();
    void *result;
    for (;;)
    {
        // 不斷嘗試釋放、配置、再釋放、再配置…
        my_malloc_handler = __malloc_alloc_oom_handler;
        if (0 == my_malloc_handler)
        {
            __THROW_BAD_ALLOC;
        }
        (*my_malloc_handler)(); // 呼叫處理常式，企圖釋放記憶體。
        result = malloc(n);
        // 再次嘗試配置記憶體。
        if (result)
            return (result);
    }
}
template <int inst>
void *__malloc_alloc_template<inst>::oom_realloc(void *p, size_t n)
{
    void (*my_malloc_handler)();
    void *result;
    for (;;)
    {
        // 不斷嘗試釋放、配置、再釋放、再配置…
        my_malloc_handler = __malloc_alloc_oom_handler;
        if (0 == my_malloc_handler)
        {
            __THROW_BAD_ALLOC;
        }
        (*my_malloc_handler)();
        // 呼叫處理常式，企圖釋放記憶體。
        result = realloc(p, n);
        // 再次嘗試配置記憶體。
        if (result)
            return (result);
    }
}
// 注意，以下直接將參數 inst 指定為 0。
typedef __malloc_alloc_template<0> malloc_alloc;

#include <new>

enum
{
    _ALLGN = 8
};
enum
{
    _MAX_BYTES = 128
};
enum
{
    _NFREELISTS = _MAX_BYTES / _ALLGN // free-list 个数
};

template <bool threads, int inst>
class _default_alloc_template
{
private:
    // ROUND_UP() 將 bytes 上調至 8 的倍數。
    static size_t ROUND_UP(size_t bytes)
    {
        return (((bytes) + _ALLGN - 1) & ~(_ALLGN - 1));
    }

private:
    union obj // free-lists的节点构造
    {
        union obj *free_list_link;
        char client_data[1];
    };

private:
    // 16个 free-lists
    static obj *volatile free_list[_NFREELISTS];

    static size_t FREELIST_INDEX(size_t bytes)
    {
        return (((bytes) + _ALLGN - 1) / _ALLGN - 1);
    }

    static void *refill(size_t n);
    static char *chunk_alloc(size_t size, int &nobjs);

    static char *start_free;
    static char *end_free;
    static size_t heap_size;

public:
    static void *allocate(size_t n)
    {
        obj *volatile *my_free_list;
        obj *result;

        if (n > (size_t)_MAX_BYTES)
            return (malloc_alloc::allocate(n));
    }
    static void deallocate(void *p, size_t n);
    static void *reallocate(void *p, size_t old_sz, size_t new_sz);
};

template <bool threads, int inst>
char *_default_alloc_template<threads, inst>::start_free = 0;
template <bool threads, int inst>
char *_default_alloc_template<threads, inst>::end_free = 0;
template <bool threads, int inst>
size_t _default_alloc_template<threads, inst>::heap_size = 0;

template <bool threads, int inst>
typename _default_alloc_template<threads, inst>::obj *volatile _default_alloc_template<threads, inst>::free_list[_NFREELISTS] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

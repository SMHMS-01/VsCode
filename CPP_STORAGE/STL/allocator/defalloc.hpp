#ifndef _DEFALLOC_H
#define _DEFALLOC_H

#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>

namespace SGI
{
    template <typename T>
    inline T *_allocate(ptrdiff_t size, T *)
    {
        std::set_new_handler(0);
        T *tmp = (T *)(::operator new((size_t)(size * sizeof(T))));
        if (tmp == 0)
        {
            std::cerr << "out of memory" << std::endl;
            exit(1);
        }
        return tmp;
    }

    template <typename T>
    inline void _deallocate(T *buffer) { ::operator delete(buffer); }

    template <typename T1, typename T2>
    inline void _construct(T1 *p, const T2 &value)
    {
        new (p) T1(value);
    }

    template <typename T>
    inline void _destory(T *ptr)
    {
        ptr->~T();
    }

    template <typename T>
    class allocator
    {
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef T &reference;
        typedef const T &const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

        //rebind allocator of type U
        template <typename U>
        struct rebind
        {
            typedef allocator<U> other;
        };

        pointer allocate(size_type n, const void *hint = 0)
        {
            return _allocate((difference_type)n, pointer(0));
        }

        void deallocate(pointer p, size_type n) { _deallocate(p); }

        void construct(pointer p, const T &value) { _construct(p, value); }

        void destory(pointer p) { _destory(p); }

        pointer address(reference x) { return (pointer)&x; }

        const_pointer const_address(const_reference x) { return (const_pointer)&x; }

        size_type max_size() const { return size_type(size_t(-1) / sizeof(T)); }

        size_type init_page_size() { return std::max(size_type(1), size_type(4096 / sizeof(T))); }
    };
    template <>
    class allocator<void>
    {
    public:
        typedef void *pointer;
    };
}

#endif
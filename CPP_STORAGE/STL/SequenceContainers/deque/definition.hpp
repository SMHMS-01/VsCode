// Deque 之迭代器
#include <iostream>
size_t __deque_buf_size(size_t n, size_t sz);
template <class T, class Ref, class Ptr, size_t BufSiz>
struct __deque_iterator
{ // 未繼承 std::iterator
    typedef __deque_iterator<T, T &, T *, BufSiz> iterator;
    typedef __deque_iterator<T, const T &, const T *, BufSiz> const_iterator;
    static size_t buffer_size() { return __deque_buf_size(BufSiz, sizeof(T)); }
    // 未繼承 std::iterator，所以必須自行撰寫五個必要的迭代器相應型別（第 3 章）
    // typedef random_access_iterator_tag iterator_category; // (1)
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T **map_pointer;

    typedef __deque_iterator self;

    // 保持與容器的聯結
    T *cur;   // 此迭代器所指之緩衝區㆗的現行（current）元素
    T *first; // 此迭代器所指之緩衝區的頭
    T *last;  // 此迭代器所指之緩衝區的尾（含備用空間）

    map_pointer node; // 指向管控中心

    void set_node(map_pointer new_node)
    {
        node = new_node;
        first = *new_node;
        last = first + difference_type(buffer_size());
    }

    reference operator*() const { return *cur; }
    reference operator->() const { return &(operator*()); }
    difference_type operator-(const self &x) const
    {
        return difference_type(buffer_size()) * (node - x.node - 1) + (cur - first) + (x.last - x.cur);
    }

    self &operator++()
    {
        ++cur; // 切換至下一個元素。

        if (cur == last)
        {

            set_node(node + 1); // 如果已達所在緩衝區的尾端，
            cur = first;        // 就切換至下一節點（亦即緩衝區）的第一個元素
        }
        return *this;
    }
    self operator++(int) // 後置式，標準寫法
    {
        self tmp = *this;
        ++*this;
        return tmp;
    }
    self &operator--()
    {
        if (cur == first) // 如果已達所在緩衝區的頭端，
        {
            set_node(node - 1); // 就切換至前一節點（亦即緩衝區）的最後一個元素。
            cur = last;
        }
        --cur; // 切換至前一個元素。

        return *this;
    }
    self operator--(int) // 後置式，標準寫法
    {

        self tmp = *this;
        --*this;
        return tmp;
    }

    // 以下實現隨機存取。迭代器可以直接跳躍 n 個距離。
    self &operator+=(difference_type n)
    {
        difference_type offset = n + (cur - first);
        if (offset >= 0 && offset < difference_type(buffer_size()))
            // 標的位置在同一緩衝區內
            cur += n;
        else
        {
            // 標的位置不在同一緩衝區內
            difference_type node_offset =
                offset > 0 ? offset / difference_type(buffer_size())
                           : -difference_type((-offset - 1) / buffer_size()) - 1;
            // 切換至正確的節點（亦即緩衝區）
            set_node(node + node_offset);
            // 切換至正確的元素
            cur = first + (offset - node_offset * difference_type(buffer_size()));
        }
        return *this;
    }

    self operator+(difference_type n) const
    {
        self tmp = *this;
        return tmp += n; // 喚起 operator+=
    }
    self &operator-=(difference_type n) { return *this += -n; }

    // 以上利用 operator+= 來完成 operator-=
    self operator-(difference_type n) const
    {
        self tmp = *this;
        return tmp -= n; // 喚起 operator-=
    }

    // 以下實現隨機存取。迭代器可以直接跳躍 n 個距離。
    reference operator[](difference_type n) const { return *(*this + n); }
    // 以上喚起 operator*, operator+
    bool operator==(const self &x) const
    {
        return cur == x.cur;
    }
    bool operator!=(const self &x) const
    {
        return !(*this == x);
    }
    bool operator<(const self &x) const
    {
        return (node == x.node) ? (cur < x.cur) : (node < x.node);
    }
    bool operator>(const self &x) const
    {
        return (node == x.node) ? (cur > x.cur) : (node > x.node);
    }
};
// 其中用來決定緩衝區大小的函式 buffer_size() ，呼叫 __deque_buf_size() ，
// 後者是個全域函式，定義如下：
// 如果 n 不為 0，傳回 n，表示 buffer size 由使用者自定。
// 如果 n 為 0，表示 buffer size 使用預設值，那麼
// 如果 sz（元素大小，sizeof(value_type)）小於 512，傳回 512/sz，
// 如果 sz 不小於 512，傳回 1。
inline size_t __deque_buf_size(size_t n, size_t sz)
{
    return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
}
template <class T, class Alloc = alloc, size_t BufSiz = 0>
class deque
{
public: // Basic types
    typedef T value_type;
    typedef value_type *pointer;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

public: // Iterators
    typedef __deque_iterator<T, T &, T *, BufSiz> iterator;

protected: // Internal typedefs
    // 元素的指標的指標（pointer of pointer of T）
    typedef pointer *map_pointer;

protected:          // Data members
    iterator start; // 表現第一個節點。

    iterator finish; // 表現最後一個節點。

    map_pointer map;
    // 指向 map，map 是塊連續空間，
    // 其每個元素都是個指標，指向一個節點（緩衝區）。
    size_type map_size; // map 內有多少指標。

public:
    iterator begin() { return start; }
    iterator end() { return finish; }
    reference operator[](size_type n) { return start[difference_type(n);] }
    reference front() { return *start; }
    reference back()
    {
        iterator tmp = finish;
        --tmp;
        return *tmp;
    }
    size_type size() const { return finish - start; }

    size_type max_size() const { return size_type(-1); }
    bool empty() const { return finish == start; }

    //空间配置
protected:
    typedef simple_alloc<value_type, Alloc> data_allocator;
    typedef simple_alloc<pointer, Alloc> map_allocator;

    deque(int n, const value_type &value) : start(), finish(), map(0), map_size(0) { fill_initialize(n, value); }

    
};
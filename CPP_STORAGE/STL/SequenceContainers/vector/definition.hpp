#include <iostream>

#if 0
template <typename T, typename Alloc = alloc>
class vector
{
public:
    typedef T value_type;
    typedef value_type *pointer;
    typedef value_type *iterator;
    typedef value_type &reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

protected:
    typedef simple_alloc<value_type, Alloc> data_allocator;
    iterator start;          // 表示目前使用空間的頭
    iterator finish;         // 表示目前使用空間的尾
    iterator end_of_storage; // 表示目前可用空間的尾
    void insert_aux(iterator position, const T &x);
    void deallocate()
    {
        if (start)
            data_allocator::deallocate(start, end_of_storage - start);
    }
    void fill_initialize(size_type n, const T &value)
    {
        start = allocate_and_fill(n, value);
        finish = start + n;
        end_of_storage = finish;
    }

public:
    iterator begin() { return start; }
    iterator end() { return finish; }
    size_type size() const { return size_type(end() - begin()); }
    size_type capacity() const
    {
        return size_type(end_of_storage - begin());
    }
    bool empty() const { return begin() == end(); }
    reference operator[](size_type n) { return *(begin() + n); }
    vector() : start(0), finish(0), end_of_storage(0) {}
    vector(size_type n, const T &value) { fill_initialize(n, value); }
    vector(int n, const T &value) { fill_initialize(n, value); }
    vector(long n, const T &value) { fill_initialize(n, value); }
    explicit vector(size_type n) { fill_initialize(n, T()); }
    ~vector()
    {
        destroy(start, finish);
        // 全域函式，見 2.2.3 節。
        deallocate();
        // 這是 vector 的㆒個 member function
    }
    reference front() { return *begin(); }
    // 第㆒個元素
    reference back() { return *(end() - 1); }
    // 最後㆒個元素
    void push_back(const T &x)
    {
        // 將元素安插至最尾端
        if (finish != end_of_storage)
        {
            construct(finish, x);
            // 全域函式，見 2.2.3 節。
            ++finish;
        }
        else
            insert_aux(end(), x);
        // 這是 vector 的一個 member function
    }
    void pop_back()
    {
        --finish;
        destroy(finish);
        // 全域函式，見 2.2.3 節。
    }

    void insert(iterator position, size_type n, const T &x);

    iterator erase(iterator position)
    {
        // 清除某位置㆖的元素
        if (position + 1 != end())
            copy(position + 1, finish, position);
        // 後續元素往前搬移
        --finish;
        destroy(finish);
        // 全域函式，見 2.2.3 節。
        return position;
    }
    void resize(size_type new_size, const T &x)
    {
        if (new_size < size())
            erase(begin() + new_size, end());
        else
            insert(end(), new_size - size(), x);
    }
    void resize(size_type new_size) { resize(new_size, T()); }
    void clear() { erase(begin(), end()); }

protected:
    // 配置空間並填滿內容
    iterator allocate_and_fill(size_type n, const T &x)
    {
        iterator result = data_allocator::allocate(n);
        uninitialized_fill_n(result, n, x); // 全域函式，見 2.3 節
        return result;
    } // 將最尾端元素取出
};

template <class T, class Alloc>
void vector<T, Alloc>::insert_aux(iterator position, const T &x)
{
    if (finish != end_of_storage)
    {
        // 還有備用空間
        // 在備用空間起始處建構㆒個元素，並以 vector 最後㆒個元素值為其初值。
        construct(finish, *(finish - 1));
        // 調整水位。
        ++finish;
        T x_copy = x;
        copy_backward(position, finish - 2, finish - 1);
        *position = x_copy;
    }
    else
    {
        // 已無備用空間
        const size_type old_size = size();
        const size_type len = old_size != 0 ? 2 * old_size : 1;
        // 以㆖配置原則：如果原大小為 0，則配置 1（個元素大小）；
        // 如果原大小不為 0，則配置原大小的兩倍，
        // 前半段用來放置原資料，後半段準備用來放置新資料。
        iterator new_start = data_allocator::allocate(len); // 實際配置
        iterator new_finish = new_start;
        try
        {
            // 將原 vector 的內容拷貝到新 vector。
            new_finish = uninitialized_copy(start, position, new_start);
            // 為新元素設定初值 x
            construct(new_finish, x);
            // 調整水位。
            ++new_finish;
            // 將原 vector 的備用空間㆗的內容也忠實拷貝過來（侯捷疑惑：啥用途？）
            new_finish = uninitialized_copy(position, finish, new_finish);
        }
        catch (...)
        {
            // "commit or rollback" semantics.
            destroy(new_start, new_finish);
            data_allocator::deallocate(new_start, len);
            throw;
        }
        // 解構並釋放原 vector
        destroy(begin(), end());
        deallocate();
        // 調整迭代器，指向新 vector
        start = new_start;
        finish = new_finish;
        end_of_storage = new_start + len;
    }
}

template <class T, class Alloc>
void vector<T, Alloc>::insert(iterator position, size_type n, const T &x)
{
    if (n != 0)
    { // 當 n != 0 才進行以㆘所有動作
        if (size_type(end_of_storage - finish) >= n)
        {
            // 備用空間大於等於「新增元素個數」
            T x_copy = x;-
            // 以㆘計算安插點之後的現有元素個數
            const size_type elems_after = finish - position;
            iterator old_finish = finish;
            if (elems_after > n)
                // 「安插點之後的現有元素個數」大於「新增元素個數」
                uninitialized_copy(finish - n, finish, finish);
            finish += n;
            // 將 vector 尾端標記後移
            copy_backward(position, old_finish - n, old_finish);
            fill(position, position + n, x_copy);
            // 從安插點開始填入新值
        }
        else
        {
            // 「安插點之後的現有元素個數」小於等於「新增元素個數」
            uninitialized_fill_n(finish, n - elems_after, x_copy);
            finish += n - elems_after;
            uninitialized_copy(position, old_finish, finish);
            finish += elems_after;
            fill(position, old_finish, x_copy);
        }
    }
    else
    {
        // 備用空間小於「新增元素個數」（那就必須配置額外的記憶體）
        // 首先決定新長度：舊長度的兩倍，或舊長度+新增元素個數。
        const size_type old_size = size();
        const size_type len = old_size + max(old_size, n);
        // 以㆘配置新的 vector 空間
        iterator new_start = data_allocator::allocate(len);
        iterator new_finish = new_start;
        try
        {
            // 以㆘首先將舊 vector 的安插點之前的元素複製到新空間。
            new_finish = uninitialized_copy(start, position, new_start);
            // 以㆘再將新增元素（初值皆為 n）填入新空間。
            new_finish = uninitialized_fill_n(new_finish, n, x);
            // 以㆘再將舊 vector 的安插點之後的元素複製到新空間。
            new_finish = uninitialized_copy(position, finish, new_finish);
        }
#ifdef __STL_USE_EXCEPTIONS
        catch (...)
        {
            // 如有異常發生，實現 "commit or rollback" semantics.
            destroy(new_start, new_finish);
            data_allocator::deallocate(new_start, len);
            throw;
        }
#endif /* __STL_USE_EXCEPTIONS */
        // 以㆘清除並釋放舊的 vector
        destroy(start, finish);
        deallocate();
        // 以㆘調整水位標記
        start = new_start;
        finish = new_finish;
        end_of_storage = new_start + len;
    }
}
int main()
{
    system("pause");
    return 0;
}

#endif
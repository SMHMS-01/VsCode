#include <iostream>
template <typename T>
struct __list_node
{
    typedef void *void_pointer;
    void_pointer prev; // 型別為 void*。其實可設為 __list_node<T>*
    void_pointer next;
    T data;
};
template <typename T, typename Ref, typename Ptr>
struct _list_iterator
{
    typedef _list_iterator<T, T &, T *> iterator;
    typedef _list_iterator<T, Ref, Ptr> self;

    typedef bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef __list_node<T> *link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    link_type node; // 迭代器內部當然要有個原生指標，指向 list 的節點

    // constructor
    _list_iterator(link_type x) : node(x) {}

    _list_iterator() {}
    _list_iterator(const _list_iterator &x) : node(x.node) {}

    bool operator==(const self &x) const { return node == x.node; }
    bool operator!=(const self &x) const { return node != x.node; }

    reference operator*() const { return (*node).data; }

    pointer operator->() const { return &(operator*()); }

    // 對迭代器累加 1，就是前進一個節點
    self &operator++()
    {
        node = (link_type)((*node).next);
        return *this;
    }

    self operator++(int)
    {
        self temp = *this;
        ++*this;
        return temp;
    }

    self &operator--()
    {
        node = (link_type)((*node).prev);
        return *this;
    }
    self operator--(int)
    {
        self temp = *this;
        --*this;
        return temp;
    }
};

template <class T, class Alloc = alloc> // 預設使用 alloc 為配置器
class list
{
protected:
    typedef __list_node<T> list_node;

public:
    typedef list_node *link_type;

protected:
    link_type node; // 只要一个指针，便可表示整個環狀雙向串列
    iterator begin() { return (link_type)((*node).next); }
    iterator end() { return node; }
    bool empty() const { return node->next == node; }
    size_type size() const
    {
        size_type result = 0;
        distance(begin(), end(), result); // 全域函式，第 3 章。
        return result;
    }
    // 取頭節點的內容（元素值）。
    reference front() { return *begin(); }
    // 取尾節點的內容（元素值）。
    reference back() { return *(--end()); }

    // construct and manage memory
protected:
    typedef __list_node<T> list_node;
    typedef simple_alloc<list_node, Alloc> list_node_allocator;

protected:
    link_type get_node() { return list_node_allocator::allocate(); }
    void put_node(link_type p)
    {
        list_node_allocator::deallocate(p);
    }

    link_type creat_node(const T &x)
    {
        link_type p = get_node();
        construct(&p->data, x);
        return p;
    }

    void destory_node(link_type p)
    {
        destory(&p->data);
        put_node(p);
    }

public:
    list() { empty_initialize(); }

protected:
    void empty_initialize()
    {
        node = get_node();
        node->next = node;
        node->prev = node;
    }

public:
    iterator insert(iterator position, const T &x)
    {
        link_type tmp = creat_node(x);
        tmp->next = position.node;
        tmp->prev = position.node->prev;
        (link_type(position.node->prev))->next = tmp;
        position.node->prev = tmp;
        return tmp;
    }

    void push_back(const T &x) { insert(end(), x); }
    void push_front(const T &x) { insert(beign(), x); }
    iterator erase(iterator position)
    {
        link_type next_node = link_type(position.node->next);
        link_type prev_node = link_type(position.node->prev);
        prev_node->next = next_node;
        next_node->prev = prev_node;
        destroy_node(position.node);
        return iterator(next_node);
    }

    void pop_front() { erase(begin()); }
    void pop_back()
    {
        iterator temp = end();
        erase(--temp);
    }

    void clear()
    {
        link_type cur = (link_type)node->next; // begin()
        while (cur != node)
        {
            link_type temp = cur;
            cur = (link_type)cur->next;
            destory_node(temp);
        }
        node->next = node;
        node->prev = node;
    }

    void remove(const T &x)
    {
        iterator first = begin();
        iterator last = end();
        while (first != last)
        {
            iterator next = first;
            ++next;
            if (*first == x)
                erase(first);
            first = next;
        }
    }

    void unique()
    {
        iterator first = begin();
        iterator last = end();
        if (first == last)
            return;
        iterator next = first;
        while (++next != last)
        {
            if (*first == *next)
                erase(next);
            else
            {
                first = next;
                next = first; // 修正區段範圍
            }
        }
    }

protected:
    void transfer(iterator position, iterator first, iterator last)
    {
        if (position != last)
        {
            (*(link_type((*last.node).prev))).next = position.node; // P139图，需要对两个链表调整
            (*(link_type((*first.node).prev))).next = last.node;
            (*(link_type((*position.node).prev))).next = first.node;
            link_type tmp = link_type((*position.node).prev);
            (*position.node).prev = (*last.node).prev;
            (*last.node).prev = (*first.node).prev;
            (*first.node).prev = tmp;
        }
    }

public:
    // 將 x 接合於 position 所指位置之前。x 必須不同於 *this。
    void splice(iterator position, list &x)
    {
        if (!x.empty())
            transfer(position, x.begin(), x.end());
    }
    // 將 i 所指元素接合於 position 所指位置之前。position 和 i 可指向同㆒個 list。
    void splice(iterator position, list &, iterator i)
    {
        iterator j = i;
        ++j;
        if (position == i || position == j)
            return;
        transfer(position, i, j);
    }
    // 將 [first,last) 內的所有元素接合於 position 所指位置之前。
    // position 和[first,last)可指向同㆒個 list，
    // 但 position 不能位於[first,last)之內。
    void splice(iterator position, list &, iterator first, iterator last)
    {
        if (first != last)
            transfer(position, first, last);
    }

    void merge(list &x)
    {
        // merge() 將 x 合併到 *this 上。兩個 lists 的內容都必須先經過遞增排序。
        iterator first1 = begin();
        iterator last1 = end();
        iterator first2 = x.begin();
        iterator last2 = x.end();
        while (first1 != last1 && first2 != last2)
        {
            if (*first2 < *first1)
            {
                iterator next = first;
                transfer(first1, first2, ++next);
                first2 = next;
            }
            else
                ++first1;
            if (first2 != last2)
                transfer(last1, first2, last2);
        }
    }

    void reverse()
    {
        // 以㆘判斷，如果是空白串列，或僅有一個元素，就不做任何動作。
        // 使用 size() == 0 || size() == 1 來判斷，雖然也可以，但是比較慢。
        if (node->next == node || link_type(node->next)->next == node)
            return;
        iterator first = begin();
        ++first;
        while (first != end())
        {
            iterator old = first;
            ++first;
            transfer(begin(), old, first);
        }
    }

    // list 不能使用 STL 演算法 sort()，必須使用自己的 sort() member function，
    // 因為 STL 演算法 sort() 只接受 RamdonAccessIterator.
    // 本函式採用 quick sort.
    template <class T, class Alloc>
    void list<T, Alloc>::sort()
    {
        // 以下判斷，如果是空白串列，或僅有一個元素，就不做任何動作。
        // 使用 size() == 0 || size() == 1 來判斷，雖然也可以，但是比較慢。
        if (node->next == node || link_type(node->next)->next == node)
            return;
        // 一些新的 lists，做為中介資料存放區
        list<T, Alloc> carry;
        list<T, Alloc> counter[64];
        int fill = 0;
        while (!empty())
        {
            carry.splice(carry.begin(), *this, begin());
            int i = 0;
            while (i < fill && !counter[i].empty())
            {
                counter[i].merge(carry);
                carry.swap(counter[i++]);
            }
            carry.swap(counter[i]);
            if (i == fill)
                ++fill;
        }
        for (int i = 1; i < fill; ++i)
            counter[i].merge(counter[i - 1]);
        swap(counter[fill - 1]);
    }
};
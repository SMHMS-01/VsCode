#include <iostream>
#include <windows.h>
#include <memory>
#include <vector>
using namespace std;

void test()
{
    auto p = make_shared<int>(42);
    cout << p.use_count() << endl;
    auto q(p);
    cout << q.use_count() << endl;
    auto r = make_shared<int>(43);
    r = q;
    q = make_shared<int>(777);
    auto j = p;
    auto z = p;
    cout << p.use_count() << ends << q.use_count() << ends << r.use_count();
}

template <typename Type>
class StrBlob
{
public:
    typedef typename std::vector<Type>::size_type size_type;
    StrBlob() : data(make_shared<vector<Type>>()) {}
    StrBlob(std::initializer_list<Type> i1) : data(make_shared<vector<Type>>(i1)) {}
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const Type &data) { data->push_back(data); }
    void pop_back()
    {
        check(0, "pop_back on empty StrBlob");
        data->pop_back();
    }
    Type &front() const
    {
        check(0, "front on empty StrBlob");
        return data->front();
    }
    Type &back() const
    {
        check(0, "back on empty StrBlob");
        return data->back();
    }
    shared_ptr<vector<Type>> getData() const
    {
        return data;
    }

private:
    shared_ptr<vector<Type>> data;
    void check(size_type i, const Type &msg) const
    {
        if (i >= data->size())
            throw out_of_range(msg);
    }
};
 
//unique_ptr
void test2()
{
    unique_ptr<int> p1(new int(42));
    unique_ptr<double> p2;
    double d = 3.1415;
    p2 = make_unique<double>(d);
    //     unique_ptr<int> p3(p1);//false
    //     unique_ptr<int >p4=p1;//false:unique 不支持赋值与拷贝，因为其拥有它指向的对象，并且只有一个
    unique_ptr<string> _p(new string("abcdefg"));
    unique_ptr<string> p5(_p.release()); //release将_p置为空，转移权限
    unique_ptr<string> p6 = make_unique<string>("jk");
    p5.reset(p6.release()); //reset释放了p5原来指向的内存
    // p5.release();           //false: p5不会释放内存，并且我们丢失了指针
    auto p_ = p5.release(); //true： 但是我们必须delete p_
    cout << *p_ << endl;

    string *str = new string("Jk my love");
    _p.reset(str); //u.reset(p) 如果提供了内置指针p，令u指向这个对象；否则把u置为空  u.reset(nullptr);
    cout << *_p << endl;
}

void test3()
{
    auto p = make_shared<int>(42);
    weak_ptr<int> wp(p);
    //安全访问
    if (auto np = wp.lock())
        cout << *np << endl;
}
//核查指针类
class StrBlobPtr
{
public:
    StrBlobPtr() : curr(0) {}
    StrBlobPtr(StrBlob<string> &a, size_t sz) : wptr(a.getData()), curr(sz) {}
    string &deref() const;
    StrBlobPtr &incr();

private:
    shared_ptr<vector<string>> check(size_t, const string &) const;
    weak_ptr<vector<string>> wptr;
    size_t curr;
};
shared_ptr<vector<string>> StrBlobPtr::check(size_t sz, const string &s) const
{
    auto ret = wptr.lock(); //vector还存在吗
    if (!ret)
        throw runtime_error("unbound StrBlobStr");
    if (sz >= ret->size())
        throw out_of_range(s);
    return ret;
}
string &StrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}
// 前缀递增：返回递增后的对象的引用
StrBlobPtr &StrBlobPtr::incr()
{
    check(curr, "Increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

void test4()
{
    //shared_ptr构成环，无法释放
    shared_ptr<int> p1(new int(20));
    shared_ptr<int> p2(new int(99));
    p1 = p2;
    cout << "p1: " << p1.use_count() << endl;
    p2 = p1;
    cout << "p2: " << p2.use_count() << endl;
    cout << p1.use_count() << ' ' << p2.use_count() << endl;
    weak_ptr<int> wp(p1);
    if (wp.lock())
        wp.reset();
}

void test5()
{
    shared_ptr<int> sp(new int[10], [](int *p)
                       { delete[] p; });
    for (size_t i = 0; i < 10; ++i)
    {
        *(sp.get() + i) = i + 10;
    }
    for (size_t i = 0; i < 10; ++i)
        cout << *(sp.get() + i) << ends;
}

//Allocator
void test6()
{
    allocator<string> alloc;           //可以分配string的allocator对象
    auto const p = alloc.allocate(10); //p为初地址
    auto q = p;
    alloc.construct(q++);          //*q为空字符串
    alloc.construct(q++, 10, 'c'); //*q为cccccccccc
    alloc.construct(q, "hi");      //*q为hi
    cout << *(p) << endl;          //true:
    // cout << *(++q) << endl;        //false: q指向未构造的内存
    while (q != p)
        alloc.destroy(--q); //元素被销毁
    alloc.deallocate(p, 10);
}
//allocator算法
// uninitialized_copy(b,e,b2);
// uninitialized_copy_n(b,n,b2);
// uninitialized_fill(b,e,value);
// uninitialized_fill_n(b,n,value);
void test7()
{
    allocator<int> alloc;
    vector<int> vi{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto const p = alloc.allocate(vi.size() * 2);
    //给定目的位置创建元素，而不是由系统分配内存给它们
    auto q = uninitialized_copy(vi.begin(), vi.end(), p);
    uninitialized_fill_n(q, vi.size(), 42);
    while (q != p)
    {
        cout << *(--q) << ends;
    }
}
int main()
{
    SetConsoleOutputCP(65001);
    test();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    system("pause");
    return 0;
}

#include <iostream>
#include <windows.h>
#include <utility>
#include <vector>
using namespace std;
template <typename T>
class DynamicArray
{
public:
    explicit DynamicArray(int size) : m_size{size}, m_array{new T[size]}
    {
        cout << "Constructor: dynamic array is created!\n";
    }

    virtual ~DynamicArray()
    {
        delete[] m_array;
        cout << "Destructor: dynamic array is destroyed!\n";
    }

    // 复制构造函数
    DynamicArray(const DynamicArray &rhs) : m_size{rhs.m_size}
    {

        m_array = new T[m_size];
        for (int i = 0; i < m_size; ++i)
            m_array[i] = rhs.m_array[i];
        cout << "Copy constructor: dynamic array is created!\n";
    }

    // 复制赋值操作符
    DynamicArray &operator=(const DynamicArray &rhs)
    {
        cout << "Copy assignment operator is called\n";
        if (this == &rhs)
            return *this;

        delete[] m_array;

        m_size = rhs.m_size;
        m_array = new T[m_size];
        for (int i = 0; i < m_size; ++i)
            m_array[i] = rhs.m_array[i];

        return *this;
    }

    // 索引运算符
    T &operator[](int index)
    {
        // 不进行边界检查
        return m_array[index];
    }

    const T &operator[](int index) const
    {
        return m_array[index];
    }

    int size() const { return m_size; }

    // 移动构造函数
    DynamicArray(DynamicArray &&rhs) noexcept : m_size{rhs.m_size}, m_array{rhs.m_array}
    {
        rhs.m_size = 0;
        rhs.m_array = nullptr;
        cout << "Move constructor: dynamic array is moved!\n";
    }

    // 移动赋值操作符
    DynamicArray &operator=(DynamicArray &&rhs) noexcept
    {
        cout << "Move assignment operator is called\n";
        if (this == &rhs)
            return *this;
        delete[] m_array;
        m_size = rhs.m_size;
        m_array = rhs.m_array;
        rhs.m_size = 0;
        rhs.m_array = nullptr;

        return *this;
    }

private:
    T *m_array;
    int m_size;
};
DynamicArray<int> arrayFactor(int size)
{
    DynamicArray<int> arr{size};
    return arr;
}

int main()
{
    SetConsoleOutputCP(65001);
    {
        DynamicArray<int> arr = arrayFactor(10);
        DynamicArray<int> arr2 = arrayFactor(std::move(arr.size()));
    }
    system("pause");
    return 0;
}

// 标准库是如何定义的
template <typename T>
typename remove_reference<T>::type &&move(T &&t)
{
    return static_cast<typename remove_reference<T>::type &&>(t);
}
void test()
{
    string s1("hello"), s2;
    s2 = std::move(string("yoa!")); //正确，从一个右值移动数据
    s2 = std::move(s1);             //正确：但在赋值之后，s1的值是不稳定的
}

//转发
void f(int v1, int &v2)
{
    cout << v1 << " " << ++v2 << endl;
}
void g(int &&v1, int &v2)
{
    cout << v1 << " " << v2 << endl;
}
template <typename T, typename F1, typename F2>
void flip(T t, F1 f1, F2 f2)
{
    f(f2, f1);
}
void flipCalled()
{
    int i, j = 0;
    f(42, j);       //改变了j的值
    flip(f, j, 42); //没有改变j的值，因为传递是j的拷贝，j的拷贝的引用++而不会改变j自身
    flip(g, i, 42);
}
//如果想要改变保持类型信息，可改为fcn(T t,F1 &&f1,F2 &&f2)

//在调用中使用std::forward保持类型信息
//forward能保持原始实参的类型。类似move，forward定义在头文件utility中。与move不同，forward必须通过显示模板实参来调用，forward返回
//该显示实参类型的右值引用，即forward<T>的返回类型是&&
//利用forward再次重写翻转函数
template <typename F, typename T1, typename T2>
void flip_2(F f, T1 &&t1, T2 &&t2)
{
    f(std::forward<T2>(t2), std::forward<T1>(t1)); //如果我们调用flip_2(g,i,42),i将以int&类型传递给g，42将以int&&类型传递给g
}
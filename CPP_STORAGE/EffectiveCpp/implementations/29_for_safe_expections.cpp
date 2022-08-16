#include <iostream>
#include <windows.h>

using namespace std;

//条款29：为"异常安全"而努力是值得的
//首先了解一下异常安全的概念，异常安全的意思就是：当程序在异常发生的时候，程序可以回退干净。什么事会退的干净呢？其实就是函数在发生异常的时候不会
//泄露资源或不会发生任何数据结构的破坏，这两个条件必须被满足。

//当异常被抛出时，带有异常安全性的函数会：
//1.不泄露任何资源；
//2.不允许数据破坏;

//异常安全函数即使发生异常也不会泄露资源或允许任何数据结构被破坏。
//异常安全函数提供以下三个保证之一：
//1.基本承诺；
//2.强烈保证；往往能够以copy-and-swap实现出来，但强烈保证并非对所有函数都可以实现或具备现实意义
//3.不抛出

//函数提供的"异常安全保证"通常最高只等于其所调用各个函数的"异常安全保证"中的最弱者。

//资源泄漏的问题，参考"以对象管理资源"@条款13
//一个造成数据破坏的例子
template <typename T>
class Type
{
public:
    Type &operator=(const Type &t)
    {
        if (this == &t)
            return *this;
        delete m_t;
        m_t = new T(t->m_t); //如果new T(t->m_t)执行时抛出异常，此时m_t指向破坏，m_t数据遭受了破坏

        //解决方案可以参考operator=内部swap+副本的实现方式
        //Type temp(t)；
        //swap(m_t，temp->m_t)；
        return *this;
    }

private:
    T *m_t;
};
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}

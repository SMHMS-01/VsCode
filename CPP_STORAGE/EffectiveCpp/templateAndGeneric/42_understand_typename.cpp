#include <iostream>
#include <windows.h>

using namespace std;

//条款42:了解typename的双重意义
//声明template参数时,前缀关键字class和typename可互换
//请使用关键字typename标识嵌套丛书类型名称;但不在base class list(基类列)或member initialization list(成员初值列)内它作为base class修饰符

//"typename必须作为嵌套从属类型名称的前缀词"这一规则的例外:typename不可以出现在base classes list内的嵌套从属类型名称之前,
//也不可在member initialization list中作为base class修饰符.如A:
template <typename T>
void print2nd(const T &container)
{
    if (container.size() >= 2)
    {
        //缺省情况下嵌套从属名称不是类型,必须用typename指涉一个嵌套从属类型名称
        typename T::const_iterator iter(container.begin());
        ++iter;
        int value = *iter;
        cout << value;
    }
}

template <typename T>
class Base
{
public:
    typedef T nested;
};
//A
template <typename T>
class Dervied : public Base<T> //base class list中不允许"typename'
{
public:
    explicit Dervied(int x) : Base<T>::nested(x)
    {
        typename Base<T>::nested temp; //mem init list中不允许"typename"嵌套从属类型名称,既不在base class list中也不在mem init list中作为一个base class修饰符需加上一个typename
    }
};
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}

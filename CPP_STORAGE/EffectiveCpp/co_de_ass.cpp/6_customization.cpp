#include <iostream>
#include <windows.h>

using namespace std;

//条款06：若不想使用编译器自动生成的函数，就该明确拒绝
//实在不想用就delete
class HomeForSale
{
public:
    HomeForSale() = default;

private:
    HomeForSale(const HomeForSale &); //只声明而不实现
    HomeForSale(HomeForSale &&);
    HomeForSale &operator=(const HomeForSale &);
    HomeForSale &operator=(HomeForSale &&);
};

class Test
{
public:
    Test() = delete;
    Test(const Test &) = delete;
};

class Uncopyable
{
protected:
    Uncopyable() = default; //允许子类对象构造和析构
    ~Uncopyable() = default;

private:
    Uncopyable(const Uncopyable &); //但是阻止copy
    Uncopyable &operator=(const Uncopyable &);
};
class UC : private Uncopyable //class 不在声明copy构造函数或copy assign运算符
{
};
void test()
{
    HomeForSale h1, h2;
    // h1 = h2;//不可访问
    // h1(h2);//不可访问
    // Test t1, t2;//删除构造函数，不可生成构造函数
    UC u1, u2;
    // u1(u2);
    // u1=u2;
}
int main()
{
    SetConsoleOutputCP(65001);

    system("pause");
    return 0;
}

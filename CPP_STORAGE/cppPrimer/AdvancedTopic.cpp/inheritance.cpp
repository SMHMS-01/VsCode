#include <iostream>
#include <windows.h>
#include <memory>
using namespace std;

struct Base1
{
    Base1() = default;
    Base1(const string &);
    Base1(shared_ptr<int>);
};
struct Base2
{
    Base2() = default;
    Base2(const string &);
    Base2(int);
};
struct D1 : public Base1, public Base2
{
    using Base1::Base1;
    using Base2::Base2; //从Base1/2继承构造函数
};

class Base
{
public:
    explicit Base(size_t sz, const string &str) : sz(sz), name(str) {}

private:
    size_t sz;
    string name;
};
class Dervide1 : virtual public Base
{
public:
    Dervide1(size_t sz, const string &str, int pos) : Base(sz, str), pos(pos) {}

private:
    int pos;
};
class Dervide2 : public Dervide1
{
public:
    //虚继承的对象的构造方式是从底层子类到基类 
    Dervide2(size_t sz, const string &str, int pos, double d) : Dervide1(sz, str, pos), d(d), Base(sz, str) {} //可调用Base()，因为虚继承

private:
    double d;
};
int main()
{
    SetConsoleOutputCP(65001);
    Base1 *b = new D1;
    delete b;
    b = nullptr;
    system("pause");
    return 0;
}

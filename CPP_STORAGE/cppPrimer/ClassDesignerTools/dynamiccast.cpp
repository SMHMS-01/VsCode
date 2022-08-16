#include <iostream>
#include <windows.h>
#include <random>
#include <typeinfo>
using namespace std;

//运行时类型识别    RTTI
//使用RTTI要加倍小心，最好还是定义虚函数而非直接接管类型管理的重任
class Base
{
    friend bool operator==(const Base &, const Base &);

public:
    inline virtual int RandNumber(const pair<int, int> &p)
    {
        static default_random_engine e;
        static uniform_int_distribution<int> u(p.first, p.second);

        return u(e);
    }

protected:
    virtual bool equal(const Base &) const;
};
class Dervide : virtual public Base
{
public:
    inline int RandNumber(const pair<int, int> &p) override
    {
        static default_random_engine e;
        static uniform_int_distribution<int> u(p.first + 10, p.second - 10);
        return u(e);
    }

protected:
    bool equal(const Base &) const;
};

bool operator==(const Base &lhs, const Base &rhs)
{
    return typeid(lhs) == typeid(rhs) && lhs.equal(rhs);
}
bool Dervide::equal(const Base &rhs) const
{
    auto r = dynamic_cast<const Dervide &>(rhs);
    return *this == r;
}
bool Base::equal(const Base &rhs) const
{ //执行比较base对象的操作
    return true;
}
//dynamic_cast&&typeid&&type_info
void dc()
{
    pair<int, int> p(0, 90);
    Base *bp = new Dervide;
    Base *dp = bp;

    cout << (typeid(*bp) == typeid(*dp)) << ' ' << (typeid(bp) == typeid(Dervide)) << ' ' << (typeid(*bp) == typeid(Dervide)) << endl;

    int arr[10];
    cout << typeid(42).name() << ' ' << typeid(arr).name() << ' ' << typeid(bp).name() << ' ' << typeid(*dp).name() << ' ' << typeid(string).name() << ' ' << endl;
    cout << typeid(p).name() << endl;
    cout << typeid(vector<int>).name() << endl;
}
int main()
{
    SetConsoleOutputCP(65001);
    dc();
    system("pause");
    return 0;
}

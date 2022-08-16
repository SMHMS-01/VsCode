#include <iostream>
#include <windows.h>
#include <sstream>
using namespace std;

//条款39：明智而审慎地使用private
//private继承意味着implemented-in-terms-of。它通常比复合的级别低。但是当derived class需要访问protected base class的成员，
//或需要重新定义继承而来的virtual时，这么设计是合理的。
//和复合不同，private继承可以造成empty class的最优化。这对致力于"对象尺寸最小化"的程序库开发者而言，可能很重要。
class person
{
};
class student : private person
{
};
void eat(const person &);
void study(const student &);

// void test1()
// {
//     person p;
//     student s;
//     eat(p);
//     // eat(s);//false: private继承意味着implemented-in-terms-of
// }

class Empty
{
};
class holder : public Empty
{
    int x;
};
void test2()
{
    cout << sizeof(Empty) << ' ' << sizeof(holder) << endl; //编译器优化，如果选择复合则size会变大...
}
class vehicle
{
public:
    enum Color
    {
        RED,
        BLUE,
        WHITE,
        BLACK,
        YELLOW
    };
    vehicle() = default;
    vehicle(unsigned price, Color col, const string &s) : price(price), color(col = BLACK), name(s) {}
    virtual int discountPrice(float f)
    {
        f = f / 10;
        return (f >= 0 ? price * f : price * (1 - f));
    }
    const string &EnginerNumber(unsigned num)
    {
        for (auto &s : name)
        {
            if (islower(s))
                s = toupper(s);
        }
        ostringstream os;
        os << name << num;
        enginerNumber = os.str();
        return enginerNumber;
    }

private:
    unsigned price;
    Color color;
    string name;
    string enginerNumber;
};
class bicycle : private vehicle
{

public:
    bicycle(unsigned price, Color col, const string &s, int h) : highestPrice(h)
    {
        vehicle(price, col = BLACK, s);
    }
    bicycle(const bicycle &bcl) : vehicle(bcl), highestPrice(bcl.highestPrice) {}
    virtual int discountPrice(float f)
    {
        cout << "The highest discount is : " << highestPrice * (f / 10) << endl;
        return highestPrice * (f / 10);
    }

private:
    int highestPrice;
};
void test3()
{
    vehicle v(10000, vehicle::RED, "vehicle");
    string s = v.EnginerNumber(03);
    cout << s << endl;
    cout << v.discountPrice(8) << endl;
    bicycle b(100000, vehicle::BLACK, "bicycle", 200000);
    b.discountPrice(8);
    // b.EnginerNumber(); //false
}
int main()
{
    SetConsoleOutputCP(65001);
    test3();
    system("pause");
    return 0;
}

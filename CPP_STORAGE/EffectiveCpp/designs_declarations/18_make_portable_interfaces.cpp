#include <iostream>
#include <windows.h>
#include <memory>
using namespace std;

//条款18：让接口容易被正确使用，不易被误用
//"促进正确使用"的方法包括接口的一致性，以及内置类型的行为兼容
//"阻止误用"的方法包括建立新类型、限制类型上的操作，束缚对象值，以及消除客户的资源管理责任(如智能指针)。
//shared_ptr支持定制型删除器
struct Date
{
    explicit Date(int mouths, int day, int year);
    explicit Date(const Month &m, const Day &d, const Year &y);
};
struct Day
{
    explicit Day(int d) : val(d) {}
    int val;
};
struct Month
{
    explicit Month(int m) : val(m) {}
    int val;
    static Month Jan() { return Month(1); }
    static Month Feb() { return Month(2); }
    //...
    static Month Dec() { return Month(12); }

private:
    // explicit Month(int m); //阻止生成新月份
};
struct Year
{
    explicit Year(int y) : val(y) {}
    int val;
};

class Investment
{

public:
    shared_ptr<Investment> creatInvestment()
    {
        return shared_ptr<Investment>(new Investment); //预先定制智能指针返回给用户，消弭忘记删除底部数据的可能性
        //还可以自定义删除其，章节复习：智能指针
    }
};
void test()
{
    Date d(30, 3, 1997); //乍一看合理，实际上不合法
    // Date d2(Day(30), Month(3), Year(2010)); //false
    Date d3(Month(3), Day(30), Year(1995)); //ok
}
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}

#include <iostream>
#include <windows.h>

using namespace std;

//协议11：在operator中处理自我赋值
//确保当对象自我赋值时operator=有良好行为。其中技术包括比较"来源对象"和"目标对象"的地址、精心周到的语句顺序、以及copy-and-swap
//确定任何函数如果操作一个以上的对象，而其中多个对象是同一个对象时，其行为仍然正确。
class Widget
{
public:
    Widget &operator=(const Widget &rhs)
    {
        delete str;
        str = new string(*rhs.str); //注意！如果自我赋值的话就表示删除了本身后指向了一个已经被删除的对象！下面有两种改进：
        return *this;
    }

private:
    string *str;
};
//advance1
class Bitmap
{
public:
    Bitmap &operator=(const Bitmap &rhs)
    {
        if (this == &rhs) //首先进行判断，是否是本身。
            return *this;
        delete str;
        str = new string(*rhs.str);
        return *this;
    }

private:
    string *str;
};
//advance2
class Bitmap2
{
public:
    Bitmap2 &operator=(const Bitmap2 &rhs)
    {
        string *Ostr = str;         //记住原先的Ostr
        str = new string(*rhs.str); //令str指向*str的一个副本
        delete Ostr;                //删除原先的str
        return *this;
    }

private:
    string *str;
};

//swap版
class Bitmap3
{
public:
    static void swap(Bitmap3 &b1, Bitmap3 &b2);
    Bitmap3 &operator=(const Bitmap3 &rhs)
    {
        Bitmap3 temp(rhs);
        swap(*this, temp);
        return *this;
    }
    // 或
    Bitmap3 &operator=(Bitmap3 rhs)
    {
        swap(*this, rhs);
        return *this;
    }

private:
    string *str;
};
void Bitmap3::swap(Bitmap3 &b1, Bitmap3 &b2)
{
    std::swap(b1.str, b2.str);
}
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}

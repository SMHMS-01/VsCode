#include <iostream>
#include <windows.h>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

class A
{
public:
    typedef size_t position;
    A() : pos(0) {}
    inline static const string *data()
    {
        return &A::contents;
    }
    inline position get_pos()
    {
        return A::pos;
    }

private:
    static const string contents;
    position pos;
};

class Screen
{
public:
    using Action = Screen &(Screen::*)();
    typedef size_t Direction;
    Screen &back();
    Screen &forward();
    Screen &Top();
    Screen &button();
    Screen &move(Direction);

private:
    static Action Menu[];
};
//函数表
Screen::Action Screen::Menu[] = {
    &Screen::back,
    &Screen::button,
    &Screen::forward,
    &Screen::Top};
Screen &Screen::move(Direction cm)
{
    return (this->*Menu[cm])();
}

const string A::contents = "ABC";

//使用function/mem_fn/bind生成一个可调用对象
void test()
{
    vector<string *> pvec{new string("Akemi"), new string("Homura")};
    function<bool(const string *)> fp = &string::empty;
    auto p = find_if(pvec.cbegin(), pvec.cend(), fp);
    cout << *p << endl;

    //mem_fn可根据成员指针的类型推断可调用函数的类型，无须用户显示地指定
    find_if(pvec.cbegin(), pvec.cend(), mem_fn(&string::empty));

    //mem_fn生成的可调用对象可以通过对象/指针调用
    vector<string> svec;
    auto f = mem_fn(string::empty);
    f(*svec.begin());
    f(&svec[0]);

    using namespace ::placeholders;
    auto it = find_if(svec.cbegin(), svec.cend(), bind(&string::empty, _1));
    auto f2 = bind(&string::empty, _1);
    f2(*svec.cbegin());
    f2(&svec[0]);
}
int main()
{
    SetConsoleOutputCP(65001);
    const string *pData = A::data();
    cout << *pData << endl;
    test();
    system("pause");
    return 0;
}

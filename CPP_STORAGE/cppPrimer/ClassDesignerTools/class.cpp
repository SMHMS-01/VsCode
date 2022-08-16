#include <iostream>
#include <windows.h>

using namespace std;

class Screen
{
private:
    mutable size_t access_ctr; //declared mutable data member
    size_t abcd;
    string text;

public:
    explicit Screen(string str) : text(str) {}
    Screen(size_t access);
    ~Screen();
    void member() const;
    size_t output() const
    {
        return access_ctr;
    }
    Screen &input(const string &str)
    {
        text = str;
        return *this;
    }
    void outputStr() const { cout << text; }
};

Screen::Screen(size_t access = 0) : access_ctr(access)
{
}

Screen::~Screen()
{
}
inline void Screen::member() const
{
    ++access_ctr; //可变数据成员即使在const函数内也可以改变
    //++abcd; 非可变数据成员，非法
}

class ExpicitTest
{
public:
    explicit ExpicitTest() = default;
    explicit ExpicitTest(int a) : _num(a) {}

private:
    int _num;
};
int main()
{
    SetConsoleOutputCP(65001);
    Screen *s = new Screen;
    s->member();
    s->member();
    s->member();
    s->input("abcde").outputStr();
    cout << s->output() << endl;

    ExpicitTest e;
    //如果添加了explicit则不可隐形转换，且explicit只能写在构造函数的声明而非定义中
    // e = 10;
    delete s;
    s = NULL;
    system("pause");
    return 0;
}

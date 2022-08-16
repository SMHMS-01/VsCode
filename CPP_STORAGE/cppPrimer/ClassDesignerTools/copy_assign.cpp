 #include <iostream>
#include <windows.h>

using namespace std;

//Copy\assign\erase
class HasPtr
{
private:
    string *ps;
    int i;
    size_t *used; //引用计数器

public:
    HasPtr(const string &s, const int i) : ps(new string(s)), i(i), used(new size_t(1)){};
    HasPtr(const HasPtr &p) : ps(p.ps), i(p.i), used(p.used) { ++*used; };
    HasPtr &operator=(const HasPtr &rhs);
    void display();
    ~HasPtr();
};

HasPtr::~HasPtr()
{
    if (--*used == 0)
    {
        delete used;
        used = nullptr;
        delete ps;
        ps = nullptr;
    }
}
HasPtr &HasPtr::operator=(const HasPtr &rhs)
{
    ++*rhs.used;
    if (--*used == 0)
    {
        delete used;
        used = nullptr;
        delete ps;
        ps = nullptr;
    }
    //定义像值的类
    // string *newp = new string(*rhs.ps); //为防止=自己，应该申请额外空间并拷贝
    // delete ps;
    // ps = newp;

    //定义像指针的类
    ps = rhs.ps;
    i = rhs.i;
    used = rhs.used;
    return *this;
}

void HasPtr::display()
{
    cout << i << " " + *ps << endl;
}
int main()
{
    SetConsoleOutputCP(65001);
    HasPtr *h1 = new HasPtr("homura", 99);
    HasPtr *h2 = h1;
    HasPtr *h3(h2);
    h3->display();
    system("pause");
    return 0;
}

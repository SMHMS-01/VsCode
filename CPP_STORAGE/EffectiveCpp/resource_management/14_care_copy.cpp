#include <iostream>
#include <windows.h>
using namespace std;

//条款14：在资源管理类中小心copying行为
class HasPtr
{

public:
    HasPtr(const string &s, const int i) : ps(new string(s)), i(i), used(new size_t(1)){};
    HasPtr(const HasPtr &p) : ps(p.ps), i(p.i), used(p.used) { ++*used; };
    HasPtr(HasPtr &&rhs) noexcept : ps(rhs.ps), i(rhs.i), used(rhs.used)
    {
        rhs.ps = nullptr;
        rhs.used = nullptr;
        rhs.i = 0;
    }
    HasPtr &operator=(const HasPtr &rhs);
    HasPtr &operator=(HasPtr &&rhs) noexcept;
    void display();
    ~HasPtr();

private:
    string *ps; //或用shared_ptr替代raw pointer

    int i;
    size_t *used; //引用计数器
};

HasPtr::~HasPtr()
{
    if (used == nullptr || --*used == 0)
    {
        delete used;
        used = nullptr;
        delete ps;
        ps = nullptr;
    }
}
HasPtr &HasPtr::operator=(const HasPtr &rhs)
{
    if (this == &rhs)
        return *this;
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
HasPtr &HasPtr::operator=(HasPtr &&rhs) noexcept
{
    if (this == &rhs)
        return *this;
    delete used;
    delete ps;
    ps = rhs.ps;
    used = rhs.used;
    i = rhs.i;

    rhs.i = 0;
    rhs.used = nullptr;
    rhs.ps = nullptr;
    return *this;
}
void HasPtr::display()
{
    cout << i << " " + *ps << endl;
}
int main()
{
    SetConsoleOutputCP(65001);
    HasPtr *hp = new HasPtr("Akemi Homura", 99);
    HasPtr hp2(std::move(*hp));
    HasPtr hp3 = std::move(hp2);
    hp3.display();
    // hp2.display();
    // hp->display();
    system("pause");
    return 0;
}

#include <iostream>
#include <windows.h>
#include <memory>
using namespace std;

//条款17：以独立语句将newed对象置入智能指针
class Widget
{
public:
    inline static int get_priority() { return priority; }
    static void processWidget(shared_ptr<Widget> pw, int pri) {}

private:
    static int priority;
};
void test()
{
    Widget::processWidget(shared_ptr<Widget>(new Widget), Widget::get_priority()); //由于各种原因，万一第二次调用get_priority失常，可能发生资源泄漏

    //独立语句将newed置入智能指针内就会安全得多
    shared_ptr<Widget> pw(new Widget);
    Widget::processWidget(pw, Widget::get_priority()); //这个动作绝不至于造成泄露
}
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}

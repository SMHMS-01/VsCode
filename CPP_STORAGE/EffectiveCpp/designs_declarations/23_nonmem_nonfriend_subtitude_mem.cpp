#include <iostream>
#include <windows.h>

using namespace std;

//条款23:宁以non-member, non-friend替换member函数
//宁可以non-member, non-friend替换member函数。这样做可以增加封装性、包裹弹性和技能扩充性。

//可在不同头文件中添加便利函数进入一个命名空间
namespace webBrowser
{
    class Browser
    {
    public:
        void clearCache();
        void addStuff();
        void download();
        void deleteStuff();
        void clearEach() //一个共同操作函数（便利函数）
        {
            clearCache();
            deleteStuff();
        };
    };
    void clearEach_(Browser &b)
    {
        b.clearCache();
        b.deleteStuff();
    }
}
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}

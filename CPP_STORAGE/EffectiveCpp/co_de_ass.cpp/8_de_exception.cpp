#include <iostream>
#include <windows.h>
#include <vector>
using namespace std;
//条款08：别让异常逃离异构函数
//C++并不禁止析构函数吐出异常，但他不鼓励这么做。
//比如在函数内创建容器、数组类型是类类型，则局部变量离开后会销毁，会抛出位置数量的异常，程序可能出现不明确行为

//请记住：析构函数绝对不要吐出异常。如果一个被析构函数调用的函数可能抛出异常，析构函数应该捕捉任何异常，然后吞下他们（不传播）或结束程序
//如果客户需要对某个操作函数运行期间的异常做出反应，那么class应该提供一个普通函数（而非在析构函数中）这姓该操作.
class DBConnection
{
public:
    static DBConnection creat();
    void close();
};
class DBConn
{
public:
    void close() //提供新函数
    {
        db.close();
        closed = true;
    }
    ~DBConn()
    {
        if (!closed) //如果客户没有主动关闭连接
        {
            try
            {
                db.close();
            }
            catch (...) //如果关闭动作失败吞下异常(catch空)；
            {
                std::abort(); //或记录下来,并结束程序
            }
        }
    }

private:
    DBConnection db;
    bool closed;
};

void test()
{
}
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}

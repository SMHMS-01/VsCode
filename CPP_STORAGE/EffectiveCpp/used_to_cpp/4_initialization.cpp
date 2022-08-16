#include <iostream>
#include <windows.h>

using namespace std;

//条款04：确定对象被使用前已被初始化p26
//代码例子，无法运行
class FileSystem
{ //来自你的程序库
public:
    size_t numDisks() const; //众多成员函数之一
    inline FileSystem &tfsCalled();
};
extern FileSystem tfs; //预留给客户的对象

class Director //由程序库客户建立
{
public:
    Director();
    inline Director &tempDirCalled();
};
Director::Director()
{
    size_t disks = tfs.numDisks(); //使用tfs对象
}
void test()
{
    //假设，这些客户决定创建一个Director对象用来放置临时文件
    Director tempDir(); //为临时文件而做的目录

    //现在，初始化次序的重要性就显现出来了：除非tfs在tempDir之前先被初始化，否则tempDir的构造函数会用到尚未初始化的tfs。
    //而tfs和tempDir是不同的人在不同的时间于不同的源文件建立起的，他们是定义与不同编译单元内的non-local static对象。
    //如何确定tfs会在tempDir之前被初始化？

    //解决方法如下：p31
}
inline FileSystem &FileSystem::tfsCalled()
{
    static FileSystem tfs;
    return tfs;
}
inline Director &Director::tempDirCalled()
{
    static Director tempDir;
    return tempDir;
}
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}

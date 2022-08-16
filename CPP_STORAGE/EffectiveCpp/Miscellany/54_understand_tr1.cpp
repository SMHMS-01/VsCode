#include <iostream>
#include <windows.h>

using namespace std;

//条款54：让自己熟悉包括TR1在内的标准程序库
//C++标准程序库的主要机能有STL、iostreams、locales组成。并包含C99标准程序库；
//TR1标准添加了智能指针、一般化函数指针、hash-base容器、正则表达式以及另外10个组件的支持；
//TR1自身只是一种规范。为获得TR1提供的好处，你需要一份实物。一个好的来源是Boost@条款55
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}

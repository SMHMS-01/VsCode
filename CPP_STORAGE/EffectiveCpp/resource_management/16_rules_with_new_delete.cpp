#include <iostream>
#include <windows.h>

using namespace std;
//条款16：成对使用new和delete时要采取相同形式

void test()
{
    string *s = new string[10];
    delete[] s; //valid!

    string *s2 = new string();
    delete[] s2; //false:可能会调用不相同类型的虚构函数，导致内存区被破坏

    typedef string addressLines[4];
    string *s3 = new addressLines;
    delete s3;   //false
    delete[] s3; //good
}
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}

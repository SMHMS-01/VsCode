#include <iostream>
#include <windows.h>

using namespace std;

//51：编写new和delete时需固守常规
//operator new 应该内含一个无穷循环，并且在其中尝试分配内存，如果它无法满足内存需求，就该调用new-handler。它也应该有能力处理0bytes申请。
//class专属版本则还应该处理"比正确大小更大的（错误）申请"。
//operator delete应该在收到null指针时不做任何事。class专属版本还应该处理"比正确大小更大的（错误）申请"。

//伪码
/*
void *operator new(size_t size)throw(bad_alloc)
{
    using namespace std;
    if(size==0)//处理0byte申请，把它视为1byte申请
    size=1;
    while(true)
    {
        尝试分配size bytes;
        if(分配成功)    return (一个指针，指向分配得来的内存);

        分配失败:找出目前的new-handler函数：
        new_handler globalHandler=set_new_handler(0);
        set_new_handler(globalHandler);

        if(globalHandler)(*globalHandler)();
        else throw bad_alloc();
    }

}
*/
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}

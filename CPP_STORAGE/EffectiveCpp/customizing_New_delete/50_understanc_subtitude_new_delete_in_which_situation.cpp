#include <iostream>
#include <windows.h>
#include <exception>
using namespace std;

//条款50：了解new和delete的合理替换时机
//替换编译器提供的operator new/delete的理由
//1.用来检测运用上的错误
//2.为了强化效能（增加分配和归还的速度）
//3.为了收集使用上的统计数据
//4.为了降低缺省内存管理器所带来的空间额外开销
//5.为了弥补缺省分配器中的非最佳齐位
//6.为了将相关对象成簇集中
// 7.为了获得自定义非传统行为
static const int signature = 0xDEADBEEF;
typedef unsigned char Byte;
void *operator new(std::size_t size) throw()
{
    std::size_t reSize = size + 2 * sizeof(int); //增加大小，使之能够塞入两个signature
    void *pMem = malloc(reSize);                 //取得内存
    if (!pMem)
        throw bad_alloc();

    //将signature写入内存的最前段落和最后段落
    *(static_cast<int *>(pMem)) = signature;
    *(reinterpret_cast<int *>(static_cast<Byte *>(pMem) + reSize - sizeof(int))) = signature;
    // 返回指针，指向恰好位于第一个signature之后的内存位置
    return static_cast<Byte *>(pMem) + sizeof(int);
}
//上面的例子的缺点主要是它忽略了身为这个特殊函数所应该具备的"坚持C++规矩"的态度。
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}

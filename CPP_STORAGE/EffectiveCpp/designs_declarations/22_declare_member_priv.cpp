#include <iostream>
#include <windows.h>

using namespace std;

//条款22：将成员变量声明为private
//如果将一个成员变量声明为public、protected而客户开始使用他，就很难改变那个成员变量所涉及的一切，太多代码需要重写、重新测试、重新编写文档、
// 重新编译。从封装的角度来看，其实只有两种访问权限：private(提供封装)和其他(不提供封装)。
//切记把成员变量声明为private。这可赋予客户访问数据的一致性、可细微划分访问控制、允许约束条件获得保证，并提供class作者以充分的实现弹性。
//protected 并不比public更具备封装性.
class AccessLevels
{
public:
    int getReadOnly() const { return readOnly; }
    void setReadWrite(int val) { readWrite = val; }
    int getReadWrite() const { return readWrite; }
    void setWriteOnly(int val) { writeOnly = val; }

private:
    int noAccess;  //不可访问
    int readOnly;  //只读
    int readWrite; //读写
    int writeOnly; //只写
};
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}

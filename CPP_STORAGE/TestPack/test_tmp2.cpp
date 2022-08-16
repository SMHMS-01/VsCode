#include <iostream>
#include <windows.h>

using namespace std;

struct C_point
{
    int a = 0;
};

class point
{
public:
    point() = default;
    operator C_point() { return _c_point; }

private:
    C_point _c_point;
};

void test()
{
}
int main()
{
    SetConsoleOutputCP(65001);
    point t;
    C_point var;
    var = C_point(t);
    system("pause");
    return 0;
}

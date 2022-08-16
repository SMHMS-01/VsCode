#include <iostream>
#include <windows.h>
#include <exception>
using namespace std;

void excep()
{
    exception *pE = new exception();
    throw pE->what();
}
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}

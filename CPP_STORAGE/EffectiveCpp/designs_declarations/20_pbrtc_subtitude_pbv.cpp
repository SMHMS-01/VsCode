#include <iostream>
#include <windows.h>

using namespace std;

//条款20：宁以pass-by-reference-to-const替换pass-by-value
//advance：非内置类型/STL的迭代器和函数对象，一般情况Pass-by-reference-to-const高效得多，并且可以避免切割
//STL的迭代器和函数对象还是pass-by-value更妥当

class Tools
{
public:
    static void display(const Tools &t) //可避免切割
    {
        cout << "number is " << t.num << "\n name is " << t.name << endl;
    }
    static void print(Tools t) //构造函数生成，一般情况下浪费空间和时间，并且有可能被切割
    {
        cout << "number is " << t.num << "\n name is " << t.name << endl;
    }

private:
    unsigned short num;
    string name;
};
class sofa : public Tools
{
private:
    string materials;
};

void test()
{
    sofa s;
    Tools::display(s);
}
int main()
{
    SetConsoleOutputCP(65001);
    test();
    system("pause");
    return 0;
}

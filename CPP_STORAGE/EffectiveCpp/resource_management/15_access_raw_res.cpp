#include <iostream>
#include <windows.h>

using namespace std;
//条款15：在资源管理类中提供对原始资源的访问
// APIs往往要求访问原始数据，所以每一个RAII class因该提供一个"取得其所管理的资源"的办法
//对原始资源的访问可能经由显式转换或隐式转换。一般而言显式转换比较安全，隐式转换比较方便。
class PrintString
{
public:
   PrintString(ostream &o, char c = '\0') : os(o), sep(c) {}
   void operator()(const string &str) { os << str << sep; }
   ostream &get() const { return os; } //显式调用函数

private:
   ostream &os;
   char sep;
};
class PrintStringOrInt : public PrintString
{
public:
   PrintStringOrInt(ostream &o, char c = '\0') : PrintString(o, c), ps(PrintString(cout, '\0')) {}
   PrintStringOrInt(ostream &o = cout, char c = '\0', int i = 0) : PrintString(o, c), rhs(i), ps(PrintString(cout, '\0')) {}
   PrintStringOrInt(const PrintStringOrInt &rhs_) : PrintString(rhs_), rhs(rhs_.rhs), ps(rhs_) {}
   operator PrintString() const { return ps; } //隐式转换函数

private:
   int rhs;
   PrintString ps;
};
void test()
{
   PrintString *printer = new PrintString(cout, '\n');
   printer->operator()("Homura");
   (printer);
   PrintString errors(cerr, '\n');
   errors("error!");
   delete printer;

   ostream &os = errors.get(); //显式调用
   PrintStringOrInt psot(cout, '\0', 10);
   PrintString ps2 = psot; //隐式调用
   ps2.get() << "hhh" << endl;
}
int main()
{
   SetConsoleOutputCP(65001);
   test();
   system("pause");
   return 0;
}

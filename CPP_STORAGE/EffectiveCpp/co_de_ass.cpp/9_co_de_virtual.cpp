#include <iostream>
#include <windows.h>

using namespace std;
//条款09：绝不在析构和构造函数中调用virtual函数

class Transaction
{
public:
   explicit Transaction(const string &logInfo);
   void logTransaction(const string &logInfo) const;
};

Transaction::Transaction(const string &logInfo)
{
   //如果此处执行virtual调用，由于编译器/运行期类型信息会把对象视为base class类型，对象在derived class构造函数开始执行前不会成为一个derived calss对象
   logTransaction(logInfo); //non-virtual调用
}
class BuyTransaction : public Transaction
{
public:
   BuyTransaction(const string &logInfo) : Transaction(creatLogString(logInfo)) {}

private:
   static string creatLogString(const string &logStr);
};

class SellTransaction : public Transaction
{
public:
   virtual void logTranscation() const;
};

int main()
{
   SetConsoleOutputCP(65001);
   //在建造派生类的构造函数的时候一定会首先生成基类的构造函数，所以不要在构造/析构函数中调用了virtual函数，因为这类调用从不下降到derived calsses
   //（比起当前执行构造函数和析构函数的那层）
   BuyTransaction b("abc");
   system("pause");
   return 0;
}

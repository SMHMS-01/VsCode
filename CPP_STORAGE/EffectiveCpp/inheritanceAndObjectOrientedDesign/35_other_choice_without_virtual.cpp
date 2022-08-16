#include <iostream>
#include <windows.h>

using namespace std;

//条款35:考虑virtual函数以外的其他选择
//策略Strategy设计模式学习...++任务

//virtual函数的替代方案包括NVI手法以及strategy设计模式的多种形式.NVI手法自身是一个特殊形式的Template Method设计模式。
//将机能从成员函数转移到class外部函数，带来的一个缺点是：非成员函数无法访问class的non-public成员。
//trl::function 对象的行为就像一般指针函数。这样的对象可接纳"与给定目标签名式兼容"的所有可调用物。
class gameCharacter
{
public:
    virtual int heathValue() const;
};

//藉由Non-virtual interface手法实现 Template Method 设计模式
class GameCharacter
{
public:
    int heathValue() const
    {
        int retval = doHeathValue();
        return retval;
    }

private:
    virtual int doHeathValue() const
    {
        //...缺省实现
    }
};

//藉由Function Pointers实现Strategy模式(用trl::function<>更好，c++11)
class gamecharacter;
int defaultHeathCalc(const gamecharacter &gc);
class gamecharacter
{
public:
    typedef int (*HeathCalcFunc)(const gamecharacter &);
    explicit gamecharacter(HeathCalcFunc hcf = defaultHeathCalc) : heathFunc(hcf)
    {
    }
    int heathValue() const { return heathFunc(*this); }

private:
    HeathCalcFunc heathFunc;
};

class envi : public gamecharacter
{
public:
    explicit envi(HeathCalcFunc hcf = defaultHeathCalc) : gamecharacter(hcf) {}
};
int loseHeathQuickly(const gamecharacter &);
int loseHeathSlowly(const gamecharacter &);
void test2()
{
    envi en1(loseHeathQuickly);
    envi en2(loseHeathSlowly);
}
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}

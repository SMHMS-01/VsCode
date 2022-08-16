#include <iostream>
#include <windows.h>

//条款12：赋值对象时勿忘其每一个成分
//Copying函数应该确保复制"对象内所有成员变量"及"所有base class"成分
//不要尝试以某个copying函数实现另一个copying函数。应该将共同机能放进第三个函数中，并由两个copying函数共同使用。
using namespace std;
void logCall(const string &funcName)
{
    cout << funcName << endl;
}
class Customer
{
public:
    Customer(const string &name_) : name(name_) {}
    Customer(const Customer &rhs);
    Customer &operator=(const Customer &rhs);

private:
    string name;
};
Customer::Customer(const Customer &rhs) : name(rhs.name)
{
    logCall("Customer copy constructor");
}
Customer &Customer::operator=(const Customer &rhs)
{
    logCall("Customer copy assignment operator");
    name = rhs.name;
    return *this;
}

class PriorityCustomer : public Customer
{
public:
    PriorityCustomer(int p) : Customer(""), priority(p) {}
    PriorityCustomer(const PriorityCustomer &rhs);
    PriorityCustomer &operator=(const PriorityCustomer &rhs);

private:
    int priority;
};
PriorityCustomer::PriorityCustomer(const PriorityCustomer &rhs) : Customer(rhs), priority(rhs.priority)
{
    logCall("PriorityCustomer copy construct");
}
PriorityCustomer &PriorityCustomer::operator=(const PriorityCustomer &rhs)
{
    logCall("PriorityCustomer copy assignment operator");
    priority = rhs.priority;
    return *this;
}

//避免对未初始化对象做赋值动作/构造一个已经存在的对象
//即"令copy构造函数调用copy assignment操作符"/"令copy assignment操作符调用copy构造函数"
class A
{
public:
    A(int num, const string &str, double d)
    {
        init(num, str, d);
    }
    A(const A &a)
    {
        init(a.num, a.name, a.version);
    }
    A &operator=(const A &a)
    {
        init(a.num, a.name, a.version);
        return *this;
    }

private:
    int num;
    string name;
    double version;
    void init(int num, const string &strName, double d)
    {
        this->num = num;
        name = strName;
        version = d;
    }
};
int main()
{
    SetConsoleOutputCP(65001);
    PriorityCustomer pc0(0);
    Customer *pc = new PriorityCustomer(pc0);

    delete pc;
    system("pause");
    return 0;
}

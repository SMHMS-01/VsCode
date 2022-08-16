#include <iostream>
#include <windows.h>

using namespace std;

//条款40：明智而审慎地使用多重继承
//多重继承比单一继承复杂。它可能导致新的歧义性，以及对virtual集成的需要。
//virtual继承会增加大小、速度、初始化(以及赋值)复杂度等成本。如果virtual base classes不带任何数据，将是最有实用价值的情况。
//多重继承的确有正当用途。其中一个情节涉及"public继承某个interface class"和"private继承某个协助实现的class"的两相结合.

class IPerson
{
public:
    virtual ~IPerson();
    virtual string name() const = 0;
    virtual string birthDate() const = 0;
};
class DataBaseID
{
};
class PersonInfo
{
public:
    explicit PersonInfo(DataBaseID pid);
    virtual ~PersonInfo();
    virtual const char *theName() const;
    virtual const char *theBirthDate() const;
    virtual const char *valueDelimOpen() const;
    virtual const char *valueDelimClose() const;
};
const char *PersonInfo::theName() const
{
    static char value[1000];
    strcpy(value, valueDelimOpen());
    strcat(value, valueDelimClose());
    return value;
}
class CPerson : public IPerson, private PersonInfo //多继承：public继承自某接口、private继承自某实现
{
public:
    explicit CPerson(DataBaseID pid) : PersonInfo(pid) {}
    virtual string name() const { return PersonInfo::theName(); } //实现必要的抽象基类接口
    virtual string birthDate() const { return PersonInfo::theBirthDate(); }

private:
    const char *valueDelimOpen() const { return ""; } //重新定义继承而来的virtual函数
    const char *valueDelimClose() const { return ";"; }
};
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}

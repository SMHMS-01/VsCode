#include <iostream>
#include <windows.h>
#include <memory>
#include <sstream>
using namespace std;

const string Upper(const string &str)
{
    shared_ptr<string> sp(new string(str));
    weak_ptr<string> wptr(sp);
    if (!wptr.lock())
        throw bad_alloc();
    for (unsigned int i = 0; i < (*sp).size(); ++i)
    {
        if ((*sp)[i] >= 97 && (*sp)[i] <= 122)
        {
            (*sp)[i] -= 32;
        }
    }
    return *sp;
}
const string Upper(string &&str)
{
    shared_ptr<string> sp(new string(str));
    weak_ptr<string> wptr(sp);
    if (!wptr.lock())
        throw bad_alloc();
    for (unsigned int i = 0; i < (*sp).size(); ++i)
    {
        if ((*sp)[i] >= 97 && (*sp)[i] <= 122)
        {
            (*sp)[i] -= 32;
        }
    }
    return *sp;
}
const char Upper(char &s)
{
    shared_ptr<char> sp(new char(s));
    weak_ptr<char> wptr(sp);
    if (!wptr.lock())
        throw bad_alloc();
    if (*sp >= 97 && *sp <= 122)
        *sp -= 32;
    return *sp;
}

void test()
{
    string str("eabcdadafa"), str2("edef");
    cout << (str <= str2 ? str : str2) << endl;
}
main()
{
    SetConsoleOutputCP(65001);

    cout << Upper("I muSt bE GkD! And I love BinaRy forevERy;") << endl;
    const char *str("aduadgt");
    cout << Upper(str) << endl;

    char c('a');
    cout << Upper(c) << endl;
    test();
    system("pause");
    return 0;
}

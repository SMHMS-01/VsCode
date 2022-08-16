#include <iostream>
#include <windows.h>
#include <vector>
using namespace std;

void test()
{
    constexpr const char *chr = "abcd";
    static_cast<string>(chr); //static_cast can't exit cancel const

    //false : const_cast can just change bottom const of object
    //const_cast<string>(chr);
    const char *chr2;
    const_cast<char *>(chr2);
    chr2 = "adafa"; //true

    vector<string> vs;
    string a;
    unsigned num = 1;
    vs.reserve(7);
    vs.emplace_back("how");
    vs.emplace_back("now");
    vs.emplace_back("now");
    vs.emplace_back("now");
    vs.emplace_back("brown");
    vs.emplace_back("cow");
    vs.emplace_back("cow");
    for (auto iter = vs.begin(); iter < vs.end();)
    {
        if (*(++iter) == *(iter))
        {
            num++;
            cout << *iter << '\t';
                }
    }

    cout << num;
}
int main()
{
    SetConsoleOutputCP(65001);
    test();
    system("pause");
    return 0;
}

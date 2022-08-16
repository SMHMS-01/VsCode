#include <iostream>
#include <windows.h>
#include <string>
#include <cctype>
#include <vector>
//isalnum(c) 当c是字母或数字时为真
//isalpha(c) 当c是字母时为真
//iscntrl(c) 当c是控制字符时为真
//isdigit(c) 当c是数字时为真
//isgraph(c) 当c不是空格但可打印时为真
//islower(c) 当c是小写字母时为真
//isprint(c) 当c是可打印字符时为真（即c是空格或具备可视形式）
//ispunct(c) 当c是标点符号时为真
//isspace(c) 当c是空白（空格、横向制表符、纵向制表符、回车符、换行符、进纸符）时为真
//isupper(c) 当c是大写字母时为真
//isxdigit(c) 当c是16进制数字时为真
//tolower(c) 如果c是大写字符，输出对应的小写字符；否则原样输出
//toupper(c) 如果c是小写字符，输出对应的大写字符；否则原样输出
using namespace std;

void stringV()
{
    string a("abcdefg"), b;
    // while (cin >> a)
    // {
    //     cin >> b;
    //     a += b;
    //     if (a == "##")
    //         break;
    //     cout << a << " ";
    // }
    for (auto c : a)
        cout << c;
    cout << endl;
}

void countPunct()
{
    string a("ab?c\"d\"efg i love mine something");
    decltype(a.size()) count = 0;
    for (auto c : a)
        if (ispunct(c))
            ++count;
    //全部替换成大写
    // for (auto &c : a)
    //     c = toupper(c);

    //根据下标替换字符
    if (!a.empty())
        a[0] = toupper(a[0]);
    cout << count << endl;

    //替换首字符
    // for (decltype(a.size()) i = 0; i != a.size();)
    //     if (isspace(a[i++]))
    //         a[i] = toupper(a[i]);
    for (decltype(a.size()) i = 0; i != a.size(); i++)
        if (!ispunct(a[i]))
            cout << a[i];
}

//C 标准库string函数
//include <cstring>
//strlen(c) 返回c的长度，空字符不算在内(c必须以空字符结束)
//strcat(p1,p2) 将p2附加到p1之后，返回p1
//strcmp(p1,p2) 比较p1和p2的相等性。 if(p1==p2) return 0;   else if (p1>p2) return true;  else return false
//strcpy(p1,p2) 将p2拷贝给p1，返回p1
void test2()
{
    char c[] = "abcde";
    //如果chr不以空字符结尾，则返回size_t类型长度，会引发严重错误
    const char chr[] = {'a', 'b', 'c', 'd', 'e', '\0'};
    // cout << strlen(c) << endl
    //  << strlen(chr) << endl;

    //比较字符串
    //C++ 用的是普通的关系运算符和相等性运算符
    string s1 = "a string example";
    string s2 = "a different example";
    if (s1 < s2)
        cout << "true" << endl;
    else
        cout << "false" << endl;

    //C比较的则是指针而非字符串本身
    const char a[] = "a string example";
    const char b[] = "a different example";
    if (a < b) //如果调用strcmp(a,b)<0 等价于s1<s2
        cout << "true" << endl;
    else
        cout << "false" << endl;
}

//other actions to construct string and other actions
void test3()
{
    const char *cp = "hello world";
    char noNull[]{'J', 'K'};
    vector<char> vc{'a', 'k', 'l', 'o'};
    auto vciter = vc.begin();
    string o0(vciter, vc.end());
    string s1(cp);        //拷贝until '\0'
    string s2(noNull, 2); //从npNull拷贝两个字符
    string s3(cp + 6, 5); //从cp的第六个字符开始拷贝五个
    string s4(s1, 6, 5);  //从s1的第六个字符开始拷贝五个
    string s5(s1, 6);     //  从s1的第六个字符开始拷贝
    // string s6(s1, 18);    //会抛出out_of_range异常

    string s7 = s1.substr(6); //
    // string s8 = s7.substr(6, 11); //开始位置和计数值
    cout << o0 << endl;

    s7.append("STR");
    s7.append(10, '*');
    cout << s7 << endl;
}
//p326
void search()
{
    string s("Akemi Homura");
    string::size_type pos;
    pos = s.find("Homura"); //查找s中"Homura"第一次出现的位置
    auto pos2 = s.find("Homura", 7);
    s.rfind("Homura");             //查找s中"Homura"最后一次出现的位置
    s.find_first_of("Homura");     //在s中查找"Homura"中任意一个字符第一次出现的位置
    s.find_first_not_of("Homura"); //在s中查找第一个不在"Homura"的字符的位置
    s.find_last_not_of("Homura");
    s.find_last_of("Homura");
    cout << pos << ends << pos2 << endl;

    //逆向搜索

    string river("Mississippi");
    auto first_pos = river.find("is"); //return 1 第一次出现的位置
    auto last_pos = river.rfind("is"); //return 4 最后一次出现的位置
}

void convertion()
{
    int i = 42;
    string s = to_string(i);
    double b = stod(s);
    cout << i << ' ' << s << ' ' << b;

    string s2 = "p1=3.14";
    b = stod(s2.substr(s2.find_first_of("+-.123456789")));
    cout << endl
         << b;
}
int main()
{
    SetConsoleOutputCP(65001);
    // stringV();
    countPunct();
    cout << endl;
    test2();
    test3();
    search();
    convertion();
    system("pause");
    return 0;
}

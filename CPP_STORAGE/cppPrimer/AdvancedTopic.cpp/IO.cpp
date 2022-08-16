#include <iostream>
#include <windows.h>
#include <fstream>
#include <ostream>
#include <istream>
#include <vector>
#include <assert.h>
#include <sstream>
#include <iomanip>
#include <cmath>
using namespace std;

/*
条件状态：
strm::iostate strm是一种IO类型，iostate是一种机器相关的类型，表达提供条件状态的完整功能
strm::badbit 用来指出流已崩溃
strm::goodbit 用来指出流未处于错误状态。此值保证为0
strm::failbit  用来指出一个IO操作失败了
strm::eofbit 用来指出流到达了文件结束

s.eof() 若s流的eofbit置位，则返回true
s.fail() ~
s.bad() ~
s.good() 若s流处于有效状态，则返回true
s.clear() 将s流中所有条件状态位复位，将流的状态调整为有效，返回void
s.clear(flags) 根据给定的flags标志位，将s流中对应条件状态位复位。flags的类型为strm::iostate。返回void
s.setstate(flags) 根据给定的flags标志位，将s流中对应条件状态位复位。flags的类型为strm::iostate。返回void
s.rdstate() 返回s流的当前状态，返回值类型为strm::iostate
*/

struct PersonInfo
{
    string name;
    vector<string> phones;
};

void test()
{
    ostream *old_tie = cin.tie(nullptr); //cin不再与其他流关联（cin常常和cout默认关联）
    cin.tie(&cerr);                      //cin与cerr关联（不建议）,读取cin会刷新cout
    cin.tie(old_tie);                    //重建cin和cout的正常关联
    *old_tie << "abcdefg!";
    //untibuf所有输出操作后立刻刷新缓冲区
    cout << "abcde" << nounitbuf; //回到正确的缓冲方式
    cout << "1" << flush;         //输出，然后刷新，不添加任何字符
    cout << "hijk";
}
void test2()
{
    string pathFile("D:/TXT/pthones.TXT");
    ifstream in(pathFile);
    cin >> noskipws;
    if (in.is_open())
    {
        string line, word;
        vector<PersonInfo> people;
        while (getline(in, line))
        {
            PersonInfo info;
            istringstream record(line);
            record >> info.name;
            while (record >> word)
                info.phones.push_back(word);
            people.push_back(info);
        }
        for (const auto &v : people)
            cout << "name: " << v.name << "   number: " << v.phones.front() << endl;
    }
    else
        throw runtime_error("open file false！");
    in.close();
}

//IO库再探p666
//格式化输入/输出
void test3()
{
    //控制布尔值的格式
    cout << "default bool values: " << true << ' ' << false << "\nalpha bool values: " << boolalpha << true << ' ' << false << endl;
    cout << noboolalpha; //恢复布尔值输出默认状态
    //指定整形的进制
    //oct, hex,dec只影响整型运算对象，浮点值的表示形式不受影响
    cout << "default: " << 20 << " " << 1024 << endl;
    cout << "octal: " << oct << 20 << " " << 1024 << endl;
    cout << "hex: " << hex << 20 << " " << 1024 << endl;
    cout << "decimal: " << dec << 20 << " " << 1024 << endl;

    //在输出中指定进制
    cout << showbase;
    cout << "default: " << dec << 20 << " " << 1024 << endl;
    cout << "in octal: " << oct << 20 << " " << 1024 << endl;
    //令16进制的字母大写
    cout << "in hex: " << uppercase << hex << 20 << " " << 1024 << nouppercase << endl;
    cout << "in decimal: " << dec << 20 << " " << 1024 << endl;
    cout << noshowbase; //恢复流状态

    //控制浮点数格式、打印精度
    cout << "Precision: " << cout.precision() << ", Value: " << sqrt(2.0) << endl; //默认六位
    cout.precision(8);
    cout << "Precision: " << cout.precision() << ", Value: " << sqrt(2.0) << endl;
    cout << setprecision(12) << "Precision: " << cout.precision() << ", Value: " << sqrt(2.0) << endl;

    cout << "default format: " << 100 * sqrt(2.0) << '\n'
         << "scientfic: " << scientific << 100 * sqrt(2.0) << '\n'
         << "fixed decimal: " << fixed << 100 * sqrt(2.0) << '\n'
         << "hexadeciaml" << hexfloat << 100 * sqrt(2.0) << '\n'
         << "use defaults: " << defaultfloat << 100 * sqrt(2.0) << endl;

    //打印小数点
    cout << 10.0 << endl
         << showpoint << 10.0 << noshowpoint << endl;
    //输出补白
    int i = -16;
    double j = 3.14159;
    cout << "i: " << setw(12) << i << " next col\n"
         << "j: " << setw(12) << j << " next col\n";
    cout << left << "i: " << setw(12) << i << " next col\n"
         << "j: " << setw(12) << j << " next col\n"
         << right << "i: " << setw(12) << i << " next col\n"
         << "j: " << setw(12) << j << " next col\n";
    //在符号和值之间填充符号
    cout << internal << "i: " << setw(12) << i << " next col\n"
         << "j: " << setw(12) << j << " next col\n"
         << right;
    cout << setfill('$') << "i: " << setw(12) << i << " next col\n"
         << "j: " << setw(12) << j << " next col\n"
         << setfill(' ');

    //控制输入格式
    char c;
    cin >> noskipws;
    while (cin >> c)
        cout << c;
    cin >> skipws;
}

//未格式化的输入/输出操作(不推荐)
void test4()
{
    int chr;
    // while ((chr = cin.get()) != EOF)
    //     cout.put(chr);
    char a[50];
    cin.get(a, 20, '#');
    cout << a << endl;
    cin.unget();
    cin.getline(a, 10, '$');
    cout << a << endl;
}

//流随机访问...
void test5()
{
}
int main()
{
    SetConsoleOutputCP(65001);
    test2();
    cout << endl;
    // test3();
    // test4();
    system("pause");
    return 0;
}

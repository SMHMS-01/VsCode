#include <iostream>
#include <windows.h>
#include <tuple>
#include <vector>
#include <list>
using namespace std;

//definition、 initialization、access、operator
void test1()
{
    tuple<size_t, size_t, size_t> threeD; //true
    tuple<size_t, size_t> threeE = {10, 20};
    tuple<size_t, size_t> threeF{100, 20};
    tuple<string, vector<double>, int, list<int>> someVal("constant", {3.14, 2.718}, 42, {0, 1, 2, 3, 4, 5});
    auto item = make_tuple("1966-5-16", 'C', 'R', 3, 2.00); //实例化tuple<const char*,char,char,int,double>

    //<>内必须是常量表达式
    auto str1 = get<0>(someVal);   //访问someVal的第一个元素
    auto str2 = get<2>(someVal);   //访问someVal的第三个元素
    get<3>(someVal).front() *= 10; //assignment

    typedef decltype(item) trans;                     //trans是item的类型
    size_t sz = tuple_size<trans>::value;             //返回trans类型对象中成员的数量:5
    tuple_element<0, trans>::type cnt = get<0>(item); //cnt的类型与item中首个成员相同
    cout << cnt << endl;

    bool b = (threeF == threeE);
    bool b2 = (threeF > threeE);
    // bool b3 = (threeD < threeF);//false: different count
    // bool b4 = (someVal < threeE);//different type and count!
    cout << b << ' ' << b2 << ' ' << endl;
}

//return multiple values with tuple
void test2()
{
    
}
int main()
{
    SetConsoleOutputCP(65001);
    test1();
    system("pause");
    return 0;
}

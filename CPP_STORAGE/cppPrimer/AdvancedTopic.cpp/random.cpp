#include <iostream>
#include <windows.h>
#include <random>
using namespace std;

void test1()
{
    //分布对象：生成分布均匀的unsigned值，u(min,max)
    static uniform_int_distribution<unsigned> u(0, 100);
    //引擎对象：定义了一个调用运算符，该运算符不接受参数并返回一个随机unsigned整数，我们可以通过调用一个随机数引擎对象来生成原始随机数
    static default_random_engine e; //e可以调用对象生成随机数，e()
    for (size_t i = 0; i < 10; i++)
        cout << u(e) << " "; //将u作为随机数源，每个调用返回在指定范围内并服从均匀分布的值

    /*注意：我们传递给分布对象的是引擎对象本身，即U(E)。如果我们写成U(E()），含义就将变成E生成的下一个值传递给U，会导致一个编译错误。
            我们传递的是引擎本身，而并非他生成的下一个值，原因是某些引擎可能调用多次才能得到一个值。
            当我们说 随机数发生器 时，是指分布对象和引擎对象的组合。
        */
}

static vector<unsigned> bad_randVec()
{
    //由于我们希望引擎和分布对象保持状态，因此应该将他们定义为静态的，从而每次调用都生成新的数
    static default_random_engine e;
    static uniform_int_distribution<unsigned> u(0, 99);
    vector<unsigned> ret;
    for (size_t i = 0; i < 10; ++i)
        ret.emplace_back(u(e));
    return ret;
}

//设置随机数发生器种子
void test2()
{
    default_random_engine e1; //使用默认种子
    default_random_engine e2(6054165);

    default_random_engine e3;
    e3.seed(32763);
    default_random_engine e4(32763);
    for (size_t i = 0; i != 10; ++i)
        if (e1() == e2())
            cout << "unseeded match at iteration:" << i << endl;
        else if (e3() == e4())
            cout << "seeded differs at iteration:" << i << endl;
}

//其他随机数分布
void test3()
{
    //生成随机实数
    default_random_engine e;
    uniform_real_distribution<double> u(0, 1);
    for (size_t i = 0; i < 10; ++i)
        cout << u(e) << ends;
    uniform_real_distribution<> u2(1, 2); //<>表示使用默认结果类型：double

    //生成非随机分布的随机数
    default_random_engine e2;
    normal_distribution<> n(4, 1.5); //均值4，标准差1.5
    vector<unsigned> vals(9);
    for (size_t i = 0; i != 200; ++i)
    {
        unsigned v = lround(n(e)); //舍入到最接近的整数
        if (v < vals.size())       //如果在范围内
            ++vals[v];             //统计每个数出现了多少次
    }
    for (size_t i = 0; i < vals.size(); ++i)
        cout << i << ": " << string(vals[i], '*') << endl;
}

//  bernoulli_distribution类
static void test4()
{
    static default_random_engine e;
    bernoulli_distribution b(.35); //默认50/50，此处更改为35/65

    for (int i = 0; i != 5; ++i)
        cout << (b(e) ? "i'm go first" : "you get to go first") << endl;
}

int main()
{
    SetConsoleOutputCP(65001);
    test1();
    cout << endl;
    auto vec(bad_randVec());
    auto vec2 = bad_randVec();
    cout << (vec == vec2 ? "equal" : "non-equal") << endl;
    test2();
    test3();
    cout << endl;
    test4();
    test4();
    system("pause");
    return 0;
}

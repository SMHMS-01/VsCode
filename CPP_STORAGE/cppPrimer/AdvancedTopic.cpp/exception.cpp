// #include <iostream>
// using namespace std;

// void Test1()
// {
//     try
//     {
//         char *p = new char[0x7ffffffff]; //抛出异常
//     }
//     catch (const exception &e)
//     {
//         cout << e.what() << endl; //捕获异常，然后程序结束
//     }
// }
// int main()
// {
//     Test1();
//     system("pause");
//     return 0;
// }
#include <iostream>
#include <string>
using namespace std;
// class Exception //异常类
// {
// public:
//     Exception(const string &msg, int id)
//     {
//         _msg = msg;
//         _id = id;
//     }

//     const char *What() const
//     {
//         return _msg.c_str();
//     }

// protected:
//     string _msg;
//     int _id;
// };

// template <size_t N = 10>
// class Array
// {
// public:
//     int &operator[](size_t pos)
//     {
//         if (pos >= N)
//         {
//             Exception e("the index is invalid", 1); //出了这个作用域，抛出的异常对象就销毁了，这时会生成一个匿名对象先接受这个对象，并传到外层栈帧。
//             throw e;
//         }
//         return a[pos];
//     }

// protected:
//     int a[N];
// };

// int f()
// {
//     try
//     {
//         Array<> a;
//         a[11];
//     }
//     catch (exception &e)
//     {
//         cout << e.what() << endl; //类型不匹配，找离抛出异常位置最近且类型匹配的那个。
//     }

//     return 0;
// }

// int main()
// {
//     try
//     {
//         f();
//     }
//     catch (Exception &e)
//     {
//         cout << e.What() << endl;
//     }
//     system("pause");
//     return 0;
// }
int divide(int x, int y) // 抛异常
{
    if (y == 0)
    {
        throw x;
    }
    return x / y;
}
int main()
{
    try //接异常
    {
        cout << "8/2 = " << divide(8, 2) << endl;
        cout << "10/0 =" << divide(10, 0) << endl;
    }
    catch (int e)
    {
        cout << "e= " << e
             << " is divided by zero!" << endl;
    }
    catch (...)
    {
        cout << "未知异常" << endl;
    }

    cout << "ok" << endl;
    system("pause");
    return 0;
}

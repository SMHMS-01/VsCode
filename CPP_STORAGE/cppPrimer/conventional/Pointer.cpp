#include <iostream>
#include <windows.h>

using namespace std;

//Pointer topic
void test()
{
    //the problem of priority
    int p1;             //一个普通的整型变量
    int *p2;            //首先从P处开始，先与*结合，所以说明P是一个指针，然后再与int结合，说明指针所指向的内容的类型是int型，所以P是一个返回整形数据的指针；
    int p3[3];          //首先从P处开始，先与[]结合，说明P是一个数组，然后再与int结合，说明书阻力的元素是整型的，所以P是一个由整形数据构成的数组；
    int *p4[3];         //首先从P处开始，先与[]结合，因为其优先级比*高，所以P是一个数组，然后再与*结合，说明数组里的的元素是指针类型，然后再与int结合，
                        //说明指针所指向的内容的类型是整形的，所以P是一个有返回类型数据(此处是int型)的指针所构成的数组；
    int(*p5)[3];        //首先从P处开始，先与*结合，说明P是一个指针，然后再与[]结合(与"（）"结合这部可以忽略，只是为了改变优先级），说明指针所指向的是一个数组，
                        //然后再与int结合，说明数组里的元素是整型的，所以P是一个指向由整形数据构成的数组的指针；
    int **p6;           //二级指针：
                        //首先从P开始，先与*结合，说明P是一个指针，然后再与*结合，说明指针所指向的元素是指针，然后再与int结合，说明该指针所指向的元素是整形数据，
                        //由于二级指针以及更高级的指针极少用在复杂的类型中，所以后面更复杂的类型我们就不考虑多级指针了，最多只考虑一级指针；
    int p7(int);        //首先从P开始，先与()结合，说明P是一个函数，然后进入()中分析，说明该函数有一个整型变量的参数，然后再与外面的int结合。
                        //说明函数的返回值是一个整型数据；
    int (*p8)(int);     //首先从P开始，先与*结合，说明P是一个指针，然后再与()结合，说明指针所指向的是一个函数，然后再与()里的int结合，说明函数有一个int类型
                        //的参数，再与最外层的int结合，说明函数的返回类型是整形，所以P是一个指向有一个整型参数且返回类型为整型的函数的指针；
    int *(*p9(int))[3]; //
}
void test_2()
{
    int arr[5] = {0};
    int *ptr = arr;
    for (int i = 0; i < 5; i++)
    {
        (*ptr)++;
        ptr++;
        cout << *ptr << " " << ptr << endl;
    }
    char chr[] = "You are a girl";
    int *aptr = (int *)chr;
    aptr += 5;
    cout << *aptr << '  ' << &ptr << endl;
    char *p = chr;
    char **cptr = &p;
    cout << **cptr << endl;
    //cptr++ is invalid
    p++;
    cout << **cptr << endl;
}
void test_3()
{
    char *arr[20] = {"ad", "si", "jk"};
    char **parr = arr;
    char *str;
    str = *parr;
    cout << str << endl;
    cout << *parr << endl;
    cout << *arr << endl;
    str = *(parr + 1);
    cout << str << endl;
    str = *(parr + 2);
    cout << str << endl;
}
void test_4()
{
    int array[5] = {0, 1, 2, 3, 4};
    int(*ptr)[5] = &array;
    cout << sizeof(ptr) << endl
         << "the address of ptr: " << (*ptr)[2] << endl
         << "the address of array is :" << array << endl;
}
void test_5()
{
    struct Mystruct
    {
        int a, b, c;
    };
    struct Mystruct ss = {20, 30, 40};
    struct Mystruct *ptr = &ss;
    int *pstr = (int *)&ss;

    cout << *(++pstr) << endl;
}
int fun(char *s)
{
    int num = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        num += *s;
        s++;
    }
    return num;
}
void test_6()
{
    int fun(char *);
    int a;
    char *str = "A";
    a = fun(str);
    cout << a << endl;
}
int main()
{
    SetConsoleOutputCP(65001);
    // test_2();
    // test_3();
    // test_4();
    // test_5();
    test_6();
    system("pause");
    return 0;
}

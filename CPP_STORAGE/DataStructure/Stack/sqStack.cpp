#include <iostream>
#include <windows.h>
#define MAXSIZE 20
#define OK 1
using namespace std;
typedef int elemType;
typedef int status;

typedef struct sqStack
{
    elemType data[MAXSIZE];
    int top; //used for athe pointer of stack top
} sqStack;
status push(sqStack *s, elemType e)
{
    if (s->top == MAXSIZE - 1)
    {
        throw runtime_error("false! run out of range!\n");
    }

    s->data[s->top] = e;
    s->top++;
    return OK;
}
status pop(sqStack *s)
{
    elemType *e;
    if (s->top == -1)
    {
        throw runtime_error("false! run out of range!\n");
    }
    s->top--;
    return s->data[s->top];
}

int main()
{
    // SetConsoleOutputCP(65001);
    sqStack *s = new sqStack();
    try
    {
        for (int i = 0; i <= 11; i++)
            push(s, i);
        for (int i = 0; i <= 11; i++)
            cout << pop(s) << endl;
    }
    catch (const runtime_error &parameter)
    {
        cout << parameter.what() << endl;
    }
    delete s;
    system("pause");
    return 0;
}

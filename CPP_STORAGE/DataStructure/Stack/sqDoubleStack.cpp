#include <iostream>
#include <windows.h>
#define MAXSIZE 100
using namespace std;
typedef int elemType;
typedef int status;

typedef struct sqDoubleStack
{
    elemType data[MAXSIZE];
    //pointer of stack1
    int top1;
    //pointer of stack2
    int top2;
} sqDoubleStack;
boolean initStack(sqDoubleStack *s)
{
    cout << "Init stack ..." << endl;
    s->top1 = -1;
    s->top2 = MAXSIZE;
    return true;
}
boolean clear(sqDoubleStack *s)
{
    cout << "Clear stack ..." << endl;
    s->top1 = -1;
    s->top2 = MAXSIZE;
    return true;
}
boolean Empty(sqDoubleStack *s)
{
    if (s->top1 == -1 && s->top2 == MAXSIZE)
        return true;
    else
        return false;
}
boolean empty(sqDoubleStack *s, int stackNumber)
{
    if (stackNumber == 1)
    {
        if (s->top1 == -1)
            return true;
        else
            return false;
    }
    else if (stackNumber == 2)
    {
        if (s->top2 == MAXSIZE)
            return true;
        else
            return false;
    }
}
int length(sqDoubleStack *s)
{
    cout << "Stack length ..." << endl;
    return s->top1 + 1 + MAXSIZE - s->top2;
}
status getTop(sqDoubleStack *s, int stackNumber)
{
    if (stackNumber == 1)
        if (s->top1 == -1)
            cout << "stack1 is empty!\n";
        else
            return s->data[s->top1];
    if (stackNumber == 2)
        if (s->top2 == MAXSIZE)
            cout << "stack2 is empty!\n";
        else
            return s->data[s->top2];
}

status push(sqDoubleStack *s, elemType e, int stackNumber)
{
    //top1+1=top2 is a condition that judging whether stack is full
    if (s->top1 + 1 == s->top2)
        throw runtime_error("the stack is full!\n");
    //push element into stack1
    if (stackNumber == 1)
        s->data[++s->top1] = e;
    else if (stackNumber == 2) //push element to stack2
        s->data[--s->top2] = e;
    return true;
}
status pop(sqDoubleStack *s, int stackNumber)
{
    if (stackNumber == 1)
    {
        if (s->top1 == -1) //top1=-1 is fundamental condition to judge whether stack1 is full
            throw runtime_error("the stack1 is full!\n");
        return s->data[s->top1--];
    }
    else if (stackNumber == 2)
    {
        if (s->top2 == MAXSIZE) //top2=MAXSIZE is fundamental condition to judge whether stack1 is full
            throw runtime_error("the stack2 is full!\n");
        return s->data[s->top2++];
    }
    return 0;
}
void outputToop(sqDoubleStack *s)
{
    while (!empty(s, 1))
    {
        cout << pop(s, 1) << endl;
    }
    while (!empty(s, 2))
    {
        cout << pop(s, 2) << endl;
    }
}
int main()
{
    SetConsoleOutputCP(65001);
    sqDoubleStack *s = NULL;
    s = new sqDoubleStack();
    initStack(s);

    try
    {
        for (int i = 0; i <= 9; i++)
            push(s, i, 1);
        for (int i = 0; i <= 9; i++)
            push(s, i + 10, 2);
        // for (int i = 0; i <= 10; i++)
        //     cout << pop(s, 2) << endl;
        // for (int i = 0; i <= 9; i++)
        //     cout << pop(s, 1) << endl;
    }
    catch (const runtime_error &parameter)
    {
        cout << parameter.what() << endl;
    };
    cout << "\n"
         << length(s) << "and the stack1's length is  " << s->top1 << endl;
    ;
    outputToop(s);
    clear(s);
    outputToop(s);
    delete s;
    s = NULL;
    system("pause");
    return 0;
}

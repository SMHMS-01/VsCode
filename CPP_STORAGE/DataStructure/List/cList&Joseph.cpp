#include <iostream>
#include <windows.h>

using namespace std;
typedef int elemType;
typedef struct node
{
    elemType data;
    struct node *next;

} node;
node *initNode(int total) //'total'' is the total of node
{
    int tempData = 0;
    int i = 0;
    node *head; //head pointer
    node *p;    //a pointer counter
    p = new node;
    head = p;
    cout << "please input a number to define total of queue:\t" << endl;
    for (i = 1; i <= total; i++)
    {
        cout << "the " << i << "th number ";
        cin >> tempData;
        p->data = tempData;
        if (i < total) //a circle
        {
            p->next = new node;
            p = p->next;
        }
        else if (i == total) //when i=total means finshed a circle
        {
            p->next = head;
            cout << p->next->data << endl;
            break;
        }
    }
    return head;
}

void outputList(node *head, int n)
{
    node *p = head;
    for (int i = 0; i < n; i++)
    {
        cout << p->data << '\t';
        p = p->next;
    }
    cout << endl;
}
void run(node *head, int total, int outset, int interval) //total is total of node
{
    node *p;
    node *front;      //the front node of deleted node
    node *back;       //the back node of deleted node
    node *spare_head; //a spare node that reverse for deleted head
    node *del;        //will deleted node
    int count = 1;    //counter to record member of node
    p = front = head;
    for (int i = 1; i < outset; i++)
    {
        front = p;
        p = p->next;
    }
    while (head)
    {
        if (total == 1)
        {
            cout << "the last report number is " << head->data << "\n";
            return;
        }
        for (int i = 0; i < interval; i++, p = p->next)
        {
            if (i == interval - 2)
                front = p;
            del = p;
            back = p->next;
        }
        front->next = back;
        if (del == head)
        {
            spare_head = del->next;
            head = spare_head;
        }
        cout << "the " << count << "th deleted member is " << del->data << endl;
        delete del;
        total--;
        cout << "after the " << count << "th, the queue member is ";

        count++;
        outputList(head, total);
        cout << endl;
        p = back;
    }
}
int main()
{
    SetConsoleOutputCP(65001);
    node *head;
    int total, outset, interval;
    char c;
    while (1)
    {
        cout << "please respectively input total:";
        cin >> total;
        head = initNode(total);
        cout << "the constructed queue is :" << endl;
        outputList(head, total);
        cout << "please input the first number of member\t";
        cin >> outset;
        cout << "please input the interval:\t";
        cin >> interval;
        cout << endl;
        if (outset > total)
        {
            cout << "FAILED!\nYOU INPUTED NUMBER IS INVALID!\nplease input again!\n";
            cin >> interval;
        }
        run(head, total, outset, interval);
        cout << "Do you want play it again?(Y or N)\t";
        cin >> c;
        switch (c)
        {
        case 'Y':
            continue;
            break;
        case 'N':
            exit(0);
        default:
            break;
        }
    }
    system("pause");
    return 0;
}

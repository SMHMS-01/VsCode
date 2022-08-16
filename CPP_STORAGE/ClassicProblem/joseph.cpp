#include <windows.h>
#include <iostream>
using namespace std;
int T = 1; //定义一个全局变量T用以计算操作次数
//定义一个约瑟夫节点结构体j_node
//------------------------------
struct j_node
{
    int data;     //节点保存的数据
    j_node *next; //指向下一节点的指针
};
//循环链表的赋值
//---------------------
j_node *Initnode(int n) //参数n是总共的节点数
{
    int temp_date = 0;
    int i = 0;
    j_node *head; //定义节点的头指针
    j_node *p;
    head = p = new j_node; //新创建节点
    cout << "请输入" << n << "个数字：" << endl;
    for (i = 1; i <= n; i++)
    {
        cout << "第" << i << "个：";
        cin >> temp_date;    //输入的节点数据temp
        p->data = temp_date; //将输入的节点数据赋值给节点
        if (i < n)
        {
            p->next = new j_node; //节点指针指向新创建的节点
            p = p->next;          //指针后移
        }
        else if (i == n)
        {
            p->next = head; //已经到达尾节点，让其指向头结点，以构成循环链表
            break;
        }
    }
    cout << p->next->data << endl; //将尾节点的下一节点输出，以验证是否构成循环链表
    return head;                   //返回头指针
}
//------------------
//链表输出函数

void Output_node(j_node *head, int n) //参数分别是头指针head，节点总数n
{
    j_node *p;
    p = head;
    for (int i = 0; i < n; i++)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}
//-------------------------------
//执行函数
void Done(j_node *head, int n, int a, int b) //参数分别是头指针head，节点总数n，第一个报数的号a，报数的号码b
{
    j_node *p;        //计数指针
    j_node *front;    //存放删除前节点
    j_node *back;     //存放删除后节点
    j_node *del;      //存放删除节点
    j_node *new_head; //存放新的头指针
    p = front = head;
    //-----------------
    //这个for循环作用：找出第一个报数的节点
    for (int i = 1; i < b; i++)
    {
        front = p;
        p = p->next;
    }
    //----------------
    while (head)
    {
        //判断当n==1时，也就是链表剩下最后一个节点时，结束删除
        if (n == 1)
        {
            cout << "最后一个报数的是：" << head->data << endl;
            cout << "问题已解决！" << endl;
            return;
        }
        //-------------------------------
        //这个for循环的作用是找出要删除的节点，及其后的节点
        for (int i = 0; i < a; i++, p = p->next)
        {
            if (i == a - 2)
            {
                front = p; //要删除的前一个节点
            }
            del = p;        //要删除的节点
            back = p->next; //要删除的后一个节点
        }
        //------------------------------------
        front->next = back; //要删除的前节点指向要删除的后节点
        //------------
        //判断如果要删除的是头结点的话，就让del->next成为新的头结点
        if (del == head)
        {
            new_head = del->next;
            head = new_head; //新的头结点赋值给头结点
        }
        cout << "第" << T << "次删除的节点是:  " << del->data << endl;
        delete del; //删除节点
        n--;        //链表的长度减一
        cout << "第" << T << "次操作之后的链表是:  ";
        T++;
        Output_node(head, n); //输出删除节点后链表的情况
        cout << endl;
        p = back; //让删除节点的后一个付给p，以构成循环计算
    }
}
//--------------------------
//主函数
int main()
{
    SetConsoleOutputCP(65001);
    j_node *head;
    int a, n, b;
    char c;
    while (1)
    {
        cout << endl;
        cout << "请分别输入总人数 n：" << endl;
        cin >> n;
        head = Initnode(n); //头结点指向初始化好的循环链表
        cout << "所创建的链表为：" << endl;
        Output_node(head, n);
        cout << "请输入第一个报数的号码：" << endl;
        cin >> b;
        cout << "请输入报的号数：" << endl;
        cin >> a;
        if (b > n)
        {
            cout << "输入报数的号码不合法！" << endl;
            cout << "请再次输入： ";
            cin >> a;
        }
        Done(head, n, a, b);
        cout << "是否再来一次（Y or N）： ";
        cin >> c;
        if (c == 'N')
            exit(0);
        else
            continue;
    }
    return 0;
}
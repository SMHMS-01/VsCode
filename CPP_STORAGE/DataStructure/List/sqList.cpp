/*
Sequential storage struture of linear table
*/
#include <iostream>
#include <windows.h>

#define MAXSIZE 20 //the MaxSize of array
#define ERROR 0
#define OK 1
using namespace std;
typedef int elemType; //elemType accroding to the specific situation, the assumption here is type int
typedef int status;   //the type of function, accroding to the spcific situation
class sqList
{
private:
   elemType data[MAXSIZE];
   int length; //the length of linear table
public:
   sqList(int _lengthDef, elemType *arr);
   ~sqList();
   void unionList(sqList *La, sqList *Lb);
   void showList();
   status locateElem(sqList *L, int e);
   status getElem(sqList *L, int i, elemType *e);    //get element
   status listInsert(sqList *L, int i, elemType *e); //insert element
   status listDelete(sqList *L, int i, elemType &e); //delete element
};

sqList::sqList(int _lengthhDef, elemType arr[])
{
   length = _lengthhDef;
   for (int i = 0; i < length; i++)
      data[i] = arr[i];
   if (length > MAXSIZE)
      throw runtime_error("the length of linear table is greater than the MAXSIZE OF array\n ERROR!\n");
   try
   {
   }
   catch (const runtime_error &chr)
   {
      cout << chr.what() << endl;
   }
}
sqList::~sqList()
{
}
void sqList::showList()
{
   for (int i = 0; i < length; i++)
      cout << data[i] << endl;
}
status sqList::locateElem(sqList *L, int e)
{
   for (int i = 0; i < L->length; i++)
   {
      if (L->data[i] == e)
         return i + 1;
      else
         return ERROR;
   }
}
void sqList::unionList(sqList *La, sqList *Lb)
{
   int La_len, Lb_len, i;
   elemType e;
   La_len = La->length;
   Lb_len = Lb->length;
   for (i = 1; i <= Lb_len; i++)
   {
      getElem(Lb, i, &e);
      if (!locateElem(La, e))
         listInsert(La, ++La_len, &e);
   }
}
status sqList::getElem(sqList *L, int i, elemType *e)
{
   if (L->length == 0 || i < 1 || i > L->length)
      return ERROR;
   *e = L->data[i - 1];
   return *e;
}
status sqList::listInsert(sqList *L, int i, elemType *e)
{
   int exch;
   if (L->length == MAXSIZE || i < 1 || i > L->length + 1) //linear table is full or i is not in range
      return ERROR;
   if (i <= L->length) //insert position is not at the end of the table
   {
      for (exch = L->length - 1; exch >= i - 1; exch--) //move back all elements at the back position of inserted element
         L->data[exch + 1] = L->data[exch];
   }
   L->data[i - 1] = *e; //insert new element
   L->length++;         //lengthen the array
   return OK;
}
status sqList::listDelete(sqList *L, int i, elemType &e)
{
   int exch;
   if (L->length == 0 || i < 1 || i > L->length) //delete position is false
      return ERROR;
   e = L->data[i - 1]; //assign value, change data(delete)
   if (i < L->length)  //if delete position is not at the end
   {
      for (exch = i; exch < L->length; exch++) //move forward all elements at the front position of delete element
         L->data[exch - 1] = L->data[exch];
      L->length--;
      return e;
   }
}
void test()
{
   elemType test[19] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
   elemType test_2[19] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 110, 111, 112, 113, 114, 115, 116, 117, 118};
   sqList *_try = new sqList(19, test);
   sqList *_try_2 = new sqList(19, test_2);
   _try->showList();
   cout << "exchanged1 is " << endl;
   elemType del;
   _try->listDelete(_try, 17, del);
   _try->showList();
   cout << "the deleted val is " << del << endl
        << endl;
   cout << "exchanged2 is " << endl;
   _try->listInsert(_try, 17, &del);
   _try->showList();
   cout << "unioned is " << endl;
   _try->unionList(_try, _try_2);
   _try->showList();
}
int main()
{
   SetConsoleOutputCP(65001);
   test();
   system("pause");
   return 0;
}

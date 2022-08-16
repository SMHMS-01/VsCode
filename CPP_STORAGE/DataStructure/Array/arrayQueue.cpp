#include <iostream>
#include <windows.h>

using namespace std;
class queue
{
private:
   int maxSize; //means the Max size of array
   int front;   //pointer to head of array
   int rear;    //pointer to tail of array
   int *arr;    //the array used for store data, simulate queue

public:
   queue(int arrMaxSize);
   ~queue();
   boolean isFull();           //Determind weather the queue is full
   boolean isEmpty();          //Determind weather the queue is empty
   void addQueue(int addData); //add data to queue
   int getQueue();             //get data from queue
   void showQueue();           //show common data
   int headQueue();
};

queue::queue(int arrMaxSize)
{
   maxSize = arrMaxSize;
   arr = new int[maxSize];
   front = -1; //指向队列的头，分析出front是指向队列头部的前一个位置
   rear = -1;  //指向队列尾，指向队列尾的数据（即是队列最后一个数据）
}

queue::~queue()
{
   delete[] arr;
}

boolean queue::isFull()
{
   return rear == maxSize - 1;
}

boolean queue::isEmpty()
{
   return rear == front;
}

void queue::addQueue(int addData)
{
   if (isFull())
   {
      cout << "The queue is full!" << endl;
      return;
   }
   rear++; //make rear move back or we can
   arr[rear] = addData;
}

int queue::getQueue()
{
   if (isEmpty())
   {
      //deal with it via throw a exception
      throw "the queue is empty, you can't get any data!";
   }
   front++; //front move back
   return arr[front];
}

void queue::showQueue()
{
   if (isEmpty())
   {
      //deal with it via throw a exception
      throw "the queue is empty, you can't get any data!";
   }
   for (int i = 0; i < maxSize; i++)
   {
      cout << "arr[" << i << "]= " << arr[i] << '\t';
   }
   cout << endl;
}
int queue::headQueue()
{
   if (isEmpty())
   {
      //deal with it via throw a exception
      throw "the queue is empty, you can't get any data!";
   }
   return arr[front + 1];
}
void test()
{
   queue *arrayQueue = new queue(4);
   char key = ' ';
   bool loop = true;
   while (loop)
   {
      cout << "s(show): show queue" << endl
           << "e(exit): exit the program" << endl
           << "a(add): add data to queue" << endl
           << "h(head): view the data of the queue's head" << endl
           << "g(get): get data from the queue" << endl;
      cin >> key;
      switch (key)
      {
      case 's':
         arrayQueue->showQueue();
         break;
      case 'e':
         cin.clear();
         loop = false;
         break;
      case 'a':
         cout << "output a number:";
         cin.sync();
         int val;
         cin >> val;
         arrayQueue->addQueue(val);
         break;
      case 'g':
         try
         {
            int res = arrayQueue->getQueue();
            cout << "got the data is" << res;
         }
         catch (const std::exception &e)
         {
            std::cerr << e.what() << endl;
         }
         break;
      case 'h':
         try
         {
            int res = arrayQueue->headQueue();
            cout << "the head data of queue is " << res << endl;
         }
         catch (const std::exception &e)
         {
            std::cerr << e.what() << '\n';
         }
         break;
      default:
         break;
      }
   }
   cout << "the program is exit" << endl;
}
int main()
{
   SetConsoleOutputCP(65001);
   test();
   system("pause");
   return 0;
}

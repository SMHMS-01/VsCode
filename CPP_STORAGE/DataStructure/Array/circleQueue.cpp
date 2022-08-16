#include <iostream>
#include <windows.h>

using namespace std;

class circleQueue
{
private:
    int maxSize; //means the Max size of array
    int front;   //pointer to head element of array
    int rear;    //pointer to tail element's last of array
    int *arr;    //the array used for store data, simulate queue
public:
    circleQueue(int max);
    ~circleQueue();
    boolean isFull();           //Determind weather the queue is full
    boolean isEmpty();          //Determind weather the queue is empty
    void addQueue(int addData); //add data to queue
    int getQueue();             //get data from queue
    void showQueue();           //show common data
    int headQueue();
    int length();
};

circleQueue::circleQueue(int max) : maxSize(max)
{
    arr = new int[max];
    front = 0, rear = 0; //their value is zero defaultly
}

circleQueue::~circleQueue()
{
}
boolean circleQueue::isFull()
{
    return (rear + 1) % maxSize == 0;
}
boolean circleQueue::isEmpty()
{
    return rear == front;
}
void circleQueue::addQueue(int addData)
{
    if (isFull())
    {
        cout << "The queue is full!" << endl;
        return;
    }
    arr[rear] = addData;
    //make rear move back, because the problem of CIRCULAR QUEUES, we must consider modulo
    rear = (rear + 1) % maxSize;
}
int circleQueue::getQueue()
{
    if (isEmpty())
    {
        //deal with it via throw a exception
        throw std::runtime_error("the queue is empty, you can't get any data!");
    }
    //Due to the front pointer to the first element of the queue, so we need consider some problems
    //1.we need store a temporal variable to save the value of the front
    //2.make front move back
    //3.return temporal variable
    int value = arr[front];
    front = (front + 1) % maxSize;
    return value;
}
int circleQueue::length()
{
    return (rear - front + maxSize) % maxSize;
}
void circleQueue::showQueue()
{
    if (isEmpty())
    {
        //deal with it via throw a exception
        throw std::runtime_error("the queue is empty, you can't get any data!");
    }
    //start from front to rear
    for (int i = 0; i < length(); i++) //valid length
    {
        cout << "arr[" << i % maxSize << "]= " << arr[i % maxSize] << '\t';
    }
    cout << endl;
}
int circleQueue::headQueue()
{
    if (isEmpty())
    {
        //deal with it via throw a exception
        throw std::runtime_error("the queue is empty, you can't get any data!");
    }

    return arr[front];
}
void test()
{
    circleQueue *Queue = new circleQueue(3);
    char key = ' ';
    bool loop = true;
    while (loop)
    {
        cout << "s(show): show queue" << endl
             << "e(exit): exit the program" << endl
             << "a(add): add data to queue" << endl
             << "h(head): view the data of the queue's head" << endl
             << "g(get): get data from the queue" << endl
             << endl;
        cin >> key;
        switch (key)
        {
        case 's':
            Queue->showQueue();
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
            Queue->addQueue(val);
            break;
        case 'g':
            try
            {
                int res = Queue->getQueue();
                cout << "got the data is" << res << endl;
            }
            catch (const std::runtime_error &_str)
            {
                std::cout << _str.what() << endl;
            }
            break;
        case 'h':
            try
            {
                int res = Queue->headQueue();
                cout << "the head data of queue is " << res << endl;
            }
            catch (const std::runtime_error &e)
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

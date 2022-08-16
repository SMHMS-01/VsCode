#include <iostream>
#include <windows.h>
#include <memory>
using namespace std;

//条款28：避免返回handles指向对象内部成分
//避免返回handles(包括references、指针、迭代器)指向对象内部。遵循这个条款可增加封装性，帮助const成员函数的行为像个const，并
//将发生"虚吊号码牌"的可能性降至最低
class Point
{
public:
   Point(int x, int y) : x(x), y(y) {}
   void setX(int newval) { x = newval; }
   void setY(int newval) { y = newval; }

private:
   int x, y;
};
struct RectData
{
   Point ulhc;
   Point lrhc;
};

class RectAngle
{
public:
   RectAngle(const Point &, const Point &) {}
   // const Point &upperLeft() const { return pData->lrhc; }
   Point &upperLeft() const { return pData->lrhc; }
   // Point &lowerRight() const { return pData->ulhc; }
   const Point &lowerRight() const { return pData->ulhc; }

   //另一种返回值设置
   const Point LowerRight() const { return pData->ulhc; } //值形式返回，返回之后那个值就会被销毁，因此如果是个指针指向它的话就会空悬

private:
   shared_ptr<RectData> pData;
};

void test()
{
   Point coord1(0, 0), coord2(100, 100);
   const RectAngle rec(coord1, coord2); //rec是个const矩形（0，0）->（100，100)
   rec.upperLeft().setX(50);            //现在rec却变成了（50，0）->（100，100）
   //实际上上述操作使得封装性被破坏，Point calss 的private里的数据变成了public，原因是因为"成员函数返回references"
   //一个解决方式就是将返回的reference变为const的

   const Point *uLowerRight = &rec.LowerRight(); //false：空悬、虚吊
   cout << (uLowerRight ? "exist" : "disapper") << endl;
}
int main()
{
   SetConsoleOutputCP(65001);
   test();
   system("pause");
   return 0;
}

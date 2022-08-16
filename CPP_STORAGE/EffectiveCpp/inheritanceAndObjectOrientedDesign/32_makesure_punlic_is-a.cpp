#include <iostream>
#include <windows.h>
#include <assert.h>
using namespace std;

//确定你的public继承塑造出is-a关系
//is-a并非是唯一存在于classes之间的关系。另外两个常见的关系是has-a和is-implement-in-terms-of(根据某物实现出)。参考条款38、39
//"public继承"意味着is-a。适用于base classes身上的每一件事情也一定适用于derived classes身上，因为每一个derived class对象也都是一个base class对象。

class Bird
{ //未声明fly函数
};
class Penguin : public Bird
{ //未声明fly函数
};
void testone()
{
   Penguin p;
   // p.fly();//:false
}
class RECTANGLE
{
public:
   virtual void setHeight(int newHeight) { height = newHeight; }
   virtual void setWidth(int newWidth) { width = newWidth; }
   virtual int getHeight() const { return height; }
   virtual int getWidth() const { return width; }

private:
   unsigned int height;
   unsigned int width;
};

class Square : public RECTANGLE
{
};
void makeBigger(RECTANGLE &r)
{
   int oldHeight = r.getHeight();
   r.setWidth(r.getWidth() + 10);
   assert(r.getHeight() == oldHeight); //判断r的高度是否被改
}

void test()
{
   Square s;
   assert(s.getWidth() == s.getHeight()); //这对所有正方形一定为真
   makeBigger(s);
   assert(s.getHeight() == s.getWidth()); //对所有正方形应该为真，此处为假
}
int main()
{
   SetConsoleOutputCP(65001);
   system("pause");
   return 0;
}

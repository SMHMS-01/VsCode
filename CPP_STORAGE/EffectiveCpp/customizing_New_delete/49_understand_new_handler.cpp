#include <iostream>
#include <windows.h>

using namespace std;

//条款49：了解new handler的行为
//set_new_handler允许客户指定一个函数，在内存分配无法获得满足时调用
//Nothrow new是一个颇为局限的工具，因为它只适用于内存分配；后继的构造函数调用还是可能抛出异常

//标准库函数
//一个良好的new-handler函数必须做以下事情：
//1.让更多内存可被使用；
//2.安装另一个new-handler（或修改自身）
//3.卸除new-handler
//4.抛出bad_alloc(或派生自bad_alloc)的异常。这样的异常不会被operator new捕捉，因此会被传播到内存索求处
//5.不返回，通常调用abort或exit

namespace std
{
   typedef void (*new_handler)();
   new_handler set_new_handler(new_handler p) throw();
}

void outOfMem()
{
   std::cerr << "Unable to satisfy request for memory\n";
   std::abort();
}

template <typename T>
class NewHandlerSupport
{
public:
   static std::new_handler set_new_handler(std::new_handler p) throw();
   static void *operator new(std::size_t size) throw();

private:
   static std::new_handler currentHandler;
};
template <typename T>
std::new_handler NewHandlerSupport<T>::currentHandler = 0;

template <typename T>
std::new_handler NewHandlerSupport<T>::set_new_handler(std::new_handler p) throw()
{
   std::new_handler olderHander = currentHandler;
   currentHandler = p return olderHander;
}

template <typename T>
void *NewHandlerSupport<T>::operator new(std::size_t size) throw()
{
   NewHandlerSupport h(std::set_new_handler(currentHandler));
   return ::operator new(size);
}

class Widget : public NewHandlerSupport<Widget>
{
};

void test()
{
}
int main()
{
   SetConsoleOutputCP(65001);
   std::set_new_handler(outOfMem);
   system("pause");
   return 0;
}

#include <iostream>
#include <windows.h>
#include <vector>
#include <array>
#include "defalloc.hpp"
using namespace std;

/*
以 STL 的運用角度而言，空間配置器是最不需要介紹的東西，它總是隱藏在一切 組件（更具體㆞說是指容器，container）的背後，默默工作默默付出。
但若以 STL 的實作角度而言，第㆒個需要介紹的就是空間配置器，因為整個 STL 的操作對象 （所有的數值）都存放在容器之內，而容器㆒定需要配置空間以置放資料。
不先 掌握空間配置器的原理，難免在觀察其他 STL 組件的實作時處處遇到擋路石。
為什麼不說 allocator 是記憶體配置器而說它是空間配置器呢？因為，空間不㆒定 是記憶體，空間也可以是磁碟或其他輔助儲存媒體。
是的，你可以寫㆒個 allocator， 直接向硬碟取空間1。以㆘介紹的是 SGI STL 提供的配置器，配置的對象，呃，是的，是記憶體。
*/
/*
allocator::value_type 
allocator::pointer 
allocator::const_pointer 
allocator::reference 
allocator::const_reference 
allocator::size_type
allocator::difference_type

allocator::rebind 
一個巢狀的（nested）class template。class rebind<U> 擁有唯一成員 other， 那是一個 typedef，代表 allocator<U>。

allocator::allocator()  
————default constructor。

allocator::allocator(const allocator&)  
————copy constructor。

template <class U>allocator::allocator(const allocator<U>&)     
泛化的 copy constructor。

allocator::~allocator() 
————default constructor。

pointer allocator::address(reference x) 
const 傳回某個物件的位址。算式 a.address(x) 等同於 &x。

const_pointer allocator::address(const_reference x) const 
傳回某個 const 物件的位址。算式 a.address(x) 等同於 &x。 

pointer allocator::allocate(size_type n, cosnt void* = 0)
配置空間，足以儲存 n 個 T 物件。第㆓引數是個提示。實作㆖可能會利用它來 增進區域性（locality），或完全忽略之
。
void allocator::deallocate(pointer p, size_type n) 
歸還先前配置的空間。

size_type allocator::max_size() const 
傳回可成功配置的最大量。
.
void allocator::construct(pointer p, const T& x) 
等同於 new(const void*) p) T(x)。

void allocator::destroy(pointer p)
等同於 p->~T()。
*/
int main()
{
    SetConsoleOutputCP(65001);
    int ia[]{0, 1, 2, 3, 4};
    unsigned i;
    vector<int, SGI::allocator<int>> iv(ia, ia + 5);
    for (i = 0; i < iv.size(); ++i)
        cout << iv[i] << ' ';
    cout << endl;
    array<int, 20> a;
    int *b = &a.front();
    int *c = b + a.size();
    ptrdiff_t dif = c - b;
    cout << dif << endl;
    system("pause");
    return 0;
}
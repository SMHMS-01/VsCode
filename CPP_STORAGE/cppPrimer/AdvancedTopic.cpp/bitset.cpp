#include <iostream>
#include <windows.h>
#include <bitset>
#include <vector>
using namespace std;

//definition、initialization、access
void test1()
{
   //用unsigned 值初始化bitset
   //bitvec1比初始值小；初始值中的高位被丢弃
   bitset<13> bitvec1(0xbeef);
   //bitvec2比初始值大；它的高位被置为0
   bitset<20> bitvec2(0xbeef);
   //在64位机器中，long long 0ULL是64个0比特，因此~0ULL是64个1
   bitset<128> bitvec3(~0ULL); //0~63是 1；63~127位是0

   //从string初始化bitset
   bitset<32> bitvec4("1100"); //2,3两位为1，其余为0
   string str("111111110000001010011110101111000");
   bitset<32> bitvec5(str, 5, 4);
   bitset<32> bitvec6(str, str.size() - 10);
   cout << bitvec6 << endl;
}
int main()
{
   SetConsoleOutputCP(65001);
   test1();
   system("pause");
   return 0;
}

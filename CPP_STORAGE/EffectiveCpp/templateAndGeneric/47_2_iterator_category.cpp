#include <iostream>
#include <windows.h>

using namespace std;
//条款47:请使用traits classes表现类型信息plus

// 迭代器相應型別之五：iterator_category

//  Input Iterator：這種迭代器所指物件，不允許外界改變。唯讀（read only）。  Output Iterator：唯寫（write only）。
//  Forward Iterator：允許「寫入型」演算法（例如 replace()）在此種迭代 器所形成的區間㆖做讀寫動作。
//  Bidirectional Iterator：可雙向移動。某些演算法需要逆向走訪某個迭代器區 間（例如逆向拷貝某範圍內的元素），就可以使用 Bidirectional Iterators。
//  Random Access Iterator：前㆕種迭代器都只供應㆒部份指標算術能力（前㆔ 種支援 operator++，第㆕種再加㆖ operator--），第五種則涵蓋所有指
// 標算術能力，包括 p+n, p-n, p[n], p1-p2, p1<p2。

//以 advanced() 為例
template <typename InputIterator, typename Distance>
void advance_II(InputIterator &i, Distance n)
{
    //单向，逐一前行
    while (n--) //for(;n>0;--n,++i);
        ++i;
}

template <typename BidirectionalIterator, typename Distance>
void advance_BI(BidirectionalIterator &i, Distance n)
{
    //双向，逐一前进
    if (n >= 0)
        while (n--)
            ++i;
    else
        while (n++)
            --i;
}

template <typename RandomAccessIterator, typename Distance>
void advance_RAI(RandomAccessIterator &i, Distance n)
{
    //双向，跳跃前进
    i += n;
}

int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}

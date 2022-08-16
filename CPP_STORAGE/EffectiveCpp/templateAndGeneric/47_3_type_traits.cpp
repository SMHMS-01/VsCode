#include <iostream>
#include <windows.h>

using namespace std;
//条款47:请使用traits classes表现类型信息plusplus

// SGI STL 的私房菜：__type_traits
/*traits 編程技法很棒，適度彌補了 C++ 語言本身的不足。STL 只對迭代器加以 規範，制定出 iterator_traits 這樣的東西。
SGI 把這種技法進㆒步擴大到迭 代器以外的世界，於是有了所謂的 __type_traits。雙底線前綴詞意指這是 SGI
STL內部所用的東西，不在 STL 標準規範之內。*/

/*
iterator_traits 負責萃取迭代器的特性，__type_traits 則負責萃取型別（type）的特性。此處我們所關注的型別特性是指：
這個型別是否具備 non-trivial defalt ctor？
是否具備 non-trivial copy ctor？
是否具備 non-trivial assignment operator？
是否具備 non-trivial dtor？
如果答案是否定的，我們在對這個型別進行 建構、解構、拷貝、賦值等動作時，就可以採用最有效率的措施（例如:
根本不喚 起尸位素餐的那些 constructor, destructor），而採用記憶體直接處理動作如 malloc()、memcpy() 等等，獲得最高效率。
這對於大規模而動作頻繁的容器，有著顯著的效率提昇。

*/

struct _true_type
{
};
struct _false_type
{
};
template <typename type>
struct _type_traits
{
    typedef _true_type this_dummy_member_must_be_first; /* 不要移除這個成員。它通知「有能力自動將 __type_traits 特化」 的編譯器說，
    我們現在所看到的這個 __type_traits template 是特殊的。這是為了確保萬㆒編譯器也使用㆒個名為 __type_traits 而其 實與此處定義並無任何關聯的 template 時，所有事情都仍將順利運作。*/

    typedef _false_type has_trivial_default_constructor;
    typedef _false_type has_trivial_copy_constructor;
    typedef _false_type has_trivial_assignment_operator;
    typedef _false_type has_trivial_destructor;
    typedef _false_type is_POD_type;
};

int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}

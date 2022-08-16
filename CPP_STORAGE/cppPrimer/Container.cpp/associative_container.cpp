#include <iostream>
#include <windows.h>
#include <algorithm>
#include <vector>
#include <deque>
#include <array>
#include <numeric>
#include <iterator>
#include <functional>
#include <list>
#include <map>
#include <set>
using namespace std;

void add_find_erase_others()
{
    vector<int> ivec{2, 4, 6, 8, 2, 4, 6, 8, 9};
    set<int> set2;
    set2.insert(ivec.cbegin(), ivec.cend());
    cout << set2.size() << endl;
    set2.insert({1, 3, 5, 7, 1, 3, 5, 7});
    cout << set2.size() << endl; //Non-prepeat
    auto it = set2.find(8);
    auto it2 = set2.find(10);
    cout << *it << endl;
    cout << *it << endl; //if non-exist, return end()
    //count() used for count...
    // count() 在不允许重复元素的容器里和find基本没啥区别

    auto it3 = set2.lower_bound(6); //return a iterator is not less than number
    cout << *it3 << endl;
    auto it4 = set2.upper_bound(8);
    cout << *it4 << endl;
    auto it5 = set2.equal_range(7);
    cout << *(it5.first) << " " << *(it5.second) << endl;

    map<string, size_t> m1;
    m1.insert({string("Akemi"), 1});
    m1.insert(pair<string, size_t>(" Sai", 3));
    m1.insert(make_pair(" Homura", 2));
    m1.insert(map<string, size_t>::value_type("Ko", 4));
    // m1.erase(m1.begin(), m1.end());
    m1.erase(m1.cbegin());
    for (const auto &m : m1)
        cout << m.first << "->" << m.second << ends;
}

//无序容器
void unordered()
{
    unordered_map<string, size_t> um;
}
int main()
{
    SetConsoleOutputCP(65001);
    add_find_erase_others();
    system("pause");
    return 0;
}

#include <iostream>
#include <windows.h>
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;

//我第一讨厌不写注释的人，第二讨厌写注释

int nextPrime(const int n);
template <typename T>
class HashTable
{

public:
    HashTable(int size = 101);
    int insert(const T &x);
    int remove(const T &x);
    int contains(const T &x);
    void make_empty();
    void display() const;

private:
    vector<list<T>> lists;
    size_t currentSize;
    int hash(const string &key);
    int myHash(const T &x);
    void rehash();
};

template <typename T>
HashTable<T>::HashTable(int size)
{
    lists = vector<list<T>>(size);
    currentSize = 0;
}

template <typename T>
int HashTable<T>::hash(const string &key)
{
    int hashVal = 0;
    int tableSize = lists.size();
    size_t i = 0;
    for (i = 0; i < (size_t)key.length(); i++)
        hashVal = hashVal * 37 + key[i];
    hashVal = hashVal % tableSize;
    if (hashVal < 0)
        hashVal += tableSize;
    return hashVal;
}

template <typename T>
int HashTable<T>::myHash(const T &x)
{
    string key = x.getName();
    return hash(key);
}

template <typename T>
int HashTable<T>::insert(const T &x)
{
    list<T> &whichlist = lists[myHash(x)];
    if (find(whichlist.begin(), whichlist.end(), x) != whichlist.end())
        return 0;
    whichlist.push_back(x);
    currentSize++;
    if (currentSize > lists.size())
        rehash();
    return 1;
}

template <typename T>
int HashTable<T>::remove(const T &x)
{
    typename list<T>::iterator iter;
    list<T> &whichlist = lists[myHash(x)];
    iter = find(whichlist.begin(), whichlist.end(), x);
    if (iter != whichlist.end())
    {
        whichlist.erase(iter); // delete x
        currentSize--;
        return 1;
    }
    return 0;
}

template <typename T>
int HashTable<T>::contains(const T &x)
{
    list<T> whichlist;
    whichlist = lists[myHash(x)];
    if (find(whichlist.begin(), whichlist.end(), x) != whichlist.end())
        return 1;
    else
        return 0;
}

template <typename T>
void HashTable<T>::make_empty()
{
    int i;
    for (i = 0; i < lists.size; i++)
        lists[i].clear();
    currentSize = 0;
}

template <typename T>
void HashTable<T>::rehash()
{
    vector<list<T>> oldlist = lists;
    lists.resize(nextPrime(2 * lists.size()));
    size_t i;
    for (i = 0; i < lists.size(); i++)
        lists[i].clear();

    typename list<T>::iterator iter = oldlist[0].begin();
    for (i = 0; i < lists.size(); i++)
    {
        iter = oldlist[i].begin();
        while (iter != oldlist[i].end())
            insert(*(iter++));
    }
}

template <typename T>
void HashTable<T>::display() const
{
    size_t i;
    for (i = 0; i < lists.size(); i++)
    {
        cout << i << " : ";
        typename std::list<T>::const_iterator iter = lists[i].begin();
        while (iter != lists[i].end())
            cout << *(iter++) << "  ";
        cout << endl;
    }
}
int nextPrime(const int n)
{
    int ret, i;
    ret = n;
    while (1)
    {
        int flag = 1;
        for (i = 2; i < sqrt(ret); i++)
        {
            if (ret % i == 0)
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
            break;
        else
        {
            ret++;
            continue;
        }
    }
    return ret;
}

class empolyee
{
public:
    empolyee() {}
    empolyee(const string n, int s = 0) : name(n), salary(s) {}
    const string &getName() const { return name; }
    bool operator==(const empolyee &rhs) const
    {
        return getName() == rhs.getName();
    }
    bool operator!=(const empolyee &rhs) const
    {
        return !(*this == rhs);
    }
    friend ostream &operator<<(ostream &os, const empolyee &e)
    {
        os << "(" << e.name << "," << e.salary << ")";
        return os;
    }

private:
    string name;
    int salary;
};
int main()
{
    SetConsoleOutputCP(65001);
    empolyee e1("Tom", 6000);
    empolyee e2("Alan", 7000);
    empolyee e3("Misaki", 6500);
    empolyee e4("Lucy", 9000);
    HashTable<empolyee> emp_table(13); // tablesize must be Prime number
    emp_table.insert(e1);
    emp_table.insert(e2);
    emp_table.insert(e3);
    emp_table.insert(e4);

    cout << "Hash table is :" << endl;
    emp_table.display();

    if (emp_table.contains(e4) == 1)
        cout << "Tom is exist in hash table" << endl;
    if (emp_table.remove(e1) == 1)
        cout << "Removing Tom form the hash table successfully" << endl;
    if (emp_table.contains(e1) == 1)
        cout << "Tom is exist in hash table" << endl;
    else
        cout << "Tome is not exist in hash table" << endl;
    cout << "display agaion\n";
    emp_table.display();
    system("pause");
    return 0;
}

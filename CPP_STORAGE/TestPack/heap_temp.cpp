#include <iostream>
#include <windows.h>
#include <memory>
#include <vector>
using namespace std;

constexpr size_t MAX_SIZE = 101;
template <typename T>
class Heap
{

public:
    Heap() : size(0)
    {
        val.reserve(MAX_SIZE);
    }

    ~Heap()
    {
        val.clear();
    }

    explicit Heap(const vector<T> &v, size_t sz) : val(v), size(sz)
    {
        val.reserve(MAX_SIZE);
        if (sz > MAX_SIZE)
            throw out_of_range("out of range!");
        else if (sz < 0)
            throw invalid_argument("invalid argument");
    }

    explicit Heap(const vector<T> &v) : val(v), size(v.size())
    {
        val.reserve(MAX_SIZE);
        if (v.size() > MAX_SIZE)
            throw out_of_range("out of range!");
        else if (v.size() < 0)
            throw invalid_argument("invalid argument");
    }
    void swap(int index1, int index2)
    {
        using std::swap;
        swap(val[index1], val[index2]);
    }

    void insert(const T &v)
    {
        ++size;
        val[size - 1] = v;
        shiftUp(size - 1);
    }
    void heapInit(const vector<T> &v)
    {
        for (int i = 0; i < v.size(); ++i)
            insert(v[i]);
    }
    void replace(const T &v)
    {
        val[0] = v;
        shiftDown(0);
    }

    void sort()
    {
        heapify();
        size_t sz = size - 1;
        for (; sz > 0; sz--)
        {
            swap(0, sz);
            adjust(0, sz);
        }
    }

    void print()
    {
        for (size_t i = 0; i < size; ++i)
            cout << val[i] << ends;
    }

private:
    vector<T> val;
    size_t size;

    void heapify()
    {
        for (size_t i = parent(size - 1); i > 0; i--)
            shiftDown(i);
    }

    void shiftUp(size_t index)
    {
        while (index > 0 && val[index] > val[parent(index)])
        {
            swap(index, parent(index));
            index = parent(index);
        }
    }

    void shiftDown(size_t index)
    {
        size_t temp;
        while (left(index) < size)
        {
            temp = left(index);
            if (right(index) < size && val[temp] < val[right(index)])
                ++temp;
            if (val[index] >= val[temp])
                break;
            swap(index, temp);
            index = temp;
        }
    }

    int parent(size_t index) const
    {
        if (index == 0)
            throw out_of_range("error: it's root\n");
        return (index - 1) / 2;
    }

    int left(size_t index) const { return 2 * index + 1; }
    int right(size_t index) const { return 2 * index + 2; }

    void adjust(size_t index, size_t currSize)
    {
        size_t temp;
        while (left(index) < currSize)
        {
            temp = left(index);
            if (right(index) < currSize && val[temp] < val[right(index)])
                ++temp;
            if (val[index] >= val[temp])
                break;
            swap(temp, index);
            index = temp;
        }
    }
};
template <>
Heap<string>::Heap() : size(0) { val.resize(MAX_SIZE); }

int main()
{
    SetConsoleOutputCP(65001);
    vector<int> val{-20, 0, 99, 213, 3234, 242, 1, 213, 32, 121, 3243, 21, 414, 143, 4, 5345, 532, 2432, 213, 123, 43, 999, -99, 12317641};
    Heap<int> hp;
    Heap<string> hp_s;
    vector<string> vals{"acd", "a", "v", "ae", "eua", "akemi", "homura", "Nagisa", "Koito", "YUU", "NAnaMi"};
    hp_s.heapInit(vals);
    hp_s.print();
    cout << endl
         << " After Sorted\n";
    hp_s.sort();
    hp_s.print();
    cout << endl;
    hp.heapInit(val);
    hp.print();
    cout << endl
         << "After Sorted\n";
    hp.sort();
    hp.print();
    system("pause");
    return 0;
}

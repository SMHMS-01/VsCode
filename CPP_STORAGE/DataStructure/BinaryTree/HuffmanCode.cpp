#include <iostream>
#include <windows.h>
#include <string>
#include <cstring>
using namespace std;

typedef struct HuffmanNode
{
    int weight;
    char ch;
    string code;
    int lchild, rchild, parent;
} HuffmanNode, *HuffmanTree;
typedef struct
{
    int min;
    int secMin;
} Min;
class HuffmanCode
{
public:
    HuffmanCode(const string &str);
    ~HuffmanCode();
    Min MIN(int &min, int &secmin, int parent);
    void Merge(int min, int secmin, int parent);
    void EnCoding();
    void Decoding(const string &str);

private:
    HuffmanTree huffmanTree;
    int sizeLeaves;
};

HuffmanCode::HuffmanCode(const string &str)
{
    int len = (int)str.size(); //the size of string (at the same time len is number of leaf node)
    int arr[256], i;           //store number of appearance of every characters in string
    huffmanTree = new HuffmanNode[256];

    //1.initialize huffmanTree array
    int numNodes = 2 * len - 1; //the maxium of nodes
    for (i = 0; i < numNodes; i++)
    {
        huffmanTree[i].lchild = huffmanTree[i].rchild = huffmanTree[i].parent = -1;
        huffmanTree[i].code = ""; //set empty
    }

    //2.record number of occurences of every char that inputed string
    memset(arr, 0, sizeof(arr)); //clear

    for (i = 0; i < len; i++) //statistics frequency
    {
        arr[i] = (int)str[i]; //str[i]-> convert to corresponding ASCII code, like '0' -> 48
    }
    sizeLeaves = 0; //the number of occuences of difference
    for (i = 0; i < 256; i++)
    {
        if (arr[i] != 0) //there is occured to char
        {
            cout << "char: " << (char)arr[i] << " ASCII number(is also weight) of occurences is : " << arr[i] << endl;
            huffmanTree[sizeLeaves].ch = (char)arr[i]; //make number convert to corresponding char
            huffmanTree[sizeLeaves].weight = arr[i];   //weight
            sizeLeaves++;
        }
    }

    //3.select two relative lower number to merge
    Min getMin;
    for (i = sizeLeaves; i < 2 * sizeLeaves - 1; i++)
    {
        MIN(getMin.min, getMin.secMin, i);
        Merge(getMin.min, getMin.secMin, i);
    }
}

HuffmanCode::~HuffmanCode()
{
    delete[] huffmanTree;
    huffmanTree = nullptr;
}

Min HuffmanCode::MIN(int &min, int &secmin, int parent)
{
    double weight = 0;
    int i;
    Min _min;
    //search mininum of weight
    for (i = 0; i < parent; i++)
    {
        if (huffmanTree[i].parent == -1)
            if (weight == 0)
            {
                weight = huffmanTree[i].weight;
                min = i;
            }
            else if (huffmanTree[i].weight < weight)
            {
                weight = huffmanTree[i].weight;
                min = i;
            }
    }
    weight = 0;
    for (i = 0; i < parent; i++)
    {
        if (huffmanTree[i].parent == -1 && i != min)
            if (weight == 0)
            {
                weight = huffmanTree[i].weight;
                secmin = i;
            }
            else if (huffmanTree[i].weight < weight)
            {
                weight = huffmanTree[i].weight;
                secmin = i;
            }
    }
    _min.min = min;
    _min.secMin = secmin;
    return _min;
}

void HuffmanCode::Merge(int min, int secmin, int parent)
{
    huffmanTree[min].parent = huffmanTree[secmin].parent = parent;
    huffmanTree[parent].lchild = min;
    huffmanTree[parent].rchild = secmin;
    huffmanTree[parent].weight = huffmanTree[min].weight + huffmanTree[secmin].weight;
}

void HuffmanCode::EnCoding()
{
    string code; //used to store undefine binary code of char
    int i, j, k, parent;

    for (i = 0; i < sizeLeaves; i++) //start from leaf nodes
    {
        j = i;
        code = "";
        while (huffmanTree[j].parent != -1) //research root upward
        {
            parent = huffmanTree[j].parent;      //parent nodes
            if (j == huffmanTree[parent].lchild) //if leftchild, 0
                code += "0";
            if (j == huffmanTree[parent].rchild)
                code += "1";
            j = parent; //move upward to parent node
        }

        //need reverse, because research leaves to root if you want to encode
        for (k = (int)code.size() - 1; k >= 0; k--)
            huffmanTree[i].code += code[k]; //store code
        cout << "char: " << huffmanTree[i].ch << "'s code is: " << huffmanTree[i].code << '\n';
    }
}
void HuffmanCode::Decoding(const string &str)
{
    string decode, temp; //decode used to store total decoding, temp used to store single decoding
    int len = (int)str.size();
    int i, j;

    decode = temp = ""; //initialization
    for (i = 0; i < len; i++)
    {
        temp += str[i]; //add code
        for (j = 0; j < sizeLeaves; j++)
        {
            if (huffmanTree[j].code == temp) //research corresponding code frome leaf nodes
            {
                decode += huffmanTree[j].ch; //covert to corresponding char
                temp = "";
                break;
            }
        }
        if (i == len - 1 && j == sizeLeaves) //if not searched corresponding code
        {
            cout << "Decoding error!\n";
            return;
        }
    }
    cout << decode << endl;
}
int main()
{
    SetConsoleOutputCP(65001);
    string str;
    cout << "please input string to code:\n";
    cin >> str;
    HuffmanCode st(str);

    cout << "Coding the string is:\n";
    st.EnCoding();
    cout << endl
         << "please input binary-coding you want to decode:\n";
    cin >> str;
    cout << "Decoding the string is:\n";
    st.Decoding(str);
    system("pause");
    return 0;
}

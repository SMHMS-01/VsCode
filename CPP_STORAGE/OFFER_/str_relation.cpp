#include <iostream>
#include <windows.h>

using namespace std;

//一眼哈希，鉴定为Time complexity is O(n) but O(1) space complexity is.
char FirstNotRepeatingChar(char const *pString)
{
    if (!pString)
        return '\0';
    constexpr unsigned int maxTableSize = 256;
    unsigned int hashTable[maxTableSize];
    memset(hashTable, 0, maxTableSize);

    char const *pHashKey = pString;
    while (*pHashKey != '\0')
        hashTable[*(pHashKey++)]++;
    pHashKey = pString;
    while (*pHashKey != '\0')
    {
        if (hashTable[*pHashKey] == 1)
            return *pHashKey;
        pHashKey++;
    }
    return '\0';
}

class CharStatistics
{
public:
    explicit CharStatistics() : index(0)
    {
        for (int i = 0; i < 256; ++i)
            occurence[i] = -1;
    }
    void Insert(char ch)
    {
        if (occurence[ch] == -1)
            occurence[ch] = index;
        else if (occurence[ch] >= 0)
            occurence[ch] = -2;
        index++;
    }

    char FirstAppearingOnce()
    {
        char ch = '\0';
        int minIndex = numeric_limits<int>::max();
        for (int i = 0; i < 256; ++i)
        {
            if (occurence[i] >= 0 && occurence[i] < minIndex)
            {
                ch = (char)i;
                minIndex = occurence[i];
            }
        }
        return ch;
    }

private:
    int occurence[256];
    int index;
};
int main()
{
    SetConsoleOutputCP(65001);
    cout << FirstNotRepeatingChar("abcdefg") << endl;
    system("pause");
    return 0;
}

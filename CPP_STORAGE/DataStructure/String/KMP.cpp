#include <iostream>
#include <windows.h>
using namespace std;
//PAY ATTATION TO THAT THE RETURN VALUE OF FUNCTION——STRING.LENGTH() IS UNSIGNED INT, WE MUST CONVERT, OR RECEIPT FAILED!!!
int violence_index(string s, string t, int pos)
{
    int i = 0;                                           //i used for sub of current position of primary string     if pos!=1, match from pos position
    int j = 1;                                           //j used for sub of current position of secondary string
    while (i <= (int)s.length() && j <= (int)t.length()) //Cycle only when length of i is less than length of s and length of j is less than length of t
    {
        if (s[i] == t[j]) //if match, continue
        {
            ++i;
            ++j;
        }
        else //pointer move back and restar match
        {
            i = i - j + 2; //i move back to the next one after the first match last time. Don't ask, is just about matchematics, just think about it
            j = 1;         //j move back to original position
        }
    }
    if (j > (int)t.length())        //j is more than length of t means match is finished
        return i - (int)t.length(); //i mins length of t is the all-match position
    else
        return -1;
}
void makeNextVal(string str, int next[])
{
    int j, k;
    j = 0;
    k = -1;
    next[0] = -1;
    while (j < (int)str.length())
    {
        if (k == -1 || str[j] == str[k]) //k move back to next[0] or they are the same
        {
            ++j;
            ++k;
            if (str[j] == str[k])  //advance, for a instance "aaaab"
                next[j] = next[k]; //if the same, omit suffix
            else
                next[j] = k; //save the most size of public suffix and prefix
        }
        else
            k = next[k]; //backtracking
    }
}
int KMP(string S, string T, int pos)
{
    int j = 0;
    int k = 0;
    int next[(int)S.length()]; //initlizae next[];
    makeNextVal(T, next);
    while (j < (int)S.length() && k < (int)T.length()) //judging length of j&k
    {
        if (k == -1 || S[j] == T[k])
        {
            ++j;
            ++k;
        }
        else
            k = next[k]; //backtracking
    }
    if (k == (int)T.length()) //if all-match
        return j - k;
    else
        return -1;
}
int main()
{
    SetConsoleOutputCP(65001);
    string index = "*)";
    string Str_2 = "ababababbadaihfaufksloliololiakdgafyg*#$%^&*)&^^$$";
    int len_2 = (int)Str_2.length();
    int next[len_2];
    makeNextVal(Str_2, next); //output the most size of public suffix and prefix
    for (int i = 0; i < (int)index.length(); i++)
    {
        cout << next[i] << ' ';
    }
    cout << endl
         << "length= " << len_2 << " and " << (int)index.length() << endl
         << KMP(Str_2, index, 0) << endl;
    system("pause");
    return 0;
}

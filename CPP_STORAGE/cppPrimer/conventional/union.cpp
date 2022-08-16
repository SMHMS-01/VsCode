#include <iostream>
#include <windows.h>

using namespace std;

union token
{
    //默认情况下为公有
    char cval;
    int ival;
    double dval;
};
//匿名union
//匿名union不可包含受保护的、私有的成员，也不可定义成员函数
static union
{
    char cval1;
    int ival1;
    double dval1;
};
void test()
{
    token a{'a'};
    cval1 = '&';
}

//使用类管理union成员
class Token
{
public:
    Token() : tok(INT), ival(0) {} //只能在此初始化一个union函数
    Token(const Token &t) : tok(t.tok) { copyUnion(t); }
    Token &operator=(const Token &t);
    ~Token()
    {
        if (tok == STR)
            sval.~string();
    }
    Token &operator=(const string &);
    Token &operator=(int);
    Token &operator=(char);
    Token &operator=(double);

private:
    enum
    {
        INT,
        CHAR,
        DBL,
        STR
    } tok;
    union
    {
        char cval;
        int ival;
        double dval;
        string sval;
    };
    void copyUnion(const Token &);
};
Token &Token::operator=(const Token &t)
{
    if (tok == STR && t.tok != STR)
        sval.~basic_string();
    if (tok == STR && t.tok == STR)
        sval = t.sval;
    else
        copyUnion(t);
    tok = t.tok;
    return *this;
}
Token &Token::operator=(int i)
{
    if (tok == STR)
        sval.~basic_string();
    ival = i;
    tok = INT;
    return *this;
}
Token &Token::operator=(char c)
{
    if (tok == STR)
        sval.~basic_string();
    cval = c;
    tok = CHAR;
    return *this;
}
Token &Token::operator=(double d)
{
    if (tok == STR)
        sval.~basic_string();
    dval = d;
    tok = DBL;
    return *this;
}
Token &Token::operator=(const string &str)
{
    if (tok != STR)
        new (&sval) string(str);
    else
        sval = str;
    tok = STR;
    return *this;
}

void Token::copyUnion(const Token &t)
{
    switch (t.tok)
    {
    case Token::INT:
        ival = t.ival;
        break;
    case Token::CHAR:
        cval = t.cval;
        break;
    case Token::DBL:
        dval = t.dval;
        break;
    case Token::STR:
        new (&sval) string(t.sval);
        break;
    default:
        break;
    }
}
int main()
{
    SetConsoleOutputCP(65001);
    test();
    Token t1;
    t1 = "abcde";
    system("pause");
    return 0;
}

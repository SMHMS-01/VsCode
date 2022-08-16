#include <iostream>
#include <windows.h>
#include <memory>
using namespace std;

//条款44:将与参数无关的代码抽离templates
//Template生成多个classes和 多个函数,所以任何template代码都不该与某个造成膨胀的template参数产生相依关系
//因非类型模板参数(non-type template parames)而造成的代码膨胀,往往可以消除,做法是以函数参数或class成员变量替代template参数
//因类型参数而造成的代码膨胀,往往可降低,做法是让带有完全相同二进制表述(int/long在某些平台上一致)的具现类型共享实现码.
template <typename T, size_t n>
class SquareMatrix
{
public:
    void invert();
};
void test()
{
    //两个函数的其他部分完全相同,造成了代码膨胀
    SquareMatrix<double, 5> sm1;
    SquareMatrix<double, 10> sm2;
}

//第一次修订:
template <typename T>
class squareMatrixBase
{
protected:
    void invert(size_t matrixSize);
};

template <typename T, size_t n>
class Squarematrix : private squareMatrixBase<T>
{
private:
    using squareMatrixBase<T>::invert;

public:
    void invert() { this->invert(n); } //问题来了,我们怎么知道哪个特定矩阵的数据在哪?
};

//第二次修订
template <typename T>
class SQUAREMATRIX_BASE
{
protected:
    SQUAREMATRIX_BASE(size_t n, T *pMem) : size(n), pData(pMem) {}
    void setDataPtr(T *ptr) { pData = ptr; }

private:
    size_t size;
    shared_ptr<T> pData;
};
template <typename T, size_t n>
class SQUAREMATRIX : private SQUAREMATRIX_BASE<T>
{
public:
    SQUAREMATRIX() : SQUAREMATRIX_BASE<T>(n, 0), pData(new T[n * n])
    {
        this->setDataPtr(pData.get());
    }

private:
    shared_ptr<T> pData;
};
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}

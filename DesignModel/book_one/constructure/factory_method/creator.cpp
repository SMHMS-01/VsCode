#include "product.h"

class Creator
{
public:
    virtual Product *Creat(ProductId);
};

Product *Creator::Creat(ProductId id)
{
    if (id == MINE)
        return new MyProduct;
    if (id == YOURS)
        return new YourProduct;

    return 0;
}

class MyCreator : public Creator
{
public:
    Product *Creat(ProductId);
};

Product *MyCreator::Creat(ProductId id)
{
    if (id == MINE)
        return new MyProduct;
    if (id == YOURS)
        return new YourProduct;
    if (id == THEIRS)
        return new TheirProduct;

    return Creator::Creat(id);
}
enum ProductId
{
    MINE,
    YOURS,
    THEIRS
};

class Product
{

public:
    Product();
};

class MyProduct : public Product
{
public:
    MyProduct();
};

class YourProduct : public Product
{
public:
    YourProduct();
};

class TheirProduct : public Product
{
public:
    TheirProduct();
};
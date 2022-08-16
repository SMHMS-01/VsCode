#include <iostream>
#include <windows.h>

using namespace std;
class car
{
public:
    car() : color("black"), usedTime(0) {}
    explicit car(const string &e, const string &color, int usedTime)
    {
        enginerNumb = e;
        this->color = color;
        this->usedTime = usedTime;
    }

    explicit car(const car &carr) = default;
    car(car &&carr) noexcept = default;

    car &operator=(const car &carr)
    {
        enginerNumb = carr.color;
        color = carr.color;
        usedTime = carr.usedTime;
        return *this;
    }

    inline virtual int usedTimeGet() const
    {
        return usedTime;
    }

    virtual ~car() = default;

protected:
    inline virtual string &customColor(const string &str)
    {
        color = str;
        return color;
    }

private:
    string enginerNumb;
    string color;
    int usedTime;
};

class vechile : private car
{
public:
    using car::usedTimeGet;
    vechile(const string &color, int usedTime) : car() {}

protected:
    using car::customColor;

private:
    unsigned weight;
};

int main()
{
    SetConsoleOutputCP(65001);

    system("pause");
    return 0;
}

#include <iostream>
#include <windows.h>
#include <string>
#include <vector>

class Product1
{
public:
    std::vector<std::string> parts_;
    void ListParts() const
    {
        std::cout << "Product parts: ";
        for (size_t i = 0; i < parts_.size(); i++)
        {
            if (parts_[i] == parts_.back())
            {
                std::cout << parts_[i];
            }
            else
            {
                std::cout << parts_[i] << ", ";
            }
        }
        std::cout << "\n\n";
    }
};

class HouseBulider
{
public:
    virtual void reset() = 0;
    virtual void bulidWalls() const = 0;
    virtual void bulidDoors() const = 0;
    virtual void bulidWindows() const = 0;
    virtual void bulidRoof() const = 0;
    virtual void bulidGarage() const = 0;
};

class HouseWithGardenBulider : public HouseBulider
{
public:
    void reset()
    {
        this->product = new Product1();
    }
    void bulidWalls() const override
    {
        this->product->parts_.push_back("Walls");
    }
    void bulidDoors() const override
    {
        this->product->parts_.push_back("Doors");
    }
    void bulidWindows() const override
    {
        this->product->parts_.push_back("Windows");
    }
    void bulidRoof() const override
    {
        this->product->parts_.push_back("Roof");
    }

    void bulidGarage() const override
    {
        this->product->parts_.push_back("Garage");
    }

    virtual void bulidGarden() const
    {
        this->product->parts_.push_back("Garden");
    }

    Product1 *getResult()
    {
        return this->product;
    }

private:
    Product1 *product;
};

class HouseWithPoorBulider : public HouseBulider
{
public:
    void reset()
    {
        this->product = new Product1();
    }
    void bulidWalls() const override
    {
        this->product->parts_.push_back("Walls with subWindows");
    }
    void bulidDoors() const override
    {
        this->product->parts_.push_back("Doors");
    }
    void bulidWindows() const override
    {
        this->product->parts_.push_back("Superme  Windows");
    }
    void bulidRoof() const override
    {
        this->product->parts_.push_back("Roof");
    }

    void bulidGarage() const override
    {
        this->product->parts_.push_back("Garage");
    }

    virtual void bulidPoor() const
    {
        this->product->parts_.push_back("Poor");
    }

    Product1 *getResult()
    {
        return this->product;
    }

private:
    Product1 *product;
};
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}

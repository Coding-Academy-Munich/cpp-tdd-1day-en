#ifndef UNIT_TESTING_03_ITEM_H_
#define UNIT_TESTING_03_ITEM_H_

#include <iostream>
#include <string>

class Item
{
private:
    std::string name;
    double price;

public:
    Item(std::string name, double price) : name(name), price(price) {}

    std::string getName() const { return name; }
    double getPrice() const { return price; }

    void setPrice(double value);
};

inline void Item::setPrice(double value)
{
    if (value < 0)
    {
        value = -value;
    }
    price = value;
}

inline bool operator==(const Item& a, const Item& b)
{
    return a.getName() == b.getName() && a.getPrice() == b.getPrice();
}

inline std::ostream& operator<<(std::ostream& os, const Item& item)
{
    os << "Item(" << item.getName() << ", " << item.getPrice() << ")";
    return os;
}

#endif // UNIT_TESTING_03_ITEM_H_

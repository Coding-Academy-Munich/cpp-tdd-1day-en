#ifndef UNIT_TESTING_03_ORDER_H_
#define UNIT_TESTING_03_ORDER_H_

#include <initializer_list>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

#include "item.h"

class Order
{
private:
    std::vector<Item> items;

public:
    Order(std::initializer_list<Item> itemList) : items(itemList) {}

    std::vector<std::pair<std::string, double>> getItems() const;
    double getTotal() const;
};

inline std::vector<std::pair<std::string, double>> Order::getItems() const
{
    std::vector<std::pair<std::string, double>> itemList;
    for (auto& item : items)
    {
        itemList.push_back(make_pair(item.getName(), item.getPrice()));
    }
    return itemList;
}

inline double Order::getTotal() const
{
    return std::accumulate(
        items.begin(), items.end(), 0.0,
        [](double sum, const Item& item) { return sum + item.getPrice(); }
    );
}

inline std::ostream& operator<<(std::ostream& os, const Order& order)
{
    os << "Order(";
    for (const auto& item : order.getItems())
    {
        os << "(" << item.first << ", " << item.second << ")";
    }
    os << ")";
    return os;
}

#endif // UNIT_TESTING_03_ORDER_H_
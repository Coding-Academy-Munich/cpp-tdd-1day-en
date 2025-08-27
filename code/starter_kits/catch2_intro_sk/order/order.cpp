// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "order.h"

double Order::total_price() const
{
    return std::accumulate(
        items_.begin(), items_.end(), 0.0,
        [](double sum, const Item& item) { return sum + item.get_price(); }
    );
}

Order& Order::add_item(const std::string& name, double price)
{
    add_item(Item{name, price});
    return *this;
}

Order& Order::add_item(const Item& item)
{
    items_.push_back(item);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Order& order)
{
    os << "Order: ";
    std::string separator;
    for (const auto& item : order.items())
    {
        os << separator << item;
        separator = "; ";
    }
    return os;
}

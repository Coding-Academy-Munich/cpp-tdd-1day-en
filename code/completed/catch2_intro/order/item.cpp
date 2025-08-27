// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "item.h"

void Item::set_price(double value)
{
    if (value < 0)
    {
        value = -value;
    }
    price = value;
}

bool operator==(const Item& a, const Item& b)
{
    return a.get_name() == b.get_name() && a.get_price() == b.get_price();
}

bool operator!=(const Item& a, const Item& b) { return !(a == b); }

std::ostream& operator<<(std::ostream& os, const Item& item)
{
    os << item.get_name() << ", " << item.get_price();
    return os;
}

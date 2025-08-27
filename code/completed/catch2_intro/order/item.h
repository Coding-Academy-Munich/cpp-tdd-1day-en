// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_CATCH2_INTRO_ITEM_H
#define COMPLETED_CATCH2_INTRO_ITEM_H

#include <iostream>
#include <string>
#include <utility>

class Item
{
private:
    std::string name;
    double price;

public:
    Item(std::string name, double price) : name(std::move(name)) { set_price(price); }

    [[nodiscard]] std::string get_name() const { return name; }
    [[nodiscard]] double get_price() const { return price; }

    void set_price(double value);
};

bool operator==(const Item& a, const Item& b);
bool operator!=(const Item& a, const Item& b);

std::ostream& operator<<(std::ostream& os, const Item& item);

#endif // COMPLETED_CATCH2_INTRO_ITEM_H

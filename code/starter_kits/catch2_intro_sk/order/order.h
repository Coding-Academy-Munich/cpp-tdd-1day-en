// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_CATCH2_INTRO_ORDER_ORDER_H
#define COMPLETED_CATCH2_INTRO_ORDER_ORDER_H

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
    std::vector<Item> items_;

public:
    Order() = default;
    Order(std::initializer_list<Item> itemList) : items_(itemList) {}

    [[nodiscard]] std::vector<Item> items() const { return items_; }

    Order& add_item(const std::string& name, double price);
    Order& add_item(const Item& item);

    [[nodiscard]] double total_price() const;
};

std::ostream& operator<<(std::ostream& os, const Order& order);

#endif // COMPLETED_CATCH2_INTRO_ORDER_ORDER_H
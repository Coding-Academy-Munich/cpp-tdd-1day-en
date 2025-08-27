// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef LIB_CHICAGO_ITEM_H
#define LIB_CHICAGO_ITEM_H

#include <string>

namespace chicago_vending
{

    struct Item
    {
        std::string name;
        int current_stock;
        int capacity;
    };

} // namespace chicago_vending

#endif // LIB_CHICAGO_ITEM_H

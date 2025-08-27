// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "invoice_data.h"

namespace invoice::data {

ProductMap products {
    {"Lettuce", {1.00, "Produce"}},   {"Onions", {1.10, "Produce"}},
    {"Tomatoes", {1.00, "Produce"}},  {"Milk", {2.50, "Dairy"}},
    {"Cheese", {3.00, "Dairy"}},      {"Ice Cream", {3.50, "Dairy"}},
    {"Bread", {1.00, "Bakery"}},      {"Cake", {10.00, "Bakery"}},
    {"Hammer", {10.00, "Hardware"}},  {"Nails", {0.10, "Hardware"}},
    {"Ladder", {100.00, "Hardware"}}, {"Drill", {5.00, "Hardware"}},
};

OrderList orders {
    {"John", {{"Lettuce", 2}}},
    {"Mary", {{"Lettuce", 5}}},
    {"Jill", {{"Lettuce", 10}}},
    {"James", {{"Lettuce", 4}, {"Onions", 3}, {"Tomatoes", 2}}},
    {"Bob", {{"Milk", 2}, {"Cheese", 1}}},
    {"Alice", {{"Ice Cream", 5}, {"Cheese", 1}}},
    {"Sam", {{"Milk", 4}, {"Ice Cream", 4}, {"Cheese", 2}}},
    {"Jane's Milky Way", {{"Cheese", 8}, {"Ice Cream", 8}, {"Milk", 2}}},
};

} // namespace invoice::data

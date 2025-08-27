// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "order.h"
#include <catch2/catch_test_macros.hpp>
#include <sstream>

TEST_CASE ("Empty order")
{
    Order order{};
    CHECK(order.total_price() == 0.0);
    CHECK(order.items().empty());
}

TEST_CASE ("Order with items")
{
    Order order{{"Item 1", 1.0}, {"Item 2", -2.0}};
    CHECK(order.total_price() == 3.0);
    CHECK(order.items().size() == 2);
}

TEST_CASE ("Adding items to an order")
{
    Order order{};
    SECTION ("Adding one items")
    {
        order.add_item("Item 1", 1.0);
        CHECK(order.items().size() == 1);
        CHECK(order.total_price() == 1.0);
    }
    SECTION ("Adding two items")
    {
        order.add_item("Item 1", 1.0);
        order.add_item("Item 2", 2.0);
        CHECK(order.items().size() == 2);
        CHECK(order.total_price() == 3.0);
    }
}

TEST_CASE ("Changing the price of an item in an order")
{
    Order order{{"Item 1", 1.0}, {"Item 2", -2.0}};
    order.items()[0].set_price(3.0);
    CHECK(order.total_price() == 3.0);
}

TEST_CASE ("Order output format")
{
    Order order{{"Item 1", 1.0}, {"Item 2", -2.0}};
    std::ostringstream os;
    os << order;
    CHECK(os.str() == "Order: Item 1, 1; Item 2, 2");
}

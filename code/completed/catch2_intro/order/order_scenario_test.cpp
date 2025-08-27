// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "order.h"
#include <catch2/catch_test_macros.hpp>
#include <sstream>

SCENARIO ("Creating an empty order")
{
    GIVEN ("An empty order")
    {
        Order order{};
        THEN ("It has a total price of 0")
        {
            REQUIRE(order.total_price() == 0.0);
        }
        THEN ("It has an empty list of items")
        {
            REQUIRE(order.items().empty());
        }
    }
}

SCENARIO ("Creating an order with items")
{
    GIVEN ("An order with two items")
    {
        Order order{{"Item 1", 1.0}, {"Item 2", -2.0}};
        THEN ("It has the correct total price")
        {
            REQUIRE(order.total_price() == 3.0);
        }
        THEN ("It has two items")
        {
            REQUIRE(order.items().size() == 2);
        }
    }
}

SCENARIO ("Adding items to an order")
{
    GIVEN ("An empty order")
    {
        Order order{};
        WHEN ("An item is added")
        {
            order.add_item("Item 1", 1.0);
            THEN ("The order has one item")
            {
                REQUIRE(order.items().size() == 1);
            }
            THEN ("The order has the correct total price")
            {
                REQUIRE(order.total_price() == 1.0);
            }
        }
        WHEN ("Two items are added")
        {
            order.add_item("Item 1", 1.0).add_item("Item 2", 2.0);
            THEN ("The order has two items")
            {
                REQUIRE(order.items().size() == 2);
            }
            THEN ("The order has the correct total price")
            {
                REQUIRE(order.total_price() == 3.0);
            }
        }
    }
}

SCENARIO ("Changing the price of an item in an order")
{
    GIVEN ("An order with two items")
    {
        Order order{{"Item 1", 1.0}, {"Item 2", -2.0}};
        WHEN ("Modifying the returned items")
        {
            order.items()[0].set_price(3.0);
            THEN ("The total price is unchanged")
            {
                REQUIRE(order.total_price() == 3.0);
            }
        }
    }
}

SCENARIO ("Output format of an order")
{
    GIVEN ("An order with two items")
    {
        Order order{{"Item 1", 1.0}, {"Item 2", -2.0}};
        WHEN ("Writing the order to a stream")
        {
            std::stringstream stream;
            stream << order;
            THEN ("The output format is correct")
            {
                REQUIRE(stream.str() == "Order: Item 1, 1; Item 2, 2");
            }
        }
    }
}
// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "item.h"
#include <catch2/catch_test_macros.hpp>

SCENARIO ("Creating an item")
{
    GIVEN ("An item with a positive price")
    {
        Item item{"Item 1", 1.0};
        THEN ("The item has the correct name")
        {
            REQUIRE(item.get_name() == "Item 1");
        }
        THEN ("The item has the correct price")
        {
            REQUIRE(item.get_price() == 1.0);
        }
    }
    GIVEN ("An item with a negative price")
    {
        Item item{"Item 2", -2.0};
        THEN ("The item has the correct name")
        {
            REQUIRE(item.get_name() == "Item 2");
        }
        THEN ("The item has the correct price")
        {
            REQUIRE(item.get_price() == 2.0);
        }
    }
}

SCENARIO ("Changing the price of an item")
{
    GIVEN ("An item with a positive price")
    {
        Item item{"Item 1", 1.0};
        WHEN ("The price is set to a positive value")
        {
            item.set_price(2.0);
            THEN ("The price is the new value")
            {
                REQUIRE(item.get_price() == 2.0);
            }
        }
        WHEN ("The price is set to a negative value")
        {
            item.set_price(-2.0);
            THEN ("The price is the absolute value of the new value")
            {
                REQUIRE(item.get_price() == 2.0);
            }
        }
    }
    GIVEN ("An item with a negative price")
    {
        Item item{"Item 2", -2.0};
        WHEN ("The price is set to a positive value")
        {
            item.set_price(1.0);
            THEN ("The price is positive")
            {
                REQUIRE(item.get_price() == 1.0);
            }
        }
        WHEN ("The price is set to a negative value")
        {
            item.set_price(-1.0);
            THEN ("The price is the absolute value of the new value")
            {
                REQUIRE(item.get_price() == 1.0);
            }
        }
    }
}

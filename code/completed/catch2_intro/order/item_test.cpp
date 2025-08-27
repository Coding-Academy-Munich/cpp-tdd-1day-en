// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "item.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE ("Creating an item")
{
    SECTION ("With a positive price")
    {
        Item unit{"Item 1", 1.0};
        CHECK(unit.get_name() == "Item 1");
        CHECK(unit.get_price() == 1.0);
    }
    SECTION ("With a negative price")
    {
        Item unit{"Item 2", -2.0};
        CHECK(unit.get_name() == "Item 2");
        CHECK(unit.get_price() == 2.0);
    }
}

TEST_CASE ("Changing the price of an item")
{
    SECTION ("An Item with a positive price")
    {
        Item unit{"Item 1", 1.0};
        SECTION ("The price is set to a positive value")
        {
            unit.set_price(2.0);
            CHECK(unit.get_price() == 2.0);
        }
        SECTION ("The price is set to a negative value")
        {
            unit.set_price(-2.0);
            CHECK(unit.get_price() == 2.0);
        }
    }
    SECTION ("An item with a negative price")
    {
        Item unit{"Item 2", -2.0};
        SECTION ("The price is set to a positive value")
        {
            unit.set_price(1.0);
            CHECK(unit.get_price() == 1.0);
        }
        SECTION ("The price is set to a negative value")
        {
            unit.set_price(-1.0);
            CHECK(unit.get_price() == 1.0);
        }
    }
}

TEST_CASE ("Comparing items")
{
    Item item1{"Item 1", 1.0};
    Item item2{"Item 1", 1.0};
    Item item3{"Item 2", 1.0};
    Item item4{"Item 1", 2.0};
    SECTION ("Comparison with ==")
    {
        CHECK(item1 == item2);
        CHECK_FALSE(item1 == item3);
        CHECK_FALSE(item1 == item4);
    }
    SECTION ("Comparison with !=")
    {
        CHECK_FALSE(item1 != item2);
        CHECK(item1 != item3);
        CHECK(item1 != item4);
    }
}

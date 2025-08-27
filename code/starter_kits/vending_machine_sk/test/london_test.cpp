// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include "london/vending_machine.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Check that London-style tests are executed")
{
    CHECK(london_vending::isolation() == "London");
}

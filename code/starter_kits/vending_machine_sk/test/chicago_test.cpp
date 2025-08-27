// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include "chicago/vending_machine.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Check that Chicago-style tests are executed")
{
    CHECK(chicago_vending::isolation() == "Chicago");
}

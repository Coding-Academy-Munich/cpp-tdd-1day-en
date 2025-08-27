// Created by Dr. Matthias Hölzl on 01/10/2023.
// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "DeleteMe.h"
#include <catch2/catch_test_macros.hpp>

using namespace library_sk;

TEST_CASE("Test DeleteMe")
{
    SECTION("Test ==")
    {
        DeleteMe deleteMe{};
        REQUIRE(deleteMe == deleteMe);
        REQUIRE(!(deleteMe == DeleteMe{}));
    }
}

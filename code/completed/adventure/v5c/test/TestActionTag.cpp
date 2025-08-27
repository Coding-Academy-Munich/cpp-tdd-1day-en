// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "ActionTag.h"
#include <catch2/catch_test_macros.hpp>

using namespace adventure::v5c;

TEST_CASE("Test ActionTag", "[actions]")
{
    SECTION("Empty TagSet contains nothing")
    {
        ActionTagSet tags;
        REQUIRE(!tags.Contains(ActionTag::Move));
    }

    SECTION("Non-empty TagSet contains its members")
    {
        ActionTagSet tags {ActionTag::Move};
        REQUIRE(tags.Contains(ActionTag::Move));
        REQUIRE(!tags.Contains(ActionTag::SkipTurn));
    }
}
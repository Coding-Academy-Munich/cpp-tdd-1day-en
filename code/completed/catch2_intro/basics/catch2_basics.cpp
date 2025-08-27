#include <catch2/catch_test_macros.hpp>

int add(int a, int b) { return a + b; }

TEST_CASE ("Add two numbers")
{
    REQUIRE(add(1, 2) == 3);
}

TEST_CASE ("Add several numbers with errors (REQUIRE)")
{
    REQUIRE(add(1, 2) == 4);
    REQUIRE(add(1, 3) == 2);
}

TEST_CASE ("Add several numbers with errors (CHECK)")
{
    CHECK(add(1, 2) == 4);
    CHECK(add(1, 3) == 2);
}

TEST_CASE ("Add numbers with error (REQUIRE and negation)")
{
    REQUIRE(!(add(1, 2) == 3));
}

TEST_CASE ("Add several numbers with errors (REQUIRE_FALSE)")
{
    REQUIRE_FALSE(add(1, 2) == 3);
    REQUIRE_FALSE(add(1, 3) == 4);
}

TEST_CASE ("Add several numbers with errors (CHECK_FALSE)")
{
    CHECK_FALSE(add(1, 2) == 3);
    CHECK_FALSE(add(1, 3) == 4);
}

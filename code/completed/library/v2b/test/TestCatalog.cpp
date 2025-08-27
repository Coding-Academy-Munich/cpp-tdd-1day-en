// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Catalog.h"
#include <catch2/catch_test_macros.hpp>

using namespace library::v2b;

TEST_CASE("Test Catalog")
{
    Catalog<std::string> catalog {};
    catalog.Add(std::make_unique<std::string>("alpha"));
    catalog.Add(std::make_unique<std::string>("beta"));
    catalog.Add(std::make_unique<std::string>("gamma"));

    SECTION("Test Add()") { REQUIRE(catalog.Size() == 3); }

    SECTION("Test Find()")
    {
        REQUIRE(catalog.Find([](const std::string& arg) { return arg == "alpha"; }));
    }

    SECTION("Test Find() with non-existing element")
    {
        REQUIRE(catalog.Find([](const std::string& arg) { return arg == "delta"; })
            == nullptr);
    }

    SECTION("Test Remove()")
    {
        catalog.Remove("beta");
        REQUIRE(catalog.Size() == 2);
        REQUIRE(catalog.Find([](const std::string& arg) { return arg == "beta"; })
            == nullptr);
    }

    SECTION("Test Remove() with non-existing element")
    {
        catalog.Remove("delta");
        REQUIRE(catalog.Size() == 3);
    }
}
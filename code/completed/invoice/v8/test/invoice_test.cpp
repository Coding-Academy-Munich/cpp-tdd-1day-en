// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "invoice.h"
#include <catch2/catch_test_macros.hpp>

using namespace invoice::v8;

ProductMap products = {
    {"Lettuce", {"Lettuce", 1.00, "Produce"}},
    {"Onions", {"Onions", 1.10, "Produce"}},
    {"Tomatoes", {"Tomatoes", 1.00, "Produce"}},
    {"Milk", {"Milk", 2.50, "Dairy"}},
    {"Cheese", {"Cheese", 3.00, "Dairy"}},
    {"Ice Cream", {"Ice Cream", 3.50, "Dairy"}}
    // ... any additional products if needed ...
};

TEST_CASE("GenerateInvoice works correctly", "[GenerateInvoice]") {

    SECTION("Test case for John with 2 Lettuces") {
        Order order {"John", {{"Lettuce", 2}}};
        std::string expected {"Order for John:\n"
                              "  - Lettuce:       2 à 1.00 = $2.00\n"
                              "Total: $2.00"};
        REQUIRE(GenerateInvoice(order, products) == expected);
    }

    SECTION("Test case for Mary with 5 Lettuces") {
        Order order {"Mary", {{"Lettuce", 5}}};
        std::string expected = "Order for Mary:\n"
                               "  - Lettuce:       5 à 1.00 = $4.50 "
                               "(discount: $0.50)\n"
                               "Total: $4.50";
        REQUIRE(GenerateInvoice(order, products) == expected);
    }

    SECTION("Test case for Jill with 10 Lettuces") {
        Order order {"Jill", {{"Lettuce", 10}}};
        std::string expected = "Order for Jill:\n"
                               "  - Lettuce:      10 à 1.00 = $9.00 "
                               "(discount: $1.00)\n"
                               "Subtotal:        $9.00\n"
                               "Volume discount: $0.45\n"
                               "Total:           $8.55";
        REQUIRE(GenerateInvoice(order, products) == expected);
    }

    SECTION("Test case for James with 4 Lettuces, 3 Onions, and 2 Tomatoes") {
        Order order {"James", {{"Lettuce", 4}, {"Onions", 3}, {"Tomatoes", 2}}};
        std::string expected = "Order for James:\n"
                               "  - Lettuce:       4 à 1.00 = $3.60 (discount: $0.40)\n"
                               "  - Onions:        3 à 1.10 = $3.30\n"
                               "  - Tomatoes:      2 à 1.00 = $2.00\n"
                               "Total: $8.90";
        REQUIRE(GenerateInvoice(order, products) == expected);
    }

    SECTION("Test case for Bob with 2 Milks and 1 Cheese") {
        Order order {"Bob", {{"Milk", 2}, {"Cheese", 1}}};
        std::string expected = "Order for Bob:\n"
                               "  - Milk:          2 à 2.50 = $5.00\n"
                               "  - Cheese:        1 à 3.00 = $3.00\n"
                               "Total: $8.00";
        REQUIRE(GenerateInvoice(order, products) == expected);
    }

    SECTION("Test case for Alice with 5 Ice Creams and 1 Cheese") {
        Order order {"Alice", {{"Ice Cream", 5}, {"Cheese", 1}}};
        std::string expected
            = "Order for Alice:\n"
              "  - Ice Cream:     5 à 3.50 = $16.62 (discount: $0.88)\n"
              "  - Cheese:        1 à 3.00 = $3.00\n"
              "Total: $19.62";
        REQUIRE(GenerateInvoice(order, products) == expected);
    }

    SECTION("Test case for Sam with 4 Milks, 4 Ice Creams, and 2 Cheeses") {
        Order order {"Sam", {{"Milk", 4}, {"Ice Cream", 4}, {"Cheese", 2}}};
        std::string expected = "Order for Sam:\n"
                               "  - Milk:          4 à 2.50 = $10.00\n"
                               "  - Ice Cream:     4 à 3.50 = $14.00\n"
                               "  - Cheese:        2 à 3.00 = $6.00\n"
                               "Subtotal:        $30.00\n"
                               "Volume discount: $3.00\n"
                               "Total:           $27.00";
        REQUIRE(GenerateInvoice(order, products) == expected);
    }

    SECTION("Test case for Jane's Milky Way with 8 Cheeses, 8 Ice Creams and 2 Milks") {
        Order order {
            "Jane's Milky Way", {{"Cheese", 8}, {"Ice Cream", 8}, {"Milk", 2}}};
        std::string expected {"Order for Jane's Milky Way:\n"
                              "  - Cheese:        8 à 3.00 = $22.80 (discount: $1.20)\n"
                              "  - Ice Cream:     8 à 3.50 = $26.60 (discount: $1.40)\n"
                              "  - Milk:          2 à 2.50 = $5.00\n"
                              "Subtotal:        $54.40\n"
                              "Volume discount: $5.44\n"
                              "Total:           $48.96"};
        REQUIRE(GenerateInvoice(order, products) == expected);
    }
}
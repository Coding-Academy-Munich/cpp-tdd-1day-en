#include "non_testable_order_processor.h"
#include "cout_redirect.h"

#include <catch2/catch_test_macros.hpp>


TEST_CASE(
    "Check that processing the orders.txt file results in the correct output")
{
    non_testable_order_processor::OrderProcessor processor;
    CoutRedirect cout;
    std::string expected_output = "Checking inventory for laptop\n"
                                  "Saving order to database\n"
                                  "Reducing stock for laptop by 2\n"
                                  "Processed order: laptop for $2160.9\n"
                                  "Checking inventory for mouse\n"
                                  "Saving order to database\n"
                                  "Reducing stock for mouse by 25\n"
                                  "Processed order: mouse for $379.762\n"
                                  "Checking inventory for keyboard\n"
                                  "Saving order to database\n"
                                  "Reducing stock for keyboard by 12\n"
                                  "Processed order: keyboard for $907.8\n"
                                  "Checking inventory for monitor\n"
                                  "Saving order to database\n"
                                  "Reducing stock for monitor by 1\n"
                                  "Processed order: monitor for $299.99\n";

    processor.process_orders_from_file("orders.txt");

    std::string output = cout.get_output();
    REQUIRE(output == expected_output);
}

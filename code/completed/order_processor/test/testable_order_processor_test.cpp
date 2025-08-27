// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include "testable_order_processor.h"
#include "cout_redirect.h"
#include "order.h"

#include <catch2/catch_test_macros.hpp>

using order_processor::Order;
using namespace testable_order_processor;

TEST_CASE(
    "Check that processing the orders.txt file results in the correct output")
{
    OrderProcessor processor;
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

struct MockInventoryService : testable_order_processor::IInventoryService
{
    bool check_inventory(const std::string& product, int quantity) override
    {
        return quantity <= 50;
    }
    void update_inventory(const std::string& product, int quantity) override
    {
    }
};

struct MockOrderRepository : testable_order_processor::IOrderRepository
{
    std::vector<order_processor::Order> saved_orders;

    void save_order_to_database(const order_processor::Order& order) override
    {
        saved_orders.push_back(order);
    }
};

TEST_CASE("OrderService.")
{
    std::unique_ptr<MockInventoryService> inventory_service =
        std::make_unique<MockInventoryService>();
    std::unique_ptr<MockOrderRepository> order_repository =
        std::make_unique<MockOrderRepository>();
    MockInventoryService* inventory_service_ptr{inventory_service.get()};
    MockOrderRepository* order_repository_ptr{order_repository.get()};
    OrderService order_service{std::move(inventory_service),
                               std::move(order_repository)};

    SECTION("process_order() saves valid order")
    {
        Order test_order{"premium", "laptop", 5, 1000.0, 0.0, false};
        order_service.process_order(test_order);

        REQUIRE(order_repository_ptr->saved_orders.size() == 1);
        Order& saved_order = order_repository_ptr->saved_orders[0];

        REQUIRE(saved_order.customer_type == "premium");
        REQUIRE(saved_order.product == "laptop");
        REQUIRE(saved_order.quantity == 5);
        REQUIRE(saved_order.unit_price == 1000.0);
        // Discount was applied
        REQUIRE(saved_order.total_price == 4500.0);
        REQUIRE(saved_order.is_valid);
    }
}

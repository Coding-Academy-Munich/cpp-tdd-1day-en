// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include <iostream>

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "testable_order_processor.h"

namespace testable_order_processor
{
using order_processor::Order;

OrderService::OrderService(std::unique_ptr<IInventoryService> inventory_service,
                           std::unique_ptr<IOrderRepository> order_service) :
    inventory_service_{std::move(inventory_service)},
    order_service_{std::move(order_service)}
{
}

void OrderService::process_order(Order& order) const
{
    // Service invocation
    if (!inventory_service_->check_inventory(order.product, order.quantity))
    {
        std::cout << "Not enough inventory for " << order.product << std::endl;
    }

    double discount = calculate_discount(order.customer_type, order.quantity);
    order.total_price = (order.unit_price * order.quantity) * (1.0 - discount);
    order.is_valid = true;

    // Database operations
    order_service_->save_order_to_database(order);

    // Service invocation
    const std::string& product = order.product;
    int quantity = order.quantity;
    inventory_service_->update_inventory(product, quantity);

    std::cout << "Processed order: " << order.product << " for $"
              << order.total_price << std::endl;
}

double OrderService::calculate_discount(const std::string& customer_type,
                                        int quantity)
{
    double discount = 0.0;
    if (customer_type == "premium")
    {
        discount += 0.1; // 10% for premium
    }
    if (quantity >= 10)
    {
        discount += 0.05; // 5% for bulk
    }
    return std::min(discount, 0.15); // Max 15% discount
}

OrderProcessor::OrderProcessor() :
    order_service_{std::make_unique<OrderService>(
        std::make_unique<DefaultInventoryService>(),
        std::make_unique<DefaultOrderRepository>())}
{
}

OrderProcessor::OrderProcessor(std::unique_ptr<OrderService> order_service) :
    order_service_{std::move(order_service)}
{
}

void OrderProcessor::process_orders_from_file(const std::string& file_path) const
{
    // File operations
    std::ifstream file(file_path);
    if (!file)
    {
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    while (std::getline(file, line))
    {
        Order order = parse_order_line(line);

        order_service_->process_order(order);
    }
}

Order OrderProcessor::parse_order_line(const std::string& line)
{
    std::stringstream ss(line);
    std::string customer_type, product, quantity_str, price_str;

    std::getline(ss, customer_type, ',');
    std::getline(ss, product, ',');
    std::getline(ss, quantity_str, ',');
    std::getline(ss, price_str, ',');

    return {customer_type,        product, std::stoi(quantity_str),
            std::stod(price_str), 0.0,     false};
}

bool DefaultInventoryService::check_inventory(const std::string& product,
                                              int quantity)
{
    std::cout << "Checking inventory for " << product << std::endl;
    return quantity <= 100; // Simulate inventory check against an external source
}

void DefaultInventoryService::update_inventory(const std::string& product,
                                               int quantity)
{
    std::cout << "Reducing stock for " << product << " by " << quantity
              << std::endl;
    // Simulate inventory update
}

void DefaultOrderRepository::save_order_to_database(
    const order_processor::Order& order)
{
    std::cout << "Saving order to database" << std::endl;
    // Simulate database save
}

} // namespace testable_order_processor

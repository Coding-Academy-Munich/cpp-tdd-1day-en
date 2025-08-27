#include <iostream>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "non_testable_order_processor.h"

namespace non_testable_order_processor
{
using order_processor::Order;

void OrderProcessor::process_orders_from_file(const std::string& file_path)
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

        // Service invocation
        if (!check_inventory(order.product, order.quantity))
        {
            std::cout << "Not enough inventory for " << order.product
                      << std::endl;
            continue;
        }

        double discount = calculate_discount(order.customer_type, order.quantity);
        order.total_price =
            (order.unit_price * order.quantity) * (1.0 - discount);
        order.is_valid = true;

        // Database operations
        save_order_to_database(order);

        // Service invocation
        update_inventory(order.product, order.quantity);

        std::cout << "Processed order: " << order.product << " for $"
                  << order.total_price << std::endl;
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

double OrderProcessor::calculate_discount(const std::string& customer_type,
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

bool OrderProcessor::check_inventory(const std::string& product, int quantity)
{
    std::cout << "Checking inventory for " << product << std::endl;
    return quantity <= 100; // Simulate inventory check against external source
}

void OrderProcessor::save_order_to_database(const Order& order)
{
    std::cout << "Saving order to database" << std::endl;
    // Simulate database save
}

void OrderProcessor::update_inventory(const std::string& product, int quantity)
{
    std::cout << "Reducing stock for " << product << " by " << quantity
              << std::endl;
    // Simulate inventory update
}

} // namespace non_testable_order_processor

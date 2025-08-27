// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include "orders.h"

#include <iostream>

using namespace simpleRefactoring;

int main()
{
    auto orderLines = MakeOrderLines();

    std::cout << "Original Receipt:\n";
    PrintReceipt(orderLines, false);

    std::cout << "Receipt with Discount:\n";
    PrintReceipt(orderLines, true);

    std::cout << "Calculation using poorly named function:\n";
    double result = CalculateTotalWithDiscountAndTax(orderLines, 0.19, true);
    std::cout << "Total with discount and tax: " << std::fixed << std::setprecision(2)
              << result << "€\n\n";

    std::cout << "Shipping costs:\n";
    std::cout << "Domestic: " << CalculateShipping(orderLines, "domestic") << "€\n";
    std::cout << "Europe: " << CalculateShipping(orderLines, "europe") << "€\n";
    std::cout << "International: " << CalculateShipping(orderLines, "international")
              << "€\n\n";

    std::cout << "Order line values:\n";
    for (const auto& line : orderLines)
    {
        std::cout << line.product << ": " << GetOrderLineValue(line) << "€\n";
    }

    Customer customer;
    customer.SetName("John Doe");
    customer.SetEmail("john@example.com");
    customer.LoyaltyPoints() = 150;
    customer.display();

    // Direct manipulation of customer data (bad practice)
    customer.LoyaltyPoints() += 10;
    std::cout << "After adding points: " << customer.LoyaltyPoints() << "\n";

    return 0;
}

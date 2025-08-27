// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include "orders.h"

#include <iostream>

using namespace simpleRefactoringSk;

int main()
{
    auto orderLines = MakeOrderLines();

    std::cout << "Original Receipt:\n";
    PrintReceipt(orderLines, false);

    std::cout << "Receipt with Discount:\n";
    PrintReceipt(orderLines, true);

    std::cout << "Calculation using poorly named function:\n";
    double result = Calc(true, orderLines, 0.19);
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
    customer.name = "John Doe";
    customer.email = "john@example.com";
    customer.loyaltyPoints = 150;
    customer.Display();

    // Direct manipulation of customer data (bad practice)
    customer.loyaltyPoints += 10;
    std::cout << "After adding points: " << customer.loyaltyPoints << "\n";

    return 0;
}

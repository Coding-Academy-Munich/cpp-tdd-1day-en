// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef SIMPLE_REFACTORING_SK_LIB_ORDERS_H
#define SIMPLE_REFACTORING_SK_LIB_ORDERS_H

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace simpleRefactoringSk
{
    // Examples of code that needs refactoring

    struct OrderLine
    {
        std::string product;
        int quantity;
        double price;
    };

    // Global variable that should be encapsulated
    extern std::string companyName;

    // Helper function to create sample data
    inline std::vector<OrderLine> MakeOrderLines()
    {
        return {{"Laptop", 2, 999.99}, {"Mouse", 5, 25.50}, {"Keyboard", 3, 75.00}};
    }

    // Example 1: Function that needs Extract Function refactoring
    inline void PrintReceipt(const std::vector<OrderLine>& orderLines, bool applyDiscount)
    {
        std::cout << "=== " << companyName << " Invoice ===\n";

        // Print header
        std::cout << std::left << std::setw(12) << "Product" << " " << std::right
                  << std::setw(8) << "Quantity" << " " << std::setw(10) << "Price" << " "
                  << std::setw(12) << "Subtotal" << "\n";
        std::cout << std::string(50, '-') << "\n";

        // Print order lines - this logic could be extracted
        for (const auto& orderLine : orderLines)
        {
            double subtotal = orderLine.quantity * orderLine.price;
            std::cout << std::left << std::setw(12) << orderLine.product << " "
                      << std::right << std::setw(8) << orderLine.quantity << " "
                      << std::fixed << std::setprecision(2) << std::setw(10)
                      << orderLine.price << "€ " << std::setw(11) << subtotal << "€\n";
        }

        std::cout << std::string(50, '-') << "\n";

        // Calculate total - this logic could be extracted
        double total = 0.0;
        for (const auto& orderLine : orderLines)
        {
            total += orderLine.quantity * orderLine.price;
        }

        // Apply discount logic - could be extracted
        if (applyDiscount)
        {
            double discountAmount = total * 0.1; // 10% discount
            total = total - discountAmount;
            std::cout << "Discount (10%): -" << std::fixed << std::setprecision(2)
                      << discountAmount << "€\n";
        }

        std::cout << "Total: " << std::fixed << std::setprecision(2) << total << "€\n";
        std::cout << "Thank you for your business!\n\n";
    }

    // Example 2: Function with poor naming and parameter order
    inline double Calc(bool d, const std::vector<OrderLine>& ol, double tax)
    {
        double t = 0.0;
        for (const auto& line : ol)
        {
            t += line.quantity * line.price;
        }
        if (d)
        {
            t *= 0.9; // 10% discount
        }
        t += t * tax; // Add tax
        return t;
    }

    // Example 3: Function that could benefit from Extract Variable
    inline double CalculateShipping(const std::vector<OrderLine>& orderLines,
                                    const std::string& destination)
    {
        double weight = 0.0;
        for (const auto& line : orderLines)
        {
            // Assume each item weighs 0.5kg
            weight += line.quantity * 0.5;
        }

        // Complex shipping calculation that could use explanatory variables
        if (destination == "domestic")
        {
            return (weight < 5.0) ? 5.99 : (weight * 1.2 + 2.5);
        }
        else if (destination == "europe")
        {
            return (weight < 2.0) ? 15.99 : (weight * 2.8 + 8.0);
        }
        else
        {
            // international
            return (weight < 1.0) ? 25.99 : (weight * 4.5 + 15.0);
        }
    }

    // Example 4: Unnecessary variable that could be inlined
    inline double GetOrderLineValue(const OrderLine& orderLine)
    {
        const double value = orderLine.quantity * orderLine.price;
        return value; // This variable doesn't add clarity
    }

    // Example 5: Class with exposed data that needs encapsulation
    class Customer
    {
    public:
        std::string name;
        std::string email;
        int loyaltyPoints;

        void Display() const
        {
            std::cout << "Customer: " << name << " (" << email << ")\n";
            std::cout << "Loyalty Points: " << loyaltyPoints << "\n";
        }
    };

    // Example 6: Function that could be inlined (too simple)
    inline double GetTaxRate()
    {
        return 0.19; // 19% VAT
    }

    inline double CalculateTotalWithTax(double subtotal)
    {
        return subtotal + (subtotal * GetTaxRate());
    }

} // namespace simpleRefactoringSk

#endif // SIMPLE_REFACTORING_SK_LIB_ORDERS_H

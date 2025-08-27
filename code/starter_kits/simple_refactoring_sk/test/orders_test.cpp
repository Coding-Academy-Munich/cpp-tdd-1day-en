// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include "orders.h"

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <sstream>
#include <streambuf>

#include "catch2/catch_approx.hpp"

using namespace simpleRefactoringSk;

// Test utility class to capture cout output
class CoutCapture
{
private:
    std::stringstream buffer;
    std::streambuf* old;

public:
    CoutCapture() : old(std::cout.rdbuf(buffer.rdbuf()))
    {
    }

    ~CoutCapture()
    {
        std::cout.rdbuf(old);
    }

    std::string GetOutput() const
    {
        return buffer.str();
    }

    void clear()
    {
        buffer.str("");
        buffer.clear();
    }
};

// test_before_refactoring.cpp
// Unit tests for the code before refactoring

TEST_CASE("MakeOrderLines creates expected test data", "[data]")
{
    auto orderLines = MakeOrderLines();

    REQUIRE(orderLines.size() == 3);

    SECTION("First order line")
    {
        REQUIRE(orderLines[0].product == "Laptop");
        REQUIRE(orderLines[0].quantity == 2);
        REQUIRE(orderLines[0].price == Catch::Approx(999.99));
    }

    SECTION("Second order line")
    {
        REQUIRE(orderLines[1].product == "Mouse");
        REQUIRE(orderLines[1].quantity == 5);
        REQUIRE(orderLines[1].price == Catch::Approx(25.50));
    }

    SECTION("Third order line")
    {
        REQUIRE(orderLines[2].product == "Keyboard");
        REQUIRE(orderLines[2].quantity == 3);
        REQUIRE(orderLines[2].price == Catch::Approx(75.00));
    }
}

TEST_CASE("PrintReceipt generates output", "[receipt]")
{
    auto orderLines = MakeOrderLines();

    SECTION("Receipt without discount")
    {
        CoutCapture capture;
        PrintReceipt(orderLines, false);
        std::string output = capture.GetOutput();

        REQUIRE_FALSE(output.empty());
        REQUIRE(output.find("ACME Corp") != std::string::npos);
        REQUIRE(output.find("Laptop") != std::string::npos);
        REQUIRE(output.find("Mouse") != std::string::npos);
        REQUIRE(output.find("Keyboard") != std::string::npos);
        REQUIRE(output.find("Total:") != std::string::npos);
        REQUIRE(output.find("Discount") == std::string::npos); // No discount
    }

    SECTION("Receipt with discount")
    {
        CoutCapture capture;
        PrintReceipt(orderLines, true);
        std::string output = capture.GetOutput();

        REQUIRE_FALSE(output.empty());
        REQUIRE(output.find("ACME Corp") != std::string::npos);
        REQUIRE(output.find("Discount") != std::string::npos); // Should have discount
        REQUIRE(output.find("Total:") != std::string::npos);
    }
}

TEST_CASE("Calc function calculates totals correctly", "[calculation]")
{
    auto orderLines = MakeOrderLines();
    // Expected subtotal: 2*999.99 + 5*25.50 + 3*75.00 = 1999.98 + 127.50 + 225.00 = 2352.48
    double expectedSubtotal = 2352.48;

    SECTION("Without discount, without tax")
    {
        double result = Calc(false, orderLines, 0.0);
        REQUIRE(result == Catch::Approx(expectedSubtotal));
    }

    SECTION("With discount, without tax")
    {
        double result = Calc(true, orderLines, 0.0);
        double expectedWithDiscount = expectedSubtotal * 0.9;
        REQUIRE(result == Catch::Approx(expectedWithDiscount));
    }

    SECTION("Without discount, with tax")
    {
        double taxRate = 0.19;
        double result = Calc(false, orderLines, taxRate);
        double expectedWithTax = expectedSubtotal + (expectedSubtotal * taxRate);
        REQUIRE(result == Catch::Approx(expectedWithTax));
    }

    SECTION("With discount and tax")
    {
        double taxRate = 0.19;
        double result = Calc(true, orderLines, taxRate);
        double expectedWithDiscount = expectedSubtotal * 0.9;
        double expectedWithTax = expectedWithDiscount + (expectedWithDiscount * taxRate);
        REQUIRE(result == Catch::Approx(expectedWithTax));
    }
}

TEST_CASE("CalculateShipping computes shipping costs", "[shipping]")
{
    auto orderLines = MakeOrderLines();
    // Total items: 2 + 5 + 3 = 10 items
    // Total weight: 10 * 0.5 = 5.0 kg

    SECTION("Domestic shipping")
    {
        double result = CalculateShipping(orderLines, "domestic");
        // Weight = 5.0 kg, which is >= 5.0, so: 5.0 * 1.2 + 2.5 = 8.5
        REQUIRE(result == Catch::Approx(8.5));
    }

    SECTION("Europe shipping")
    {
        double result = CalculateShipping(orderLines, "europe");
        // Weight = 5.0 kg, which is >= 2.0, so: 5.0 * 2.8 + 8.0 = 22.0
        REQUIRE(result == Catch::Approx(22.0));
    }

    SECTION("International shipping")
    {
        double result = CalculateShipping(orderLines, "international");
        // Weight = 5.0 kg, which is >= 1.0, so: 5.0 * 4.5 + 15.0 = 37.5
        REQUIRE(result == Catch::Approx(37.5));
    }

    SECTION("Light package domestic")
    {
        std::vector<OrderLine> lightOrder = {{"Item", 1, 10.0}}; // 0.5kg
        double result = CalculateShipping(lightOrder, "domestic");
        // Weight < 5.0, so fixed rate: 5.99
        REQUIRE(result == Catch::Approx(5.99));
    }
}

TEST_CASE("GetOrderLineValue calculates line value", "[orderline]")
{
    OrderLine line{"Test Product", 3, 15.50};
    double result = GetOrderLineValue(line);
    REQUIRE(result == Catch::Approx(46.50)); // 3 * 15.50
}

TEST_CASE("Tax rate functions work correctly", "[tax]")
{
    SECTION("GetTaxRate returns correct rate")
    {
        double rate = GetTaxRate();
        REQUIRE(rate == Catch::Approx(0.19));
    }

    SECTION("CalculateTotalWithTax applies tax correctly")
    {
        double subtotal = 100.0;
        double result = CalculateTotalWithTax(subtotal);
        double expected = 100.0 + (100.0 * 0.19); // 119.0
        REQUIRE(result == Catch::Approx(expected));
    }
}

TEST_CASE("Customer class functionality", "[customer]")
{
    Customer customer;

    SECTION("Customer data can be set and accessed")
    {
        customer.name = "John Doe";
        customer.email = "john@example.com";
        customer.loyaltyPoints = 100;

        REQUIRE(customer.name == "John Doe");
        REQUIRE(customer.email == "john@example.com");
        REQUIRE(customer.loyaltyPoints == 100);
    }

    SECTION("Customer Display generates output")
    {
        customer.name = "Jane Smith";
        customer.email = "jane@example.com";
        customer.loyaltyPoints = 50;

        CoutCapture capture;
        customer.Display();
        std::string output = capture.GetOutput();

        REQUIRE(output.find("Jane Smith") != std::string::npos);
        REQUIRE(output.find("jane@example.com") != std::string::npos);
        REQUIRE(output.find("50") != std::string::npos);
    }

    SECTION("Loyalty points can be modified directly")
    {
        customer.loyaltyPoints = 100;
        customer.loyaltyPoints += 25;
        REQUIRE(customer.loyaltyPoints == 125);

        customer.loyaltyPoints -= 10;
        REQUIRE(customer.loyaltyPoints == 115);
    }
}

TEST_CASE("Global company name is accessible", "[globals]")
{
    // Note: This test demonstrates the problem with global variables
    std::string originalName = companyName;

    SECTION("Company name can be read")
    {
        REQUIRE(companyName == "ACME Corp");
    }

    SECTION("Company name can be changed globally")
    {
        companyName = "New Company";
        REQUIRE(companyName == "New Company");

        // This change affects all code using the global variable,
        // which is a maintenance problem
    }

    // Restore original value
    companyName = originalName;
}

TEST_CASE("Integration test - complete order processing", "[integration]")
{
    auto orderLines = MakeOrderLines();

    SECTION("Calculate total order value with all components")
    {
        // Calculate subtotal
        double subtotal = 0.0;
        for (const auto& line : orderLines)
        {
            subtotal += GetOrderLineValue(line);
        }
        REQUIRE(subtotal == Catch::Approx(2352.48));

        // Apply discount and tax
        double totalWithDiscountAndTax = Calc(true, orderLines, 0.19);
        double expectedDiscounted = subtotal * 0.9;
        double expectedFinal = expectedDiscounted + (expectedDiscounted * 0.19);
        REQUIRE(totalWithDiscountAndTax == Catch::Approx(expectedFinal));

        // Add shipping
        double shipping = CalculateShipping(orderLines, "domestic");
        double grandTotal = totalWithDiscountAndTax + shipping;

        REQUIRE(grandTotal > totalWithDiscountAndTax);
        REQUIRE(shipping == Catch::Approx(8.5));
    }
}

// Copyright (c) 2023-2024 Dr. Matthias Hölzl. All rights reserved.

// - Initial version of the invoice generator
// - Currently only supports produce and dairy message_contents
// - We want to extend it to support more departments
// - We have a test suite in the test subdirectory

#include "invoice_sk.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace invoice_sk::v0 {

std::string GenerateInvoice(const Order& order, const ProductMap& products) {
    double produceTotal {0.0};
    int produceItems {0};
    double dairyTotal {0.0};
    int dairyItems {0};

    std::ostringstream result;
    result << "Order for " << order.first << ":\n";

    for (const auto& [item, quantity] : order.second) {
        auto productIter = products.find(item);
        if (productIter == products.end()) {
            throw std::runtime_error("Product not found");
        }

        const auto& [itemPrice, department] = productIter->second;
        double discount {0.0}, discountedPrice {0.0}, price {0.0};
        if (department == "Produce") {
            produceItems += quantity;
            discount = quantity >= 4 ? 0.1 : 0.0;
            discountedPrice = itemPrice * (1 - discount);
            price = discountedPrice * quantity;
            produceTotal += price;
            result << "  - " << std::left << std::setw(12) << (item + ":") << std::right
                   << std::setw(4) << quantity << " à " << std::fixed
                   << std::setprecision(2) << itemPrice << " = $" << price;
            if (discount > 0) {
                result << " (discount: $" << (itemPrice * quantity - price) << ")";
            }
            result << "\n";
        } else if (department == "Dairy") {
            dairyItems += quantity;
            discount = quantity >= 5 ? 0.05 : 0.0;
            discountedPrice = itemPrice * (1 - discount);
            price = discountedPrice * quantity;
            dairyTotal += price;
            result << "  - " << std::left << std::setw(12) << (item + ":") << std::right
                   << std::setw(4) << quantity << " à " << std::fixed
                   << std::setprecision(2) << itemPrice << " = $" << price;
            if (discount > 0) {
                result << " (discount: $" << (itemPrice * quantity - price) << ")";
            }
            result << "\n";
        } else {
            throw std::runtime_error("Unknown department: " + department);
        }
    }

    double volumeDiscount {0.0};
    if (produceItems >= 10) {
        volumeDiscount += produceTotal * 0.05;
    }
    if (dairyItems >= 10) {
        volumeDiscount += dairyTotal * 0.1;
    }
    double total = produceTotal + dairyTotal;

    if (volumeDiscount > 0) {
        result << "Subtotal:        $" << total << "\n";
        result << "Volume discount: $" << volumeDiscount << "\n";
        result << "Total:           $" << (total - volumeDiscount);
    } else {
        result << "Total: $" << total;
    }
    return result.str();
}
} // namespace invoice_sk::v0

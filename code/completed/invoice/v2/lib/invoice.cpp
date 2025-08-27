// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "invoice.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace invoice::v2 {

struct DepartmentStatistics {
    double produceTotal {0.0};
    int produceItems {0};
    double dairyTotal {0.0};
    int dairyItems {0};
};

std::string GenerateInvoice(const Order& order, const ProductMap& products) {
    DepartmentStatistics statistics;

    std::ostringstream result;
    result << "Order for " << order.first << ":\n";

    for (const auto& lineItem : order.second) {
        const auto& [item, quantity] {lineItem};
        const auto& [itemPrice, department] = products.at(item);

        double discount {0.0}, discountedPrice {0.0}, price {0.0};
        if (department == "Produce") {
            statistics.produceItems += quantity;
            discount = quantity >= 4 ? 0.1 : 0.0;
            discountedPrice = itemPrice * (1 - discount);
            price = discountedPrice * quantity;
            statistics.produceTotal += price;
            result << "  - " << std::left << std::setw(12) << (item + ":") << std::right
                   << std::setw(4) << quantity << " à " << std::fixed
                   << std::setprecision(2) << itemPrice << " = $" << price;
            if (discount > 0) {
                result << " (discount: $" << (itemPrice * quantity - price) << ")";
            }
            result << "\n";
        } else if (department == "Dairy") {
            statistics.dairyItems += quantity;
            discount = quantity >= 5 ? 0.05 : 0.0;
            discountedPrice = itemPrice * (1 - discount);
            price = discountedPrice * quantity;
            statistics.dairyTotal += price;
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
    if (statistics.produceItems >= 10) {
        volumeDiscount += statistics.produceTotal * 0.05;
    }
    if (statistics.dairyItems >= 10) {
        volumeDiscount += statistics.dairyTotal * 0.1;
    }
    double total = statistics.produceTotal + statistics.dairyTotal;

    if (volumeDiscount > 0) {
        result << "Subtotal:        $" << total << "\n";
        result << "Volume discount: $" << volumeDiscount << "\n";
        result << "Total:           $" << (total - volumeDiscount);
    } else {
        result << "Total: $" << total;
    }
    return result.str();
}
} // namespace invoice::v2

// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "invoice.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace invoice::v4 {

struct DepartmentStatistics {
    double total {0.0};
    int items {0};
};

void AddLineForSingleItem(
    std::map<std::string, DepartmentStatistics>& statistics,
    const std::pair<std::string, int>& lineItem, const ProductMap& products,
    std::ostringstream& result
);

std::ostringstream& AddVolumeDiscount(
    std::map<std::string, DepartmentStatistics>& statistics, std::ostringstream& result
);

std::string GenerateInvoice(const Order& order, const ProductMap& products) {
    std::ostringstream result;
    result << "Order for " << order.first << ":\n";
    std::map<std::string, DepartmentStatistics> statistics;

    for (const auto& lineItem : order.second) {
        AddLineForSingleItem(statistics, lineItem, products, result);
    }
    AddVolumeDiscount(statistics, result);

    return result.str();
}

void AddLineForSingleItem(
    std::map<std::string, DepartmentStatistics>& statistics,
    const std::pair<std::string, int>& lineItem, const ProductMap& products,
    std::ostringstream& result
) {
    const auto& [itemName, quantity] {lineItem};
    const auto& [itemPrice, departmentName] = products.at(itemName);

    double discount {};
    double discountedPrice {};
    double price {};

    if (departmentName == "Produce") {
        statistics[departmentName].items += quantity;
        discount = quantity >= 4 ? 0.1 : 0.0;
        discountedPrice = itemPrice * (1 - discount);
        price = discountedPrice * quantity;
        statistics[departmentName].total += price;
        result << "  - " << std::left << std::setw(12) << (itemName + ":") << std::right
               << std::setw(4) << quantity << " à " << std::fixed
               << std::setprecision(2) << itemPrice << " = $" << price;
        if (discount > 0) {
            result << " (discount: $" << (itemPrice * quantity - price) << ")";
        }
        result << "\n";
    } else if (departmentName == "Dairy") {
        statistics[departmentName].items += quantity;
        discount = quantity >= 5 ? 0.05 : 0.0;
        discountedPrice = itemPrice * (1 - discount);
        price = discountedPrice * quantity;
        statistics[departmentName].total += price;
        result << "  - " << std::left << std::setw(12) << (itemName + ":") << std::right
               << std::setw(4) << quantity << " à " << std::fixed
               << std::setprecision(2) << itemPrice << " = $" << price;
        if (discount > 0) {
            result << " (discount: $" << (itemPrice * quantity - price) << ")";
        }
        result << "\n";
    } else {
        throw std::runtime_error("Unknown department: " + departmentName);
    }
}

std::ostringstream& AddVolumeDiscount(
    std::map<std::string, DepartmentStatistics>& statistics, std::ostringstream& result
) {
    double volumeDiscount {0.0};
    DepartmentStatistics& produceStatistics {statistics["Produce"]};
    if (produceStatistics.items >= 10) {
        volumeDiscount += produceStatistics.total * 0.05;
    }
    DepartmentStatistics& dairyStatistics {statistics["Dairy"]};
    if (dairyStatistics.items >= 10) {
        volumeDiscount += dairyStatistics.total * 0.1;
    }
    double total = dairyStatistics.total + produceStatistics.total;

    if (volumeDiscount > 0) {
        result << "Subtotal:        $" << total << "\n";
        result << "Volume discount: $" << volumeDiscount << "\n";
        result << "Total:           $" << (total - volumeDiscount);
    } else {
        result << "Total: $" << total;
    }
    return result;
}
} // namespace invoice::v4

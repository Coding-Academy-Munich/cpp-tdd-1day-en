// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "invoice.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <stdexcept>

namespace invoice::v5 {

struct DepartmentStatistics {
    double total {0.0};
    int items {0};
};

struct Department {
    std::string name;
    double discount {};
    int discountThreshold {};
    double volumeDiscount {};
};

const std::map<std::string, Department> departments {
    {"Produce", {"Produce", 0.1, 4, 0.05}},
    {"Dairy", {"Dairy", 0.05, 5, 0.1}},
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
    auto& department {departments.at(departmentName)};

    statistics[departmentName].items += quantity;
    double discount {
        quantity >= department.discountThreshold ? department.discount : 0.0};
    double discountedPrice {itemPrice * (1 - discount)};
    double price {discountedPrice * quantity};
    statistics[departmentName].total += price;
    result << "  - " << std::left << std::setw(12) << (itemName + ":") << std::right
           << std::setw(4) << quantity << " à " << std::fixed << std::setprecision(2)
           << itemPrice << " = $" << price;
    if (discount > 0) {
        result << " (discount: $" << (itemPrice * quantity - price) << ")";
    }
    result << "\n";
}

std::ostringstream& AddVolumeDiscount(
    std::map<std::string, DepartmentStatistics>& statistics, std::ostringstream& result
) {
    double volumeDiscount {0.0};
    for (const auto& [departmentName, department] : departments) {
        DepartmentStatistics& departmentStatistics {statistics[departmentName]};
        if (departmentStatistics.items >= 10) {
            volumeDiscount += departmentStatistics.total * department.volumeDiscount;
        }
    }
    double total {std::accumulate(
        statistics.begin(), statistics.end(), 0.0,
        [](double sum, const auto& pair) {
            const auto& [departmentName, departmentStatistics] {pair};
            return sum + departmentStatistics.total;
        }
    )};

    if (volumeDiscount > 0) {
        result << "Subtotal:        $" << total << "\n";
        result << "Volume discount: $" << volumeDiscount << "\n";
        result << "Total:           $" << (total - volumeDiscount);
    } else {
        result << "Total: $" << total;
    }
    return result;
}
} // namespace invoice::v5

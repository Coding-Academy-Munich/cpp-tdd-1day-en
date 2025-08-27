// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "invoice.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <stdexcept>

namespace invoice::v6 {

extern const std::map<std::string, Department> departments {
    {"Produce", {"Produce", 0.1, 4, 0.05}},
    {"Dairy", {"Dairy", 0.05, 5, 0.1}},
};

std::string GenerateInvoice(const Order& order, const ProductMap& products) {
    std::ostringstream stream;
    stream << "Order for " << order.first << ":\n";
    DepartmentStatsMap statistics;

    for (const auto& lineItem : order.second) {
        AddLineForSingleItem(statistics, lineItem, products, stream);
    }
    AddVolumeDiscount(statistics, stream);

    return stream.str();
}

void AddLineForSingleItem(
    DepartmentStatsMap& statistics, const std::pair<std::string, int>& lineItem,
    const ProductMap& products, std::ostringstream& stream
) {
    const auto& [itemName, quantity] {lineItem};
    const auto& [itemPrice, departmentName] = products.at(itemName);
    statistics[departmentName].items += quantity;

    double discount {ComputeDiscount(departmentName, quantity)};
    double discountedPrice {itemPrice * (1 - discount)};
    double price {discountedPrice * quantity};
    statistics[departmentName].total += price;
    stream << "  - " << std::left << std::setw(12) << (itemName + ":") << std::right
           << std::setw(4) << quantity << " à " << std::fixed << std::setprecision(2)
           << itemPrice << " = $" << price;
    if (discount > 0) {
        stream << " (discount: $" << (itemPrice * quantity - price) << ")";
    }
    stream << "\n";
}

double ComputeDiscount(const std::string& departmentName, int quantity) {
    auto& department {departments.at(departmentName)};
    double discount {
        quantity >= department.discountThreshold ? department.discount : 0.0};
    return discount;
}

std::ostringstream&
AddVolumeDiscount(DepartmentStatsMap& statistics, std::ostringstream& stream) {
    double volumeDiscount {ComputeVolumeDiscount(statistics)};
    double total {ComputeTotal(statistics)};
    PrintDiscount(stream, volumeDiscount, total);

    return stream;
}

std::ostringstream&
PrintDiscount(std::ostringstream& stream, double volumeDiscount, double total) {
    if (volumeDiscount > 0) {
        stream << "Subtotal:        $" << total << "\n";
        stream << "Volume discount: $" << volumeDiscount << "\n";
        stream << "Total:           $" << (total - volumeDiscount);
    } else {
        stream << "Total: $" << total;
    }
    return stream;
}

double ComputeVolumeDiscount(DepartmentStatsMap& statistics) {
    double volumeDiscount {0.0};
    for (const auto& [departmentName, department] : departments) {
        DepartmentStatistics& departmentStatistics {statistics[departmentName]};
        if (departmentStatistics.items >= 10) {
            volumeDiscount += departmentStatistics.total * department.volumeDiscount;
        }
    }
    return volumeDiscount;
}

double ComputeTotal(const DepartmentStatsMap& statistics) {
    return std::accumulate(
        statistics.begin(), statistics.end(), 0.0,
        [](double sum, const auto& pair) {
            const auto& [departmentName, departmentStatistics] {pair};
            return sum + departmentStatistics.total;
        }
    );
}
} // namespace invoice::v6

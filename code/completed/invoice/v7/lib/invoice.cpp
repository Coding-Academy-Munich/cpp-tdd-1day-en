// Copyright (c) 2023-2024 Dr. Matthias Hölzl. All rights reserved.

#include "invoice.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <stdexcept>

namespace invoice::v7 {

ProductMap
ProductsFromDescriptions(const std::map<std::string, ProductDescription>& descriptions) {
    ProductMap products {};
    for (const auto& [productName, productDescription] : descriptions) {
        products[productName] = Product {productDescription};
    }
    return products;
}

extern const std::map<std::string, Department> departments {
    {"Produce", {"Produce", 0.1, 4, 0.05}},
    {"Dairy", {"Dairy", 0.05, 5, 0.1}},
};

std::string GenerateInvoice(const Order& order, const ProductMap& products) {
    OrderTracker ot;
    ot.GetStream() << "Order for " << order.first << ":\n";

    for (const auto& lineItem : order.second) {
        AddLineForSingleItem(ot, lineItem, products);
    }
    ot.AddVolumeDiscount();

    return ot.GetStream().str();
}

void AddLineForSingleItem(
    OrderTracker& ot, const std::pair<std::string, int>& lineItem,
    const ProductMap& products
) {
    const auto& [itemName, quantity] {lineItem};

    const auto& [itemPrice, departmentName] = products.at(itemName);
    const double discount {ComputeDiscount(departmentName, quantity)};
    const double discountedPrice {itemPrice * (1 - discount)};
    const double price {discountedPrice * quantity};
    ot[departmentName].items += quantity;
    ot[departmentName].total += price;

    ot.GetStream() << "  - " << std::left << std::setw(12) << (itemName + ":") << std::right
                   << std::setw(4) << quantity << " à " << std::fixed
                   << std::setprecision(2) << itemPrice << " = $" << price;
    if (discount > 0) {
        ot.GetStream() << " (discount: $" << (itemPrice * quantity - price) << ")";
    }
    ot.GetStream() << "\n";
}

void OrderTracker::AddVolumeDiscount() {
    double volumeDiscount {ComputeVolumeDiscount()};
    double total {ComputeTotal()};
    PrintDiscount(volumeDiscount, total);
}

double OrderTracker::ComputeVolumeDiscount() {
    double volumeDiscount {0.0};
    for (const auto& [departmentName, department] : departments) {
        DepartmentStatistics& departmentStatistics {statistics[departmentName]};
        if (departmentStatistics.items >= 10) {
            volumeDiscount += departmentStatistics.total * department.volumeDiscount;
        }
    }
    return volumeDiscount;
}

double OrderTracker::ComputeTotal() {
    return std::accumulate(
        statistics.begin(), statistics.end(), 0.0,
        [](double sum, const auto& pair) {
            const auto& [departmentName, departmentStatistics] {pair};
            return sum + departmentStatistics.total;
        }
    );
}

void OrderTracker::PrintDiscount(double volumeDiscount, double total) {
    if (volumeDiscount > 0) {
        stream << "Subtotal:        $" << total << "\n";
        stream << "Volume discount: $" << volumeDiscount << "\n";
        stream << "Total:           $" << (total - volumeDiscount);
    } else {
        stream << "Total: $" << total;
    }
}

double ComputeDiscount(const std::string& departmentName, int quantity) {
    auto& department {departments.at(departmentName)};
    double discount {quantity >= department.discountThreshold ? department.discount : 0.0};
    return discount;
}
} // namespace invoice::v7

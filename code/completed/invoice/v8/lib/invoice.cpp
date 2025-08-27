// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "invoice.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <stdexcept>

namespace invoice::v8 {

ProductMap
ProductsFromDescriptions(const std::map<std::string, ProductDescription>& descriptions
) {
    ProductMap products {};
    for (const auto& [productName, productDescription] : descriptions) {
        products[productName] = Product {productName, productDescription};
    }
    return products;
}

extern const std::map<std::string, Department> departments {
    {"Produce", {"Produce", 0.1, 4, 0.05}},
    {"Dairy", {"Dairy", 0.05, 5, 0.1}},
};

double Product::Discount(int quantity) const {
    const Department& department {departments.at(departmentName)};
    return quantity >= department.discountThreshold ? department.discount : 0.0;
}

double Product::DiscountedPrice(int quantity) const {
    return price * (1 - Discount(quantity));
}

double Product::TotalPrice(int quantity) const {
    return DiscountedPrice(quantity) * quantity;
}

std::string GenerateInvoice(const Order& order, const ProductMap& products) {
    OrderTracker ot {order.first, products};

    for (const auto& [productName, quantity] : order.second) {
        ot.RegisterSale(productName, quantity);
        ot.PrintLineItem(productName, quantity);
    }
    ot.AddVolumeDiscount();

    return ot.GetStream().str();
}

void OrderTracker::RegisterSale(const std::string& productName, int quantity) {
    const auto& product {GetProduct(productName)};
    DepartmentStatistics& departmentStatistics {
        statistics[product.GetDepartmentName()]};
    departmentStatistics.items += quantity;
    departmentStatistics.total += product.TotalPrice(quantity);
}

void OrderTracker::PrintLineItem(const std::string& productName, int quantity) {
    const Product product {GetProduct(productName)};
    stream << "  - " << std::left << std::setw(12) << (product.GetName() + ":")
           << std::right << std::setw(4) << quantity << " à " << std::fixed
           << std::setprecision(2) << product.GetPrice() << " = $"
           << product.TotalPrice(quantity);
    if (product.Discount(quantity) > 0) {
        stream << " (discount: $"
               << (product.GetPrice() * quantity - product.TotalPrice(quantity)) << ")";
    }
    stream << "\n";
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
    double discount {
        quantity >= department.discountThreshold ? department.discount : 0.0};
    return discount;
}
} // namespace invoice::v8

// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_INVOICE_LIB_V7_INVOICE_H
#define COMPLETED_INVOICE_LIB_V7_INVOICE_H

#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace invoice::v7 {

using ProductDescription = std::pair<double, std::string>;

struct Product {
    Product() = default;
    Product(double price, std::string departmentName)
        : price {price}, departmentName {std::move(departmentName)} { }
    explicit Product(const ProductDescription& description)
        : price {description.first}, departmentName {description.second} { }

    double price {};
    std::string departmentName;
};

using ProductMap = std::map<std::string, Product>;

ProductMap
ProductsFromDescriptions(const std::map<std::string, ProductDescription>& descriptions);

using Item = std::pair<std::string, int>;
using Order = std::pair<std::string, std::vector<Item>>;

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

extern const std::map<std::string, Department> departments;

class OrderTracker {
public:
    OrderTracker() = default;
    OrderTracker(const OrderTracker&) = delete;
    OrderTracker(OrderTracker&&) noexcept = default;
    OrderTracker& operator=(const OrderTracker&) = delete;
    OrderTracker& operator=(OrderTracker&&) = default;
    ~OrderTracker() = default;

    DepartmentStatistics& operator[](const std::string& departmentName) {
        return statistics[departmentName];
    }

    const DepartmentStatistics& operator[](const std::string& departmentName) const {
        return statistics.at(departmentName);
    }

    [[nodiscard]] auto begin() const { return statistics.begin(); }
    [[nodiscard]] auto end() const { return statistics.end(); }

    [[nodiscard]] std::ostringstream& GetStream() { return stream; }

    void AddVolumeDiscount();
    double ComputeTotal();
    double ComputeVolumeDiscount();
    void PrintDiscount(double volumeDiscount, double total);

private:
    std::map<std::string, DepartmentStatistics> statistics;
    std::ostringstream stream {};
};

std::string GenerateInvoice(const Order& order, const ProductMap& products);

void AddLineForSingleItem(
    OrderTracker& ot, const std::pair<std::string, int>& lineItem,
    const ProductMap& products
);

double ComputeDiscount(const std::string& departmentName, int quantity);

} // namespace invoice::v7

#endif // COMPLETED_INVOICE_LIB_V7_INVOICE_H
// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_INVOICE_LIB_V8_INVOICE_H
#define COMPLETED_INVOICE_LIB_V8_INVOICE_H

#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace invoice::v8 {

using ProductDescription = std::pair<double, std::string>;

class Product {
public:
    Product() = default;
    Product(std::string name, double price, std::string departmentName)
        : name {std::move(name)}
        , price {price}
        , departmentName {std::move(departmentName)} { }
    Product(std::string name, const ProductDescription& description)
        : name {std::move(name)}
        , price {description.first}
        , departmentName {description.second} { }

    [[nodiscard]] const std::string& GetName() const { return name; }
    [[nodiscard]] double GetPrice() const { return price; }
    [[nodiscard]] const std::string& GetDepartmentName() const {
        return departmentName;
    }
    [[nodiscard]] double Discount(int quantity) const;
    [[nodiscard]] double DiscountedPrice(int quantity) const;
    [[nodiscard]] double TotalPrice(int quantity) const;

private:
    std::string name;
    [[maybe_unused]] double price {};
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
    OrderTracker(std::string customerName, ProductMap products)
        : customerName {std::move(customerName)}, products {std::move(products)} {
        stream << "Order for " << this->customerName << ":\n";
    };
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

    [[nodiscard]] const std::string& GetCustomerName() const { return customerName; }
    [[nodiscard]] const Product& GetProduct(const std::string& productName) const {
        return products.at(productName);
    }
    [[nodiscard]] const ProductMap& GetProducts() const { return products; }
    [[nodiscard]] std::ostringstream& GetStream() { return stream; }

    void RegisterSale(const std::string& productName, int quantity);
    void AddVolumeDiscount();
    double ComputeTotal();
    double ComputeVolumeDiscount();
    void PrintLineItem(const std::string& productName, int quantity);
    void PrintDiscount(double volumeDiscount, double total);

private:
    std::string customerName;
    ProductMap products;
    std::map<std::string, DepartmentStatistics> statistics;
    std::ostringstream stream {};
};

std::string GenerateInvoice(const Order& order, const ProductMap& products);

double ComputeDiscount(const std::string& departmentName, int quantity);

} // namespace invoice::v8

#endif // COMPLETED_INVOICE_LIB_V8_INVOICE_H
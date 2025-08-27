// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_INVOICE_LIB_V6_INVOICE_H
#define COMPLETED_INVOICE_LIB_V6_INVOICE_H

#include <map>
#include <string>
#include <utility>
#include <vector>

namespace invoice::v6 {
using Product = std::pair<double, std::string>;
using ProductMap = std::map<std::string, Product>;

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

class DepartmentStatsMap {
public:
    DepartmentStatistics& operator[](const std::string& departmentName) {
        return statistics[departmentName];
    }

    const DepartmentStatistics& operator[](const std::string& departmentName) const {
        return statistics.at(departmentName);
    }

    [[nodiscard]] auto begin() const { return statistics.begin(); }
    [[nodiscard]] auto end() const { return statistics.end(); }

private:
    std::map<std::string, DepartmentStatistics> statistics;
};

std::string GenerateInvoice(const Order& order, const ProductMap& products);

void AddLineForSingleItem(
    DepartmentStatsMap& statistics, const std::pair<std::string, int>& lineItem,
    const ProductMap& products, std::ostringstream& stream
);

std::ostringstream&
AddVolumeDiscount(DepartmentStatsMap& statistics, std::ostringstream& stream);

double ComputeDiscount(const std::string& departmentName, int quantity);

double ComputeTotal(const DepartmentStatsMap& statistics);

double ComputeVolumeDiscount(DepartmentStatsMap& statistics);

std::ostringstream&
PrintDiscount(std::ostringstream& stream, double volumeDiscount, double total);

} // namespace invoice::v6

#endif // COMPLETED_INVOICE_LIB_V6_INVOICE_H
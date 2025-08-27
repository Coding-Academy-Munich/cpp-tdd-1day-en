// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "invoice.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <stdexcept>

namespace invoice::v9 {

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

std::string GenerateInvoice(const Order& order, const ProductMap& products) {
    OrderTracker ot {order.first, products};

    for (const auto& [productName, quantity] : order.second) {
        ot.RegisterSale(productName, quantity);
    }

    return ot.ToString();
}

void OrderTracker::RegisterSale(const std::string& productName, int quantity) {
    const auto& product {GetProduct(productName)};
    lineItems.emplace_back(&product, quantity);
    DepartmentStatistics& departmentStatistics {
        statistics[product.GetDepartmentName()]};
    departmentStatistics.items += quantity;
    departmentStatistics.total += product.TotalPrice(quantity);
}

std::string OrderTracker::ToString() const {
    std::ostringstream stream;
    PrintCustomerInfo(stream);
    for (const auto& lineItem : lineItems) {
        PrintLineItem(stream, lineItem);
    }
    PrintVolumeDiscountAndTotal(stream);
    return stream.str();
}

double OrderTracker::ComputeTotal() const {
    return std::accumulate(
        statistics.begin(), statistics.end(), 0.0,
        [](double sum, const auto& pair) {
            const auto& [departmentName, departmentStatistics] {pair};
            return sum + departmentStatistics.total;
        }
    );
}

double OrderTracker::ComputeVolumeDiscount() const {
    double volumeDiscount {0.0};
    for (const auto& [departmentName, department] : departments) {
        const DepartmentStatistics& departmentStatistics {statistics[departmentName]};
        if (departmentStatistics.items >= 10) {
            volumeDiscount += departmentStatistics.total * department.volumeDiscount;
        }
    }
    return volumeDiscount;
}

void OrderTracker::PrintCustomerInfo(std::ostream& stream) const {
    stream << "Order for " << this->customerName << ":\n";
}

void OrderTracker::PrintLineItem(std::ostream& stream, const LineItem& lineItem) {
    stream << "  - " << std::left << std::setw(12)
           << (lineItem.product->GetName() + ":") << std::right << std::setw(4)
           << lineItem.quantity << " à " << std::fixed << std::setprecision(2)
           << lineItem.product->GetPrice() << " = $"
           << lineItem.product->TotalPrice(lineItem.quantity);
    if (lineItem.product->Discount(lineItem.quantity) > 0) {
        stream << " (discount: $"
               << (lineItem.product->GetPrice() * lineItem.quantity
                   - lineItem.product->TotalPrice(lineItem.quantity))
               << ")";
    }
    stream << "\n";
}

void OrderTracker::PrintVolumeDiscountAndTotal(std::ostream& stream) const {
    double volumeDiscount {ComputeVolumeDiscount()};
    double total {ComputeTotal()};

    if (volumeDiscount > 0) {
        stream << "Subtotal:        $" << total << "\n";
        stream << "Volume discount: $" << volumeDiscount << "\n";
        stream << "Total:           $" << (total - volumeDiscount);
    } else {
        stream << "Total: $" << total;
    }
}

} // namespace invoice::v9

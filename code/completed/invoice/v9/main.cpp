// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "invoice.h"
#include "invoice_data.h"
#include <algorithm>
#include <iostream>

using namespace invoice::v9;

int main() {
    ProductMap products {ProductsFromDescriptions(invoice::data::products)};
    for (const auto& order : invoice::data::orders) {
        std::cout << GenerateInvoice(order, products);
        std::cout << "\n=========================================\n";
    }
}

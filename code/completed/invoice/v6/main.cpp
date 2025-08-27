// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "invoice.h"
#include "invoice_data.h"
#include <iostream>

using namespace invoice::v6;
using namespace invoice::data;

int main() {
    for (const auto& order : orders) {
        std::cout << GenerateInvoice(order, products);
        std::cout << "\n=========================================\n";
    }
}

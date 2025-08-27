// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "invoice_sk.h"
#include "invoice_sk_data.h"
#include <iostream>

using namespace invoice_sk::v0;
using namespace invoice_sk::data;

int main() {
    for (const auto& order : orders) {
        std::cout << GenerateInvoice(order, products);
        std::cout << "\n=========================================\n";
    }
}

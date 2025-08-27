// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef STARTER_KITS_INVOICE_SK_LIB_V0_INVOICE_SK_H
#define STARTER_KITS_INVOICE_SK_LIB_V0_INVOICE_SK_H

#include <map>
#include <string>
#include <utility>
#include <vector>

namespace invoice_sk::v0 {
using Product = std::pair<double, std::string>;
using ProductMap = std::map<std::string, Product>;

using Item = std::pair<std::string, int>;
using Order = std::pair<std::string, std::vector<Item>>;

std::string GenerateInvoice(const Order& order, const ProductMap& products);
} // namespace invoice_sk::v0

#endif // STARTER_KITS_INVOICE_SK_LIB_V0_INVOICE_SK_H
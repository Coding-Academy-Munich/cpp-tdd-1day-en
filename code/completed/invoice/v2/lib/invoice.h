// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_INVOICE_LIB_V2_INVOICE_H
#define COMPLETED_INVOICE_LIB_V2_INVOICE_H

#include <map>
#include <string>
#include <utility>
#include <vector>

namespace invoice::v2 {
using Product = std::pair<double, std::string>;
using ProductMap = std::map<std::string, Product>;

using Item = std::pair<std::string, int>;
using Order = std::pair<std::string, std::vector<Item>>;

std::string GenerateInvoice(const Order& order, const ProductMap& products);
} // namespace invoice::v2

#endif // COMPLETED_INVOICE_LIB_V2_INVOICE_H
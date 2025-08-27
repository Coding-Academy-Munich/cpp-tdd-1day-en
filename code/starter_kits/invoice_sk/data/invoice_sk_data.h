// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef STARTER_KITS_INVOICE_SK_DATA_INVOICE_SK_DATA_H
#define STARTER_KITS_INVOICE_SK_DATA_INVOICE_SK_DATA_H

#include "invoice_sk.h"

namespace invoice_sk::data {

using Product = std::pair<double, std::string>;
using ProductMap = std::map<std::string, Product>;

using Item = std::pair<std::string, int>;
using Order = std::pair<std::string, std::vector<Item>>;
using OrderList = std::vector<Order>;

extern ProductMap products;
extern OrderList orders;

} // namespace invoice_sk::data

#endif // STARTER_KITS_INVOICE_SK_DATA_INVOICE_SK_DATA_H
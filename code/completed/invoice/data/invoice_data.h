// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef STARTER_KITS_invoice_DATA_invoice_DATA_H
#define STARTER_KITS_invoice_DATA_invoice_DATA_H

#include "invoice.h"

namespace invoice::data {

using Product = std::pair<double, std::string>;
using ProductMap = std::map<std::string, Product>;

using Item = std::pair<std::string, int>;
using Order = std::pair<std::string, std::vector<Item>>;
using OrderList = std::vector<Order>;

extern ProductMap products;
extern OrderList orders;

} // namespace invoice::data

#endif // STARTER_KITS_invoice_DATA_invoice_DATA_H
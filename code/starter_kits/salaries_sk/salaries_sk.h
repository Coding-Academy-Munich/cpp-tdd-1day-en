// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once

#ifndef SALARIES_SK_SALARIES_SK_H
#define SALARIES_SK_SALARIES_SK_H
#include <vector>

namespace salaries_sk
{
double handle_money_stuff(
    int i_dow, double d_spd, const char* pc_n, std::vector<double>& dv_slrs
);
} // namespace salaries_sk

#endif // SALARIES_SK_SALARIES_SK_H

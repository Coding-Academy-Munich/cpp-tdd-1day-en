// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "leap_year.h"

bool is_leap_year(int year)
{
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

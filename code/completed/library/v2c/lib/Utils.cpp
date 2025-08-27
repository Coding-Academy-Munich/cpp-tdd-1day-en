// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Utils.h"

namespace library::v2c {

std::chrono::year_month_day MakeYearMonthDay(
    int year, unsigned int month, unsigned int day)
{
    return {
        std::chrono::year {year}, std::chrono::month {month}, std::chrono::day {day}};
}
} // namespace library::v2c
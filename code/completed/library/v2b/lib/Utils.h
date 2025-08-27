// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#ifndef COMPLETED_LIBRARY_V2B_LIB_UTILS_H
#define COMPLETED_LIBRARY_V2B_LIB_UTILS_H

#include <chrono>
#include <ostream>
#include <utility>
#include <vector>

namespace library::v2b {

std::chrono::year_month_day MakeYearMonthDay(
    int year, unsigned int month, unsigned int day);

template <typename T> struct JoinVector {
    explicit JoinVector(const std::vector<T>& vector, std::string separator = ", ")
        : JoinVector(vector, std::move(separator), "[", "]")
    {
    }

    JoinVector(const std::vector<T>& vector, std::string separator, std::string prefix,
        std::string suffix)
        : vector(vector)
        , separator(std::move(separator))
        , prefix(std::move(prefix))
        , suffix(std::move(suffix))
    {
    }

    const std::vector<T>& vector;
    const std::string separator;
    const std::string prefix;
    const std::string suffix;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const JoinVector<T>& joinVector)
{
    os << joinVector.prefix;
    std::string separator;
    for (const auto& element : joinVector.vector) {
        os << separator << element;
        separator = joinVector.separator;
    }
    os << joinVector.suffix;
    return os;
}
} // namespace library::v2b

#endif // COMPLETED_LIBRARY_V2B_LIB_UTILS_H

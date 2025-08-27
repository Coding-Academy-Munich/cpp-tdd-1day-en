// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "etl_expected.h"
#include <cmath>

etl::expected<double, ParseError> parse_int(const std::string& str)
{
    const char* begin = str.data();
    char* end;
    double num{std::strtod(begin, &end)};

    if (begin == end) {
        return etl::unexpected<ParseError>{ParseError::invalid_input};
    } else if (std::isinf(num)) {
        return etl::unexpected<ParseError>{ParseError::overflow};
    }

    return num;
}

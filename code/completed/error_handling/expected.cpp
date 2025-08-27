// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "expected.h"
#include <cmath>

std::expected<double, ParseError> parse_int(const std::string& str)
{
    const char* begin = str.data();
    char* end;
    double num{std::strtod(begin, &end)};

    if (begin == end) {
        return std::unexpected<ParseError>{ParseError::invalid_input};
    } else if (std::isinf(num)) {
        return std::unexpected<ParseError>{ParseError::overflow};
    }

    return num;
}

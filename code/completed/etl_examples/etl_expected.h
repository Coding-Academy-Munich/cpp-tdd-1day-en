// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ETL_EXAMPLES_ETL_EXPECTED_H
#define COMPLETED_ETL_EXAMPLES_ETL_EXPECTED_H

#include "etl/expected.h"
#include <string>

enum class ParseError : int {
    invalid_input,
    overflow,
};

etl::expected<double, ParseError> parse_int(const std::string& str);
#endif // COMPLETED_ETL_EXAMPLES_ETL_EXPECTED_H

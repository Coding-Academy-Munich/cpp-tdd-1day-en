// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ERROR_HANDLING_EXPECTED_H
#define COMPLETED_ERROR_HANDLING_EXPECTED_H

#include <expected>
#include <string>

enum class ParseError : int {
    invalid_input,
    overflow,
};

std::expected<double, ParseError> parse_int(const std::string& str);
#endif // COMPLETED_ERROR_HANDLING_EXPECTED_H

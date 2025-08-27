// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "expected.h"
#include <iostream>

void print_result(std::expected<double, ParseError> result)
{
    // if (result.has_value()) is also possible
    if (result) {
        std::cout << "Result: " << result.value() << ", " << *result << "\n";
    } else if (result.error() == ParseError::invalid_input) {
        std::cout << "Error: Invalid input\n";
    } else if (result.error() == ParseError::overflow) {
        std::cout << "Error: Overflow\n";
    } else {
        std::cout << "Error: " << static_cast<int>(result.error()) << "\n";
    }
}

int main()
{
    print_result(parse_int("123"));
    print_result(parse_int("1.23"));
    print_result(parse_int("300e300"));
    print_result(parse_int("500e500"));
    print_result(parse_int(""));
    print_result(parse_int("abc"));

    return 0;
}

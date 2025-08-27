#pragma once
#ifndef UNIT_TESTING_CHECK_H
#define UNIT_TESTING_CHECK_H

#include <iostream>

void check(bool condition, std::string message = "Test failed!")
{
    if (!condition)
    {
        std::cerr << message << "\n";
    }
}
#endif // UNIT_TESTING_CHECK_H
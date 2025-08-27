// Copyright (c) 2024-2025 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef ORDER_PROCESSOR_SK_TEST_COUT_REDIRECT_H
#define ORDER_PROCESSOR_SK_TEST_COUT_REDIRECT_H

#include <iostream>
#include <sstream>
#include <string>

class CoutRedirect
{
public:
    CoutRedirect()
    {
        saved_cout_buf = std::cout.rdbuf();
        std::cout.rdbuf(ss.rdbuf());
    }

    ~CoutRedirect() { std::cout.rdbuf(saved_cout_buf); }

    std::string get_output() { return ss.str(); }

private:
    std::streambuf* saved_cout_buf;
    std::stringstream ss;
};

#endif // ORDER_PROCESSOR_TEST_COUT_REDIRECT_H

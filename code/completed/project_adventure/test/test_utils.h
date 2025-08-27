// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#ifndef PROJECT_ADVENTURE_TEST_TEST_UTILS_H
#define PROJECT_ADVENTURE_TEST_TEST_UTILS_H

#include <iostream>
#include <sstream>
#include <string>

class CinRedirect
{
public:
    CinRedirect()
    {
        saved_cin_buf = std::cin.rdbuf();
        std::cin.rdbuf(new_stream.rdbuf());
    }

    ~CinRedirect()
    {
        std::cin.rdbuf(saved_cin_buf);
    }

    std::stringstream& stream()
    {
        return new_stream;
    }

private:
    std::stringstream new_stream;
    std::streambuf* saved_cin_buf;
};

class CoutRedirect
{
public:
    CoutRedirect()
    {
        saved_cout_buf = std::cout.rdbuf();
        std::cout.rdbuf(ss.rdbuf());
    }

    ~CoutRedirect()
    {
        std::cout.rdbuf(saved_cout_buf);
    }

    std::string str() const
    {
        return std::string{ss.str()};
    }

    void disable() const
    {
        std::cout.rdbuf(saved_cout_buf);
    }

    void enable() const
    {
        std::cout.rdbuf(ss.rdbuf());
    }

private:
    std::streambuf* saved_cout_buf;
    std::stringstream ss;
};

#endif // PROJECT_ADVENTURE_TEST_TEST_UTILS_H

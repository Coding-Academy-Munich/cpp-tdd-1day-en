// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#ifndef COMPLETED_SHARED_MEMORY_UTILS_H
#define COMPLETED_SHARED_MEMORY_UTILS_H

#include <iostream>
#include <sstream>
#include <string>

template <typename T>
std::string build_child_command(std::string_view program, const T& arg) {
    std::stringstream child_command;
    // Pass a second argument to the child process and ensure the resulting string
    // is null-terminated
    child_command << program << " " << arg << std::ends;
    return child_command.str();
}

template <typename T1, typename T2>
std::string build_child_command(std::string_view program, const T1& arg1, const T2& arg2) {
    std::stringstream child_command;
    child_command << program << " " << arg1 << " " << arg2 << std::ends;
    return child_command.str();
}

inline void print_header(std::string_view program) {
    std::stringstream title;
    title << "Running " << program;
    std::cout << title.str() << "\n" << std::string(title.str().length(), '=') << "\n\n";
}

#endif // COMPLETED_SHARED_MEMORY_UTILS_H

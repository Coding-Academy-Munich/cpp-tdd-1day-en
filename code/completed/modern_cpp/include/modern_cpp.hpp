#pragma once
#ifndef MODERN_CPP_HPP
#define MODERN_CPP_HPP

#include <algorithm>
#include <iostream>
#include <vector>

namespace mcpp {

void print_modern_cpp_info();

template <std::ranges::range R>
void print_range(const R& range)
{
    for (const auto& elt : range) {
        std::cout << elt << " ";
    }
    std::cout << "\n\n";
}

template <std::ranges::random_access_range R>
void print_sorted_range(R range)
{
    std::cout << "Sorted range:\n";
    std::ranges::sort(range);
    print_range(range);
}

} // namespace mcpp

#endif // MODERN_CPP_HPP

// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

void print(const std::vector<int>& v)
{
    for (auto i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> v(10);
    std::vector<int> w(20, -1);

    std::cout << "std::iota(v.begin(), v.end(), 0)\n";
    std::iota(v.begin(), v.end(), 0);
    print(v);

    std::cout << "std::ranges::reverse(v)\n";
    std::ranges::reverse(v);
    print(v);

    std::cout << "std::ranges::sort(v)\n";
    std::ranges::sort(v);
    print(v);

    std::cout << "std::ranges::sort(v, std::greater())\n";
    std::ranges::sort(v, std::greater());
    print(v);

    std::cout << "std::ranges::copy(v, w.begin())\n";
    std::ranges::copy(v, w.begin());
    print(w);

    std::cout << "std::ranges::fill(w, 0)\n";
    std::ranges::fill(w, 0);
    print(w);

    std::cout << "std::ranges::copy(v, w.begin())\n";
    std::ranges::copy(v, w.begin() + 1);
    print(w);

    std::cout << "std::ranges::generate(v, []() { return rand() % 10; })\n";
    std::ranges::generate(v, []() { return rand() % 10; }); // NOLINT(*-msc50-cpp)
    print(v);

    std::cout << "std::ranges::copy_backward(v, w.end())\n";
    std::ranges::copy_backward(v, w.end());
    print(w);

    return 0;
}

#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
void print_address(const std::string& prefix, T obj)
{
    std::cout << prefix << " Ox" << std::hex
              << reinterpret_cast<std::uintptr_t>(obj) << std::endl;
}

void print_content_addresses(const std::string& name, const std::vector<int>& v);

template <typename T1, typename T2>
void print_dist(const std::string& prefix, T1 obj1, T2 obj2)
{
    std::cout << prefix << std::dec
              << reinterpret_cast<std::uintptr_t>(obj2) - reinterpret_cast<std::uintptr_t>(obj1)
              << std::endl;
}

void print_memory_layout();

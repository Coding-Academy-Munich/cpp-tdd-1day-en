#include <string>

#include "modern_cpp.hpp"

using namespace std::string_literals;

int main()
{
    mcpp::print_modern_cpp_info();
    mcpp::print_sorted_range(std::vector({3, 1, 5, 4, 2, 0}));
    mcpp::print_sorted_range("the quick brown fox jumps over the lazy dog"s);
}

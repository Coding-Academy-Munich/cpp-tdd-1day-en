// ReSharper disable CppClangTidyCppcoreguidelinesProBoundsArrayToPointerDecay
// ReSharper disable CppClangTidyCppcoreguidelinesAvoidCArrays
#include "pointers.hpp"

#include <iostream>

#include "utils.hpp"

// Note: Build this in release configuration to see some interesting effects.

namespace pointers {

struct Eq
{
    long arr[1]{};
    long val{};
};

void show_pointer_operations()
{
    // Three ways to initialize valid pointers:
    int i{0};
    int* pi{&i}; // Points to a valid address
    std::cout << "Address of i:           " << address_of(pi) << "\n";

    int ia[1];
    int* pia_end = std::end(ia); // Points to one past the end of an object
    std::cout << "Address of ia:          " << address_of(ia) << "\n";
    std::cout << "Address of end(ia):     " << address_of(pia_end) << "\n";

    //int** ppia_end{&pia_end}; // Points to another pointer
    //std::cout << "Address of ppia_end:    " << address_of(ppia_end) << "\n";

    [[maybe_unused]] int* p_null{nullptr}; // Valid, but may not be dereferenced.

    Eq eq{};
    long* parr{eq.arr};
    long* parr_end{std::end(eq.arr)};
    long* pval{&eq.val};
    std::cout << "Address of eq.arr:      " << address_of(parr) << "\n";
    std::cout << "Address of end(eq.arr): " << address_of(parr_end) << "\n";
    std::cout << "Address of eq.val:      " << address_of(pval) << "\n";

}

} // namespace pointers

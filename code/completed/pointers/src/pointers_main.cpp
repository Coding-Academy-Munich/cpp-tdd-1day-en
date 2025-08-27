// ReSharper disable CppClangTidyCppcoreguidelinesProBoundsArrayToPointerDecay
// ReSharper disable CppClangTidyCppcoreguidelinesAvoidCArrays
#include <iostream>
#include <sstream>

#include "array_dangers.hpp"
#include "pointers.hpp"
#include "shapes.hpp"

using namespace pointers;
using namespace std::ranges;

int main() // NOLINT(bugprone-exception-escape)
{
    try {
        show_pointer_operations();

        std::cout << "\n\n" << std::string(72, '*') << "\n\n";
        pointers::show_bad_array_signatures();

        std::cout << "\n\n" << std::string(72, '*') << "\n\n";
        pointers::show_bad_array_access();

        // Bang!
        //const Circle circles[5]{
        //    {1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, {7.0, 8.0}, {9.0, 0.0}};
        //draw_many_shapes(circles, 5);
    }
    catch (...) {
        std::cerr << "Oops...\n";
    }
}

#include "modern_cpp.hpp"

#include <iostream>

#include "gsl/zstring"

namespace mcpp {

void print_modern_cpp_info()
{
    gsl::czstring project_name = "modern_cpp";
    gsl::czstring project_namespace = "mcpp";
    std::cout << "Subproject Info\n\n";
    std::cout << "  name:      " << project_name << "\n";
    std::cout << "  namespace: " << project_namespace << "\n\n";
}

} // namespace mcpp

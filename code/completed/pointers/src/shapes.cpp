#include "shapes.hpp"

#include <iostream>

namespace pointers {

void Circle::draw() const
{
    std::cout.precision(1);
    std::cout << "Drawing Circle at " << x() << ", " << y() << ".\n";    
}

} // namespace pointers

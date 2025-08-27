#define PRINT_MEMORY_LAYOUT 0

#if PRINT_MEMORY_LAYOUT
#include "print_memory_layout.hpp"
#endif
#include "polymorphic_array.hpp"

int main() {
#if PRINT_MEMORY_LAYOUT
    print_memory_layout();
#endif
    print_polymorphic_array_examples();
}

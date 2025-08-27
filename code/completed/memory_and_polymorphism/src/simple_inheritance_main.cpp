#include <iostream>

#define DELETE_OPERATORS_FOR_BASE 0 // NOLINT(cppcoreguidelines-macro-usage)

#include "simple_inheritance.hpp"

using namespace si;

void print_header(const std::string& call)
{
    std::cout << std::string(72, '=') << "\n";
    std::cout << std::setw(pad) << call + ":"s;
}

void print_header_with_operation(const std::string& op, const std::string& call)
{
    std::cout << std::string(72, '=') << "\n";
    std::cout << op << "\n";
    std::cout << std::setw(pad) << call + ":"s;
}

int main()  // NOLINT(bugprone-exception-escape)
{
    std::cout << std::left;
    print_header("base.get_sum()");
    // Since Base is not an abstract type, we can manipulate Base objects by
    // value. (However this may be dangerous, see below.)
    Base base{2, 3, 5};
    std::cout << base.get_sum() << "\n";
    print_by_value("base", base);
    print_by_reference("base", base);

    print_header("derived.get_sum(), derived.get_product()");
    // Similarly, if we know that an object is of type Derived, we can work with
    // values.
    const Derived derived{2, 3, 5};
    std::cout << derived.get_sum() << ", " << derived.get_product() << "\n";
    print_by_value("derived", derived);
    print_by_reference("derived", derived);

    print_header("base_pointer->get_sum()");
    // The usual way to work with polymorphic types, however is through pointers
    // or references.
    const Base* base_pointer{&base};
    std::cout << base_pointer->get_sum() << "\n";
    // We can pass polymorphic types by value, however this is not a good idea!
    print_by_value("*base_pointer", *base_pointer);
    print_by_reference("*base_pointer", *base_pointer);

    print_header_with_operation(
        "Assigning base_pointer = &derived", "base_pointer->get_sum()");
    // Here we manipulate a derived object through a pointer to its base class.
    // This is perfectly valid and the main way how we deal with object
    // hierarchies in programs. 
    base_pointer = &derived;
    // Note that we are dealing with stack-allocated objects here, so we don't
    // have to delete any memory In real code we would likely have leaked memory
    // if we don't call delete here. But how can we know that we need to call
    // delete if we just see a pointer? (We can't without further knowledge.
    // Therefore, follow the core guidelines)

    std::cout << base_pointer->get_sum() << "\n";
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // But if we try to pass such a pointer by value, things go badly wrong! The
    // function call slices and turns the derived object into a base object
    print_by_value("*base_pointer", *base_pointer);
    print_by_reference("*base_pointer", *base_pointer);

    print_header_with_operation("Assigning base = derived", "base.get_sum()");
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // Similarly, if we assign a derived object to a variable of base type (as
    // opposed to a reference or a pointer)!
    base = derived;
    std::cout << base.get_sum() << "\n";
    std::cout << std::setw(pad) << "(&base)->get_sum() after assignment:";
    std::cout << (&base)->get_sum() << "\n";
    print_by_value("base", base);
    print_by_reference("base", base);
}

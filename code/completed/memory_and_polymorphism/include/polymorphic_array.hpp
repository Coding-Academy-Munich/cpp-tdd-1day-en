// ReSharper disable CppClangTidyCppcoreguidelinesProBoundsPointerArithmetic
// ReSharper disable CppClangTidyCppcoreguidelinesAvoidCArrays
#pragma once

#include <array>
#include <gsl/gsl>
#include <iostream>
#include <memory>
#include <span>
#include <typeinfo>
#include <vector>

struct MyBase
{
    explicit MyBase(int x) : x{x} {}

    int x;

    MyBase& inc()
    {
        x += 1;
        return *this;
    }
};

struct MyDerived : public MyBase
{
    MyDerived(int x, int y) : MyBase{x}, y{y} {}
    int y;
};

inline void print_array(gsl::czstring prefix, const MyBase arr[], std::size_t len)
{
    std::cout << "MyBase[] for " << prefix << ": " << typeid(arr).name() << "\n";
    for (std::size_t i = 0; i < len; ++i) {
        std::cout << arr[i].x << "\n";
    }
}

inline void
print_array_via_pointer(gsl::czstring prefix, const MyBase* arr, std::size_t len)
{
    std::cout << "MyBase* for " << prefix << ": " << typeid(arr).name() << "\n";
    for (std::size_t i = 0; i < len; ++i) {
        std::cout << arr[i].x << "\n";
    }
}

template <typename T>
void print_std_array(std::array<T, 3> arr)
{
    std::cout << "std::array<T>: " << typeid(arr).name() << "\n";
    for (const T& elt : arr) {
        std::cout << elt.x << "\n";
    }
}

template <typename T, std::size_t n>
void print_std_array_of_pointer(gsl::czstring prefix, const std::array<T, n>& arr)
{
    std::cout << "std::array<" << prefix << ", n>: " << typeid(arr).name() << "\n";
    for (const T& elt : arr) {
        std::cout << elt->x << "\n";
    }
}

inline void print_contents_of_base_array()
{
    const MyBase arr[]{MyBase{1}, MyBase{2}, MyBase{3}};
    print_array("MyBase[]", arr, 3);
    print_array_via_pointer("MyBase[]", arr, 3);
}

inline void print_contents_of_derived_array()
{
    const MyDerived arr[]{MyDerived{1, 10}, MyDerived{2, 20}, MyDerived{3, 30}};
    print_array("MyDerived[]", arr, 3);
    print_array_via_pointer("MyDerived[]", arr, 3);
}

inline void print_contents_of_base_std_array()
{
    const std::array<MyBase, 3> arr{MyBase{1}, MyBase{2}, MyBase{3}};
    print_std_array(arr);
}

inline void print_contents_of_derived_std_array()
{
    const std::array<MyDerived, 3> arr{
        MyDerived{1, 10}, MyDerived{2, 20}, MyDerived{3, 30}};
    print_std_array(arr);
}

inline void print_contents_of_base_std_array_of_pointer()
{
    const std::array<std::unique_ptr<MyBase>, 3> arr{
        std::make_unique<MyBase>(1), std::make_unique<MyBase>(2),
        std::make_unique<MyBase>(3)};
    print_std_array_of_pointer("base", arr);
}

inline void print_contents_of_derived_std_array_of_pointer()
{
    const std::array<std::unique_ptr<MyDerived>, 3> arr{
        std::make_unique<MyDerived>(1, 10), std::make_unique<MyDerived>(2, 20),
        std::make_unique<MyDerived>(3, 30)};
    print_std_array_of_pointer("derived", arr);
}

inline void print_contents_of_mixed_std_array_of_pointer()
{
    const std::array<std::unique_ptr<MyBase>, 3> arr{
        std::make_unique<MyBase>(1), std::make_unique<MyDerived>(2, 20),
        std::make_unique<MyBase>(3)};
    print_std_array_of_pointer("mixed", arr);
}

inline void print_span_of_pointer(
    gsl::czstring prefix, const std::span<std::unique_ptr<MyBase>>& span)
{
    std::cout << "Span<std::unique_ptr<MyBase>> (" << prefix
              << "): " << typeid(span).name() << "\n";
    for (const std::unique_ptr<MyBase>& elt : span) {
        std::cout << elt->x << "\n";
    }
}

inline void print_polymorphic_array_examples()
{
    print_contents_of_base_array();
    print_contents_of_derived_array();
    print_contents_of_base_std_array();
    print_contents_of_derived_std_array();
    print_contents_of_base_std_array_of_pointer();
    print_contents_of_derived_std_array_of_pointer();
    print_contents_of_mixed_std_array_of_pointer();
}

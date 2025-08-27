// ReSharper disable CppClangTidyClangDiagnosticUndef
#pragma once
#ifndef SIMPLE_INHERITANCE_HPP
#define SIMPLE_INHERITANCE_HPP
#include <string>
#include <iomanip>

namespace si {

using namespace std::string_literals;

constexpr int pad{50};

struct Base
{
    Base(int x, int y, int z) : x{x}, y{y}, z{z} {}
#if DELETE_OPERATORS_FOR_BASE
    Base(const Base& other) = delete;
    Base(Base&& other) noexcept = delete;
    Base& operator=(const Base& other) = delete;
    Base& operator=(Base&& other) noexcept = delete;
#else
    // These should in most cases be "= delete" for base classes
    // See the assignment `base = derived` in the main file for reasons.
    Base(const Base& other) = default;
    Base(Base&& other) noexcept = default;
    Base& operator=(const Base& other) = default;
    Base& operator=(Base&& other) noexcept = default;
#endif
    virtual ~Base() = default;
    [[nodiscard]] virtual int get_sum() const { return x + y + z; }

protected:
    int x;
    int y;

private:
    int z;
};

struct Derived : public Base
{
    Derived(int x, int y, int z) : Base{x, y, z} {}
    [[nodiscard]] int get_sum() const override { return Base::get_sum() + 1; }
    [[nodiscard]] int get_product() const { return x * y; }
};

inline void print_by_value(const std::string& prefix, Base base)
{
    const std::string fun{"get_sum("s + prefix + ") via print_by_value: "s};
    std::cout << std::setw(pad) << fun;
    std::cout << base.get_sum() << "\n";
}

inline void print_by_reference(const std::string& prefix, const Base& base)
{
    const std::string fun{"get_sum("s + prefix + ") via print_by_reference: "s};
    std::cout << std::setw(pad) << fun;
    std::cout << base.get_sum() << "\n";
}

} // namespace si

#endif // SIMPLE_INHERITANCE_HPP
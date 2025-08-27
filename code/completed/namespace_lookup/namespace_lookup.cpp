// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include <iostream>

void foo(bool) { std::cout << "foo(bool)" << std::endl; }

namespace ns1 {
void foo(int) { std::cout << "foo(int)" << std::endl; }
void foo(double) { std::cout << "foo(double)" << std::endl; }
} // namespace ns1

namespace ns2 {
void foo(bool) { std::cout << "foo(bool)" << std::endl; }
} // namespace ns2

namespace ns3 {
struct Foo { };

void foo(const Foo&) { std::cout << "foo(Foo)" << std::endl; }
} // namespace ns3

int main()
{
    {
        std::cout << "Calling functions without using declaration:\n";

        foo(true);
        foo(1); // NOLINT(*-use-bool-literals)
        foo(1.0); // NOLINT(*-narrowing-conversions)
        foo(ns3::Foo {});
    }

    {
        std::cout << "Calling functions with using ns1::foo declaration:\n";

        using ns1::foo;

        foo(true);
        foo(1);
        foo(1.0);
        foo(ns3::Foo {});
    }

    {
        std::cout << "Calling functions with using ::foo and ns1::foo declarations:\n";

        using ::foo;
        using ns1::foo;

        foo(true);
        foo(1);
        foo(1.0);
        foo(ns3::Foo {});
    }

    {
        std::cout
            << "Calling functions with using ns1::foo and ns2::foo declarations:\n";

        using ns1::foo;
        using ns2::foo;

        foo(true);
        foo(1);
        foo(1.0);
        foo(ns3::Foo {});
    }
}
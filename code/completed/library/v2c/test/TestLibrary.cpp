// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Library.h"
#include "Utils.h"
#include <catch2/catch_test_macros.hpp>

using namespace library::v2c;

TEST_CASE("Library can be created", "[library]")
{
    SECTION("Without books and members")
    {
        Library library;
        REQUIRE(library.GetBooks().Empty());
        REQUIRE(library.GetMembers().Empty());
    }

    SECTION("When books and members are provided")
    {
        auto cppBookInfo {
            BookInfo::Create("978-3-16-148410-0", "The C++ Programming Language",
                std::vector<std::string> {"Bjarne Stroustrup"},
                "Addison-Wesley Professional", std::chrono::year {2013})};

        BookCatalog books;
        books.Add(std::make_unique<Book>(cppBookInfo));
        books.Add(std::make_unique<Book>(cppBookInfo));

        MemberCatalog members;
        members.Add(std::make_unique<Member>(2, std::make_unique<RegularMemberType>(),
            "Jane Doe", "123 Main Street", MakeYearMonthDay(1960, 2, 3)));
        members.Add(std::make_unique<Member>(1, std::make_unique<RegularMemberType>(),
            "John Doe", "123 Main Street", MakeYearMonthDay(1980, 7, 12)));

        Library library {std::move(books), std::move(members)};
        REQUIRE(library.GetBooks().Size() == 2);
        REQUIRE(library.GetMembers().Size() == 2);
    }
}

TEST_CASE("Library Catalog getters work", "[library]")
{
    SECTION("Book catalog")
    {
        Library library;
        const Library constLibrary;
        REQUIRE(library.GetBooks().Empty());
        REQUIRE(constLibrary.GetBooks().Empty());
    }

    SECTION("Member catalog")
    {
        Library library;
        const Library constLibrary;
        REQUIRE(library.GetMembers().Empty());
        REQUIRE(constLibrary.GetMembers().Empty());
    }
}

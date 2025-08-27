// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Book.h"
#include <catch2/catch_test_macros.hpp>

using namespace library::v2a;

TEST_CASE("Test BookInfo", "[book]")
{
    SECTION("Test operator==()")
    {
        auto cppBookInfo {
            BookInfo::Create("978-0134852485", "The C++ Programming Language",
                {"Bjarne Stroustrup"}, "Addison-Wesley", std::chrono::year {2020})};
        auto effectiveCppBookInfo {BookInfo::Create("978-0321334879", "Effective C++",
            {"Scott Meyers"}, "Addison-Wesley", std::chrono::year {2021}, 3)};
        auto effectiveCppBookInfo2 {BookInfo::Create("978-0321334879", "Effective C++",
            {"Scott Meyers"}, "Addison-Wesley", std::chrono::year {2021}, 3)};

        REQUIRE(cppBookInfo == cppBookInfo);
        REQUIRE(*cppBookInfo == *cppBookInfo);

        REQUIRE(effectiveCppBookInfo == effectiveCppBookInfo);
        REQUIRE(*effectiveCppBookInfo == *effectiveCppBookInfo);

        REQUIRE(effectiveCppBookInfo != effectiveCppBookInfo2);
        REQUIRE(*effectiveCppBookInfo == *effectiveCppBookInfo2);
    }

    SECTION("Test operator=!()")
    {
        auto bookInfo {BookInfo::Create("isbn", "title", {"author1", "author2"},
            "publisher", std::chrono::year {2023})};
        auto bookIsbn {BookInfo::Create("other-isbn", "title", {"author1", "author2"},
            "publisher", std::chrono::year {2023})};
        auto bookAuthors {BookInfo::Create(
            "isbn", "title", {"author3"}, "publisher", std::chrono::year {2023})};
        auto bookPublisher {BookInfo::Create("isbn", "title", {"author1", "author2"},
            "other-publisher", std::chrono::year {2023})};
        auto bookPubYear {BookInfo::Create("isbn", "title", {"author1", "author2"},
            "publisher", std::chrono::year {2024})};
        auto bookEdition {BookInfo::Create("isbn", "title", {"author1", "author2"},
            "publisher", std::chrono::year {2023}, 2)};

        REQUIRE(*bookInfo != *bookIsbn);
        REQUIRE(*bookInfo != *bookAuthors);
        REQUIRE(*bookInfo != *bookPublisher);
        REQUIRE(*bookInfo != *bookPubYear);
        REQUIRE(*bookInfo != *bookEdition);
    }

    SECTION("Test operator<<()")
    {
        auto bookInfo {BookInfo::Create("1234", "My Book", {"Joe Random", "Jane Doe"},
            "Troy Inc.", std::chrono::year {2023})};
        std::ostringstream os;
        os << *bookInfo;
        REQUIRE(os.str()
            == "BookInfo{isbn: 1234, title: My Book, authors: [Joe Random, Jane Doe], "
               "publisher: Troy Inc., year: 2023, edition: 1}");
    }

    SECTION("Test HasAuthor()")
    {
        auto bookInfo {BookInfo::Create("1234", "My Book", {"Joe Random", "Jane Doe"},
            "Troy Inc.", std::chrono::year {2023})};
        REQUIRE(bookInfo->HasAuthor("Joe Random"));
        REQUIRE(bookInfo->HasAuthor("Jane Doe"));
        REQUIRE(!bookInfo->HasAuthor("John Doe"));
    }
}

TEST_CASE("Test Book", "[book]")
{
    auto cppBookInfo {BookInfo::Create("978-0134852485", "The C++ Programming Language",
        {"Bjarne Stroustrup"}, "Addison-Wesley", std::chrono::year {2020})};

    auto effectiveCppBookInfo {BookInfo::Create("978-0321334879", "Effective C++",
        {"Scott Meyers"}, "Addison-Wesley", std::chrono::year {2021}, 3)};

    auto cppBook1 {Book {1, cppBookInfo}};
    auto cppBook2 {Book {2, cppBookInfo}};
    auto effectiveCppBook {Book {3, effectiveCppBookInfo}};

    SECTION("Test ID creation")
    {
        Book cppBook3 {cppBookInfo};
        Book cppBook4 {cppBookInfo};
        REQUIRE(cppBook3.GetId() != cppBook4.GetId());
    }

    SECTION("Test operator==()")
    {
        REQUIRE(cppBook1 == cppBook1);
        REQUIRE(cppBook1 != cppBook2);
        REQUIRE(cppBook1 != effectiveCppBook);
    }

    SECTION("Test GetInfo()")
    {
        REQUIRE(cppBook1.GetInfo() == *cppBookInfo);
        REQUIRE(cppBook2.GetInfo() == *cppBookInfo);
        REQUIRE(effectiveCppBook.GetInfo() == *effectiveCppBookInfo);
    }

    SECTION("Test operator<<()")
    {
        std::ostringstream os;
        os << cppBook1;
        REQUIRE(os.str()
            == "Book{id: 1, isbn: 978-0134852485, title: The C++ Programming Language, "
               "authors: [Bjarne Stroustrup], publisher: Addison-Wesley, year: 2020, "
               "edition: 1}");
    }
}

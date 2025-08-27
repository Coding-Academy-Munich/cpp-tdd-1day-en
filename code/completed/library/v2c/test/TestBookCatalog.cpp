// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "BookCatalog.h"
#include "Utils.h"
#include <catch2/catch_test_macros.hpp>

using namespace library::v2c;

TEST_CASE("BookCatalog: basics", "[book-catalog]")
{
    SECTION("Test empty catalog")
    {
        BookCatalog catalog {};
        REQUIRE(catalog.Empty());
        REQUIRE(catalog.Size() == 0);
    }

    SECTION("Test non-empty catalog")
    {
        auto cppBookInfo {
            BookInfo::Create("978-3-16-148410-0", "The C++ Programming Language",
                std::vector<std::string> {"Bjarne Stroustrup"},
                "Addison-Wesley Professional", std::chrono::year {2013})};

        BookCatalog books;
        books.Add(*cppBookInfo);
        books.Add(*cppBookInfo);

        REQUIRE(!books.Empty());
        REQUIRE(books.Size() == 2);
    }
}

TEST_CASE("BookCatalog: members can be found", "[book-catalog]")
{
    auto bookAInfo {BookInfo::Create(
        "1234", "Book A", {"Author A"}, "Publisher A", std::chrono::year {2023})};
    auto bookBInfo {BookInfo::Create("2345", "Book B", {"Author B1", "Author B2"},
        "Publisher B", std::chrono::year {2023})};
    BookCatalog catalog;
    catalog.Add(*bookAInfo);
    catalog.Add(*bookBInfo);
    catalog.Add(*bookBInfo);

    SECTION("Find book by ISBN")
    {
        auto book {catalog.FindByIsbn("1234")};
        REQUIRE(book != nullptr);
        REQUIRE(book->GetIsbn() == "1234");
    }

    SECTION("Find non-existing book by ISBN")
    {
        auto book {catalog.FindByIsbn("5678")};
        REQUIRE(book == nullptr);
    }

    SECTION("Find book by title")
    {
        auto book {catalog.FindByTitle("Book B")};
        REQUIRE(book != nullptr);
        REQUIRE(book->GetTitle() == "Book B");
        REQUIRE(book->GetInfo() == *bookBInfo);
    }

    SECTION("Find book by unique author")
    {
        auto book {catalog.FindByAuthor("Author A")};
        REQUIRE(book != nullptr);
        REQUIRE(book->HasAuthor("Author A"));
        REQUIRE(book->GetInfo() == *bookAInfo);
    }

    SECTION("Find book by first author")
    {
        auto book {catalog.FindByAuthor("Author B1")};
        REQUIRE(book != nullptr);
        REQUIRE(book->HasAuthor("Author B1"));
        REQUIRE(book->GetInfo() == *bookBInfo);
    }

    SECTION("Find book by second author")
    {
        auto book {catalog.FindByAuthor("Author B2")};
        REQUIRE(book != nullptr);
        REQUIRE(book->HasAuthor("Author B2"));
        REQUIRE(book->GetInfo() == *bookBInfo);
    }

    SECTION("Find book by publisher")
    {
        auto book {catalog.FindByPublisher("Publisher B")};
        REQUIRE(book != nullptr);
        REQUIRE(book->GetPublisher() == "Publisher B");
        REQUIRE(book->GetInfo() == *bookBInfo);
    }

    SECTION("Find book by publication year")
    {
        auto book {catalog.FindByPublicationYear(std::chrono::year {2023})};
        REQUIRE(book != nullptr);
        REQUIRE(book->GetPublicationYear() == std::chrono::year {2023});
        // We don't know which book we get, so we can't compare the book info.
        // (There are multiple books with the same publication year.)
    }
}

TEST_CASE("BookCatalog: books can be removed", "[book-catalog]")
{
    auto bookAInfo {BookInfo::Create(
        "1234", "Book A", {"Author A"}, "Publisher A", std::chrono::year {2023})};
    auto bookBInfo {BookInfo::Create("2345", "Book B", {"Author B1", "Author B2"},
        "Publisher B", std::chrono::year {2023})};
    BookCatalog catalog;
    catalog.Add(*bookAInfo);
    catalog.Add(*bookBInfo);
    catalog.Add(*bookBInfo);

    SECTION("Remove book A")
    {
        REQUIRE(catalog.Size() == 3);
        auto bookA {catalog.FindByIsbn("1234")};
        REQUIRE(bookA != nullptr);

        catalog.Remove(*bookA);

        REQUIRE(catalog.Size() == 2);
        REQUIRE(catalog.FindByIsbn("1234") == nullptr);
    }

    SECTION("Remove for book B removes one instance of book B")
    {
        REQUIRE(catalog.Size() == 3);
        auto bookB {catalog.FindByIsbn("2345")};
        auto removedId {bookB->GetId()};
        REQUIRE(bookB != nullptr);

        catalog.Remove(*bookB);

        REQUIRE(catalog.Size() == 2);
        REQUIRE(catalog.FindByIsbn("2345") != nullptr);
        REQUIRE(catalog.FindByIsbn("2345")->GetId() != removedId);
    }

    SECTION("Removing a non-existing book does not change the library")
    {
        REQUIRE(catalog.Size() == 3);
        Book nonExistingBook {123, bookAInfo};

        catalog.Remove(nonExistingBook);

        REQUIRE(catalog.Size() == 3);
    }
}
// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Library.h"
#include "Utils.h"
#include <catch2/catch_test_macros.hpp>

using namespace library::v2b;

TEST_CASE("Library can be created", "[library]")
{
    SECTION("Without books and members")
    {
        Library library;
        REQUIRE(library.GetBooks().empty());
        REQUIRE(library.GetMembers().empty());
    }

    SECTION("When books and members are provided")
    {
        auto cppBookInfo {
            BookInfo::Create("978-3-16-148410-0", "The C++ Programming Language",
                std::vector<std::string> {"Bjarne Stroustrup"},
                "Addison-Wesley Professional", std::chrono::year {2013})};

        Catalog<Book> books;
        books.Add(std::make_unique<Book>(cppBookInfo));
        books.Add(std::make_unique<Book>(cppBookInfo));

        Catalog<Member> members;
        members.Add(std::make_unique<Member>(2, std::make_unique<RegularMemberType>(),
            "Jane Doe", "123 Main Street", MakeYearMonthDay(1960, 2, 3)));
        members.Add(std::make_unique<Member>(1, std::make_unique<RegularMemberType>(),
            "John Doe", "123 Main Street", MakeYearMonthDay(1980, 7, 12)));

        Library library {std::move(books), std::move(members)};
        REQUIRE(library.GetBooks().size() == 2);
        REQUIRE(library.GetMembers().size() == 2);
    }
}

TEST_CASE("Books can be found", "[library]")
{
    auto bookAInfo {BookInfo::Create(
        "1234", "Book A", {"Author A"}, "Publisher A", std::chrono::year {2023})};
    auto bookBInfo {BookInfo::Create("2345", "Book B", {"Author B1", "Author B2"},
        "Publisher B", std::chrono::year {2023})};
    Library library;
    library.AddBook(*bookAInfo);
    library.AddBook(*bookBInfo);
    library.AddBook(*bookBInfo);

    SECTION("Find book by ISBN")
    {
        auto book {library.FindBookByIsbn("1234")};
        REQUIRE(book != nullptr);
        REQUIRE(book->GetIsbn() == "1234");
    }

    SECTION("Find non-existing book by ISBN")
    {
        auto book {library.FindBookByIsbn("5678")};
        REQUIRE(book == nullptr);
    }

    SECTION("Find book by title")
    {
        auto book {library.FindBookByTitle("Book B")};
        REQUIRE(book != nullptr);
        REQUIRE(book->GetTitle() == "Book B");
        REQUIRE(book->GetInfo() == *bookBInfo);
    }

    SECTION("Find book by unique author")
    {
        auto book {library.FindBookByAuthor("Author A")};
        REQUIRE(book != nullptr);
        REQUIRE(book->HasAuthor("Author A"));
        REQUIRE(book->GetInfo() == *bookAInfo);
    }

    SECTION("Find book by first author")
    {
        auto book {library.FindBookByAuthor("Author B1")};
        REQUIRE(book != nullptr);
        REQUIRE(book->HasAuthor("Author B1"));
        REQUIRE(book->GetInfo() == *bookBInfo);
    }

    SECTION("Find book by second author")
    {
        auto book {library.FindBookByAuthor("Author B2")};
        REQUIRE(book != nullptr);
        REQUIRE(book->HasAuthor("Author B2"));
        REQUIRE(book->GetInfo() == *bookBInfo);
    }

    SECTION("Find book by publisher")
    {
        auto book {library.FindBookByPublisher("Publisher B")};
        REQUIRE(book != nullptr);
        REQUIRE(book->GetPublisher() == "Publisher B");
        REQUIRE(book->GetInfo() == *bookBInfo);
    }

    SECTION("Find book by publication year")
    {
        auto book {library.FindBookByPublicationYear(std::chrono::year {2023})};
        REQUIRE(book != nullptr);
        REQUIRE(book->GetPublicationYear() == std::chrono::year {2023});
        // We don't know which book we get, so we can't compare the book info.
        // (There are multiple books with the same publication year.)
    }
}

TEST_CASE("Members can be found", "[library]")
{
    Library library;
    library.AddMember(1, std::make_unique<RegularMemberType>(), "John Doe",
        "123 Main Street", MakeYearMonthDay(1980, 7, 12));
    library.AddMember(2, std::make_unique<RegularMemberType>(), "Jane Doe",
        "123 Main Street", MakeYearMonthDay(1960, 2, 3), "Software Engineer");

    SECTION("Find member by ID")
    {
        auto member {library.FindMemberById(1)};
        REQUIRE(member != nullptr);
        REQUIRE(member->GetId() == 1);
        REQUIRE(member->GetName() == "John Doe");
    }

    SECTION("Find non-existing member by ID")
    {
        auto member {library.FindMemberById(3333)};
        REQUIRE(member == nullptr);
    }

    SECTION("Find member by name")
    {
        auto member {library.FindMemberByName("Jane Doe")};
        REQUIRE(member != nullptr);
        REQUIRE(member->GetId() == 2);
        REQUIRE(member->GetName() == "Jane Doe");
    }

    SECTION("Find member by birthday")
    {
        auto member {library.FindMemberByBirthday(MakeYearMonthDay(1960, 2, 3))};
        REQUIRE(member != nullptr);
        REQUIRE(member->GetId() == 2);
        REQUIRE(member->GetName() == "Jane Doe");
    }

    SECTION("Find member by address")
    {
        auto member {library.FindMemberByAddress("123 Main Street")};
        REQUIRE(member != nullptr);
        REQUIRE(member->GetId() == 1);
        REQUIRE(member->GetName() == "John Doe");
    }

    SECTION("Find member by occupation")
    {
        auto member {library.FindMemberByOccupation("Software Engineer")};
        REQUIRE(member != nullptr);
        REQUIRE(member->GetId() == 2);
        REQUIRE(member->GetName() == "Jane Doe");
    }
}

TEST_CASE("Books can be removed")
{
    auto bookAInfo {BookInfo::Create(
        "1234", "Book A", {"Author A"}, "Publisher A", std::chrono::year {2023})};
    auto bookBInfo {BookInfo::Create("2345", "Book B", {"Author B1", "Author B2"},
        "Publisher B", std::chrono::year {2023})};
    Library library;
    library.AddBook(*bookAInfo);
    library.AddBook(*bookBInfo);
    library.AddBook(*bookBInfo);

    SECTION("Remove book A")
    {
        REQUIRE(library.GetBooks().size() == 3);
        auto bookA {library.FindBookByIsbn("1234")};
        REQUIRE(bookA != nullptr);

        library.RemoveBook(*bookA);

        REQUIRE(library.GetBooks().size() == 2);
        REQUIRE(library.FindBookByIsbn("1234") == nullptr);
    }

    SECTION("Remove for book B removes one instance of book B")
    {
        REQUIRE(library.GetBooks().size() == 3);
        auto bookB {library.FindBookByIsbn("2345")};
        auto removedId {bookB->GetId()};
        REQUIRE(bookB != nullptr);

        library.RemoveBook(*bookB);

        REQUIRE(library.GetBooks().size() == 2);
        REQUIRE(library.FindBookByIsbn("2345") != nullptr);
        REQUIRE(library.FindBookByIsbn("2345")->GetId() != removedId);
    }

    SECTION("Removing a non-existing book does not change the library")
    {
        REQUIRE(library.GetBooks().size() == 3);
        Book nonExistingBook {123, bookAInfo};

        library.RemoveBook(nonExistingBook);

        REQUIRE(library.GetBooks().size() == 3);
    }
}
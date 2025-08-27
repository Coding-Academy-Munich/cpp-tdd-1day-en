// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_LIBRARY_V2A_LIB_LIBRARY_H
#define COMPLETED_LIBRARY_V2A_LIB_LIBRARY_H

#include "Book.h"
#include "Member.h"
#include <functional>
#include <vector>

namespace library::v2a {

class Library {
public:
    using BookVector = std::vector<std::unique_ptr<Book>>;
    using MemberVector = std::vector<std::unique_ptr<Member>>;

    explicit Library(BookVector books = {}, MemberVector members = {});

    [[nodiscard]] const BookVector& GetBooks() const { return books; }
    [[nodiscard]] BookVector& GetBooks() { return books; }
    [[nodiscard]] const MemberVector& GetMembers() const { return members; }
    [[nodiscard]] MemberVector& GetMembers() { return members; }

    void AddBook(BookInfo& info);
    void AddBook(std::unique_ptr<Book> book);
    void RemoveBook(const Book& book)
    {
        const auto& iterator
            = std::ranges::find_if(books, [book](const auto& b) { return *b == book; });
        if (iterator != books.end()) {
            books.erase(iterator);
        }
    }

    [[nodiscard]] Book* FindBook(const std::function<bool(const Book&)>& predicate);
    [[nodiscard]] Book* FindBookById(unsigned int id)
    {
        return FindBook([&id](const Book& book) { return book.GetId() == id; });
    }
    [[nodiscard]] Book* FindBookByIsbn(const std::string& isbn);
    [[nodiscard]] Book* FindBookByTitle(const std::string& title)
    {
        return FindBook(
            [&title](const Book& book) { return book.GetTitle() == title; });
    }
    [[nodiscard]] Book* FindBookByAuthor(const std::string& author)
    {
        return FindBook([&author](const Book& book) { return book.HasAuthor(author); });
    }
    [[nodiscard]] Book* FindBookByPublisher(const std::string& publisher)
    {
        return FindBook([&publisher](const Book& book) {
            return book.GetPublisher() == publisher;
        });
    }
    [[nodiscard]] Book* FindBookByPublicationYear(const std::chrono::year& year)
    {
        return FindBook(
            [&year](const Book& book) { return book.GetPublicationYear() == year; });
    }

    void AddMember(unsigned int id, std::unique_ptr<MemberType> type, std::string name,
        std::string address, std::chrono::year_month_day birthday,
        std::optional<std::string> occupation = {});
    void AddMember(std::unique_ptr<Member> member);

    [[nodiscard]] Member* FindMember(
        const std::function<bool(const Member&)>& predicate);

    [[nodiscard]] Member* FindMemberById(unsigned int id)
    {
        return FindMember([&id](const Member& member) { return member.GetId() == id; });
    }
    [[nodiscard]] Member* FindMemberByName(const std::string& name)
    {
        return FindMember(
            [&name](const Member& member) { return member.GetName() == name; });
    }
    [[nodiscard]] Member* FindMemberByAddress(const std::string& address)
    {
        return FindMember([&address](const Member& member) {
            return member.GetAddress() == address;
        });
    }
    [[nodiscard]] Member* FindMemberByBirthday(
        const std::chrono::year_month_day& birthday)
    {
        return FindMember([&birthday](const Member& member) {
            return member.GetBirthday() == birthday;
        });
    }
    [[nodiscard]] Member* FindMemberByOccupation(const std::string& occupation)
    {
        return FindMember([&occupation](const Member& member) {
            return member.GetOccupation() == occupation;
        });
    }

private:
    BookVector books;
    MemberVector members;
};

} // namespace library::v2a

#endif // COMPLETED_LIBRARY_V2A_LIB_LIBRARY_H

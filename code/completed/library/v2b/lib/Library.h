// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_LIBRARY_V2B_LIB_LIBRARY_H
#define COMPLETED_LIBRARY_V2B_LIB_LIBRARY_H

#include "Book.h"
#include "Catalog.h"
#include "Member.h"
#include <functional>
#include <vector>

namespace library::v2b {

class Library {
public:
    using BookVector = Catalog<Book>::ContainerType;
    using MemberVector = Catalog<Member>::ContainerType;

    explicit Library(Catalog<Book> books = {}, Catalog<Member> members = {});

    [[nodiscard]] const BookVector& GetBooks() const { return books.GetValues(); }
    [[nodiscard]] BookVector& GetBooks() { return books.GetValues(); }

    [[nodiscard]] const MemberVector& GetMembers() const { return members.GetValues(); }
    [[nodiscard]] MemberVector& GetMembers() { return members.GetValues(); }

    void AddBook(BookInfo& info);
    void AddBook(std::unique_ptr<Book> book);
    void RemoveBook(const Book& book) { return books.Remove(book); }

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
    Catalog<Book> books;
    Catalog<Member> members;
};

} // namespace library::v2b

#endif // COMPLETED_LIBRARY_V2B_LIB_LIBRARY_H

// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Library.h"

namespace library::v2b {

Library::Library(Catalog<Book> books, Catalog<Member> members)
    : books {std::move(books)}
    , members {std::move(members)}
{
}

void Library::AddBook(BookInfo& info)
{
    books.Add(std::make_unique<Book>(info.shared_from_this()));
}

void Library::AddBook(std::unique_ptr<Book> book) { books.Add(std::move(book)); }

Book* Library::FindBook(const std::function<bool(const Book&)>& predicate)
{
    return books.Find(predicate);
}

Book* Library::FindBookByIsbn(const std::string& isbn)
{
    return FindBook([&isbn](const Book& book) { return book.GetIsbn() == isbn; });
}

void Library::AddMember(std::unique_ptr<Member> member)
{
    members.Add(std::move(member));
}

void Library::AddMember(unsigned int id, std::unique_ptr<MemberType> type,
    std::string name, std::string address, std::chrono::year_month_day birthday,
    std::optional<std::string> occupation)
{
    members.Add(std::make_unique<Member>(id, std::move(type), std::move(name),
        std::move(address), birthday, std::move(occupation)));
}

Member* Library::FindMember(const std::function<bool(const Member&)>& predicate)
{
    return members.Find(predicate);
}

} // namespace library::v2b
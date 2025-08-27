// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Library.h"

namespace library::v2a {

Library::Library(std::vector<std::unique_ptr<Book>> books,
    std::vector<std::unique_ptr<Member>> members)
    : books {std::move(books)}
    , members {std::move(members)}
{
}

void Library::AddBook(BookInfo& info)
{
    books.push_back(std::make_unique<Book>(info.shared_from_this()));
}

void Library::AddBook(std::unique_ptr<Book> book) { books.push_back(std::move(book)); }

Book* Library::FindBook(const std::function<bool(const Book&)>& predicate)
{
    for (auto& book : books) {
        if (predicate(*book)) {
            return book.get();
        }
    }
    return nullptr;
}

Book* Library::FindBookByIsbn(const std::string& isbn)
{
    return FindBook([&isbn](const Book& book) { return book.GetIsbn() == isbn; });
}

void Library::AddMember(std::unique_ptr<Member> member)
{
    members.push_back(std::move(member));
}

void Library::AddMember(unsigned int id, std::unique_ptr<MemberType> type,
    std::string name, std::string address, std::chrono::year_month_day birthday,
    std::optional<std::string> occupation)
{
    members.push_back(std::make_unique<Member>(id, std::move(type), std::move(name),
        std::move(address), birthday, std::move(occupation)));
}

Member* Library::FindMember(const std::function<bool(const Member&)>& predicate)
{
    for (auto& member : members) {
        if (predicate(*member)) {
            return member.get();
        }
    }
    return nullptr;
}

} // namespace library::v2a
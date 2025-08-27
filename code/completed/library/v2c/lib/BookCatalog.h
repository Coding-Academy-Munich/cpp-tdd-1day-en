// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_LIBRARY_V2C_LIB_BOOKCATALOG_H
#define COMPLETED_LIBRARY_V2C_LIB_BOOKCATALOG_H

#include "Book.h"
#include "Catalog.h"

namespace library::v2c {

class BookCatalog : public Catalog<Book> {
public:
    using Catalog<Book>::Add;
    void Add(BookInfo& info);

    [[nodiscard]] Book* FindById(unsigned int id)
    {
        return Find([&id](const Book& book) { return book.GetId() == id; });
    }
    [[nodiscard]] Book* FindByIsbn(const std::string& isbn)
    {
        return Find([&isbn](const Book& book) { return book.GetIsbn() == isbn; });
    }
    [[nodiscard]] Book* FindByTitle(const std::string& title)
    {
        return Find([&title](const Book& book) { return book.GetTitle() == title; });
    }
    [[nodiscard]] Book* FindByAuthor(const std::string& author)
    {
        return Find([&author](const Book& book) { return book.HasAuthor(author); });
    }
    [[nodiscard]] Book* FindByPublisher(const std::string& publisher)
    {
        return Find([&publisher](
                        const Book& book) { return book.GetPublisher() == publisher; });
    }
    [[nodiscard]] Book* FindByPublicationYear(const std::chrono::year& year)
    {
        return Find(
            [&year](const Book& book) { return book.GetPublicationYear() == year; });
    }
};

} // namespace library::v2c

#endif // COMPLETED_LIBRARY_V2C_LIB_BOOKCATALOG_H

// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_LIBRARY_V1_LIB_BOOK_H
#define COMPLETED_LIBRARY_V1_LIB_BOOK_H

#include "BookData.h"
#include <chrono>
#include <memory>
#include <ostream>
#include <string>

namespace library::v1 {

class BookInfo {
public:
    static std::shared_ptr<BookInfo> Create(const std::string& isbn,
        const std::string& title, const std::vector<std::string>& authors,
        const std::string& publisher, std::chrono::year publicationYear,
        unsigned int edition = 1);

    bool operator==(const BookInfo& rhs) const;

    [[nodiscard]] const std::string& GetTitle() const { return title; }
    [[nodiscard]] const std::vector<std::string>& GetAuthors() const { return authors; }
    [[nodiscard]] const std::string& GetIsbn() const { return isbn; }
    [[nodiscard]] const std::string& GetPublisher() const { return publisher; }
    [[nodiscard]] const std::chrono::year& GetPublicationYear() const
    {
        return publicationYear;
    }
    [[nodiscard]] unsigned int GetEdition() const { return edition; }

private:
    BookInfo(std::string isbn, std::string title,
        const std::vector<std::string>& authors, std::string publisher,
        const std::chrono::year& publicationYear, unsigned int edition);

    std::string isbn;
    std::string title;
    std::vector<std::string> authors;
    std::string publisher;
    std::chrono::year publicationYear;
    unsigned int edition;
};

std::ostream& operator<<(std::ostream& os, const BookInfo& info);

class Book {
public:
    Book(unsigned id, std::shared_ptr<BookInfo> info)
        : id(id)
        , info(std::move(info))
    {
    }

    explicit Book(std::shared_ptr<BookInfo> info)
        : info(std::move(info))
    {
    }

    bool operator==(const Book& rhs) const = default;

    [[nodiscard]] unsigned int GetId() const { return id; }
    [[nodiscard]] const std::string& GetTitle() const { return info->GetTitle(); }
    [[nodiscard]] const std::vector<std::string>& GetAuthors() const
    {
        return info->GetAuthors();
    }
    [[nodiscard]] const std::string& GetIsbn() const { return info->GetIsbn(); }
    [[nodiscard]] const std::string& GetPublisher() const
    {
        return info->GetPublisher();
    }
    [[nodiscard]] const std::chrono::year& GetPublicationYear() const
    {
        return info->GetPublicationYear();
    }
    [[nodiscard]] unsigned int GetEdition() const { return info->GetEdition(); }
    [[nodiscard]] BookInfo& GetInfo() const { return *info; }

private:
    static unsigned int nextId;
    unsigned int id {nextId++};
    std::shared_ptr<BookInfo> info;
};

std::ostream& operator<<(std::ostream& os, const Book& book);

} // namespace library::v1

#endif // COMPLETED_LIBRARY_V1_LIB_BOOK_H

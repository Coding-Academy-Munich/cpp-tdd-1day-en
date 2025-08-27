// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef REFACTORING_LMS_SK_LIB_CATALOG_H
#define REFACTORING_LMS_SK_LIB_CATALOG_H

#include "book.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace lms_sk
{
    // Catalog class - potential for moving features
    class Catalog
    {
    private:
        std::vector<std::unique_ptr<Book>> books;

    public:
        void addBook(std::unique_ptr<Book> book)
        {
            books.push_back(std::move(book));
        }

        // Complex search method - extract method opportunities
        std::vector<Book*> searchBooks(const std::string& query,
                                       const std::string& searchType)
        {
            std::vector<Book*> results;

            for (const auto& book : books)
            {
                bool matches = false;

                // Long conditional - replace with polymorphism opportunity
                if (searchType == "title")
                {
                    if (query.empty() || book->getTitle().find(query) != std::string::npos)
                    {
                        matches = true;
                    }
                }
                else if (searchType == "author")
                {
                    if (query.empty() || book->getAuthor().find(query) != std::string::npos)
                    {
                        matches = true;
                    }
                }
                else if (searchType == "isbn")
                {
                    if (query.empty() || book->getIsbn() == query)
                    {
                        matches = true;
                    }
                }
                else if (searchType == "genre")
                {
                    if (query.empty() || book->getGenre().find(query) != std::string::npos)
                    {
                        matches = true;
                    }
                }
                else if (searchType == "all")
                {
                    // Return all books regardless of query
                    matches = true;
                }

                if (matches)
                {
                    results.push_back(book.get());
                }
            }

            return results;
        }

        Book* findBookByIsbn(const std::string& isbn)
        {
            for (const auto& book : books)
            {
                if (book->getIsbn() == isbn)
                {
                    return book.get();
                }
            }
            return nullptr;
        }

        void displayAllBooks() const
        {
            for (const auto& book : books)
            {
                book->displayInfo();
                std::cout << "Available: " << (book->getAvailability() ? "Yes" : "No")
                          << std::endl;
                std::cout << "------------------------" << std::endl;
            }
        }

        size_t getBookCount() const
        {
            return books.size();
        }
    };
} // namespace lms_sk

#endif // REFACTORING_LMS_SK_LIB_CATALOG_H

// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef REFACTORING_LMS_SK_LIB_LIBRARY_H
#define REFACTORING_LMS_SK_LIB_LIBRARY_H

#include "book.h"
#include "catalog.h"
#include "loan.h"
#include "member.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace lms_sk
{
    // Main Library class - potential for extract class refactoring
    // NOTE: This class intentionally uses raw pointers for Member* to demonstrate
    // one case where manual memory management is still required for refactoring practice
    class Library
    {
    private:
        std::string libraryName;
        Catalog catalog;
        std::vector<Member*> members;
        // Raw pointers - the one case for manual memory management
        std::vector<std::unique_ptr<Loan>> loans;
        int nextLoanId;

    public:
        Library(const std::string& name) : libraryName(name), nextLoanId(1000)
        {
        }

        // Manual cleanup required for members - demonstrates need for refactoring
        ~Library()
        {
            for (Member* member : members)
            {
                delete member;
            }
        }

        // Copy constructor and assignment operator deleted to prevent issues
        Library(const Library&) = delete;
        Library& operator=(const Library&) = delete;

        void addBook(std::unique_ptr<Book> book)
        {
            catalog.addBook(std::move(book));
        }

        void addMember(Member* member)
        {
            members.push_back(member);
        }

        // Complex method with multiple responsibilities - extract method opportunities
        bool borrowBook(const std::string& memberId, const std::string& isbn)
        {
            // Find member
            Member* member = nullptr;
            for (Member* m : members)
            {
                if (m->getMemberId() == memberId)
                {
                    member = m;
                    break;
                }
            }

            if (member == nullptr)
            {
                std::cout << "Member not found!" << std::endl;
                return false;
            }

            // Find book
            Book* book = catalog.findBookByIsbn(isbn);
            if (book == nullptr)
            {
                std::cout << "Book not found!" << std::endl;
                return false;
            }

            if (!book->getAvailability())
            {
                std::cout << "Book is not available!" << std::endl;
                return false;
            }

            // Check if member has reached borrowing limit
            int currentBooks = 0;
            for (const auto& loan : loans)
            {
                if (loan->getMemberId() == memberId && !loan->getIsReturned())
                {
                    currentBooks++;
                }
            }

            if (currentBooks >= member->getMaxBooks())
            {
                std::cout << "Member has reached borrowing limit!" << std::endl;
                return false;
            }

            // Create loan
            std::string loanId = "L" + std::to_string(nextLoanId++);
            int loanDays = std::min(member->getMaxLoanDays(), book->getMaxLoanDays());
            auto loan = std::make_unique<Loan>(loanId, isbn, memberId, loanDays);
            loans.push_back(std::move(loan));

            book->setAvailability(false);
            std::cout << "Book borrowed successfully! Loan ID: " << loanId << std::endl;
            return true;
        }

        // Another complex method - extract method opportunities
        bool returnBook(const std::string& loanId)
        {
            Loan* loan = nullptr;
            for (const auto& l : loans)
            {
                if (l->getLoanId() == loanId)
                {
                    loan = l.get();
                    break;
                }
            }

            if (loan == nullptr)
            {
                std::cout << "Loan not found!" << std::endl;
                return false;
            }

            if (loan->getIsReturned())
            {
                std::cout << "Book already returned!" << std::endl;
                return false;
            }

            // Calculate late fee
            int daysLate = loan->getDaysLate();
            double lateFee = 0.0;

            if (daysLate > 0)
            {
                Book* book = catalog.findBookByIsbn(loan->getBookIsbn());
                Member* member = nullptr;
                for (Member* m : members)
                {
                    if (m->getMemberId() == loan->getMemberId())
                    {
                        member = m;
                        break;
                    }
                }

                if (book && member)
                {
                    lateFee = book->getLateFee(daysLate);
                    // Apply member discount
                    lateFee = lateFee * (1.0 - member->getDiscountRate());
                    loan->setLateFee(lateFee);
                }
            }

            loan->returnBook();

            // Make book available again
            Book* book = catalog.findBookByIsbn(loan->getBookIsbn());
            if (book)
            {
                book->setAvailability(true);
            }

            std::cout << "Book returned successfully!" << std::endl;
            if (lateFee > 0)
            {
                std::cout << "Late fee: $" << lateFee << std::endl;
            }

            return true;
        }

        void searchBooks(const std::string& query, const std::string& searchType)
        {
            std::vector<Book*> results = catalog.searchBooks(query, searchType);

            if (results.empty())
            {
                std::cout << "No books found matching your search." << std::endl;
            }
            else
            {
                std::cout << "Search results:" << std::endl;
                for (Book* book : results)
                {
                    book->displayInfo();
                    std::cout << "Available: " << (book->getAvailability() ? "Yes" : "No")
                              << std::endl;
                    std::cout << "------------------------" << std::endl;
                }
            }
        }

        void displayMemberLoans(const std::string& memberId)
        {
            std::cout << "Loans for member " << memberId << ":" << std::endl;

            for (const auto& loan : loans)
            {
                if (loan->getMemberId() == memberId)
                {
                    Book* book = catalog.findBookByIsbn(loan->getBookIsbn());
                    std::cout << "Loan ID: " << loan->getLoanId();
                    if (book)
                    {
                        std::cout << ", Book: " << book->getTitle();
                    }
                    std::cout << ", Status: "
                              << (loan->getIsReturned() ? "Returned" : "Active");
                    if (!loan->getIsReturned())
                    {
                        int daysLate = loan->getDaysLate();
                        if (daysLate > 0)
                        {
                            std::cout << " (Late by " << daysLate << " days)";
                        }
                    }
                    std::cout << std::endl;
                }
            }
        }

        void displayLibraryStats()
        {
            int totalBooks = catalog.getBookCount();
            int availableBooks = 0, borrowedBooks = 0;
            int totalMembers = members.size();
            int activeLoans = 0;

            // This could be extracted to a separate statistics class
            std::vector<Book*> allBooks = catalog.searchBooks("", "all");

            for (Book* book : allBooks)
            {
                if (book->getAvailability())
                {
                    availableBooks++;
                }
                else
                {
                    borrowedBooks++;
                }
            }

            for (const auto& loan : loans)
            {
                if (!loan->getIsReturned())
                {
                    activeLoans++;
                }
            }

            std::cout << "=== Library Statistics ===" << std::endl;
            std::cout << "Library: " << libraryName << std::endl;
            std::cout << "Total Books: " << totalBooks << std::endl;
            std::cout << "Available Books: " << availableBooks << std::endl;
            std::cout << "Borrowed Books: " << borrowedBooks << std::endl;
            std::cout << "Total Members: " << totalMembers << std::endl;
            std::cout << "Active Loans: " << activeLoans << std::endl;
        }
    };
} // namespace lms_sk

#endif // REFACTORING_LMS_SK_LIB_LIBRARY_H

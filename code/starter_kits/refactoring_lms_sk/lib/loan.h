// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef REFACTORING_LMS_SK_LIB_LOAN_H
#define REFACTORING_LMS_SK_LIB_LOAN_H

#include <ctime>
#include <string>

namespace lms_sk
{
    // Loan class - potential for data organization refactoring
    class Loan
    {
    private:
        std::string loanId;
        std::string bookIsbn;
        std::string memberId;
        std::time_t loanDate;
        std::time_t dueDate;
        std::time_t returnDate;
        bool isReturned;
        double lateFee;

    public:
        Loan(const std::string& loanId, const std::string& bookIsbn,
             const std::string& memberId, int loanDays) :
            loanId(loanId), bookIsbn(bookIsbn), memberId(memberId), isReturned(false),
            lateFee(0.0)
        {
            loanDate = std::time(nullptr);
            dueDate = loanDate + (loanDays * 24 * 60 * 60); // Convert days to seconds
            returnDate = 0;
        }

        // Getters - encapsulation opportunities
        std::string getLoanId() const
        {
            return loanId;
        }
        std::string getBookIsbn() const
        {
            return bookIsbn;
        }
        std::string getMemberId() const
        {
            return memberId;
        }
        std::time_t getLoanDate() const
        {
            return loanDate;
        }
        std::time_t getDueDate() const
        {
            return dueDate;
        }
        bool getIsReturned() const
        {
            return isReturned;
        }
        double getLateFee() const
        {
            return lateFee;
        }

        void returnBook()
        {
            returnDate = std::time(nullptr);
            isReturned = true;
        }

        void setLateFee(double fee)
        {
            lateFee = fee;
        }

        // Complex method - extract method opportunity
        int getDaysLate() const
        {
            if (!isReturned)
            {
                std::time_t currentTime = std::time(nullptr);
                if (currentTime > dueDate)
                {
                    return (currentTime - dueDate) / (24 * 60 * 60);
                }
            }
            else if (returnDate > dueDate)
            {
                return (returnDate - dueDate) / (24 * 60 * 60);
            }
            return 0;
        }
    };
} // namespace lms_sk

#endif // REFACTORING_LMS_SK_LIB_LOAN_H

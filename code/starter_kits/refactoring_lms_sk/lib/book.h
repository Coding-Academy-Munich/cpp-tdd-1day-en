// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef REFACTORING_LMS_SK_LIB_BOOK_H
#define REFACTORING_LMS_SK_LIB_BOOK_H

#include <iostream>
#include <string>

namespace lms_sk
{
    // Base Book class with inheritance opportunities
    class Book
    {
    protected:
        std::string isbn;
        std::string title;
        std::string author;
        std::string genre;
        bool isAvailable;

    public:
        Book(const std::string& isbn, const std::string& title, const std::string& author,
             const std::string& genre) :
            isbn(isbn), title(title), author(author), genre(genre), isAvailable(true)
        {
        }

        virtual ~Book() = default;

        // Getters with potential for encapsulation refactoring
        std::string getIsbn() const
        {
            return isbn;
        }
        std::string getTitle() const
        {
            return title;
        }
        std::string getAuthor() const
        {
            return author;
        }
        std::string getGenre() const
        {
            return genre;
        }
        bool getAvailability() const
        {
            return isAvailable;
        }

        void setAvailability(bool available)
        {
            isAvailable = available;
        }

        // Virtual method for polymorphism opportunities
        virtual double getLateFee(int daysLate) const
        {
            return daysLate * 0.50; // Magic number - refactoring opportunity
        }

        virtual int getMaxLoanDays() const
        {
            return 14; // Magic number - refactoring opportunity
        }

        virtual void displayInfo() const
        {
            std::cout << "Book: " << title << " by " << author << " (ISBN: " << isbn << ")"
                      << std::endl;
        }
    };

    // Derived classes for inheritance refactoring
    class PhysicalBook : public Book
    {
    private:
        std::string location; // Shelf location

    public:
        PhysicalBook(const std::string& isbn, const std::string& title,
                     const std::string& author, const std::string& genre,
                     const std::string& location) :
            Book(isbn, title, author, genre), location(location)
        {
        }

        std::string getLocation() const
        {
            return location;
        }

        double getLateFee(int daysLate) const override
        {
            return daysLate * 0.75; // Higher fee for physical books
        }

        void displayInfo() const override
        {
            Book::displayInfo();
            std::cout << "Location: " << location << " (Physical Book)" << std::endl;
        }
    };

    class EBook : public Book
    {
    private:
        std::string downloadUrl;
        int fileSizeMB;

    public:
        EBook(const std::string& isbn, const std::string& title, const std::string& author,
              const std::string& genre, const std::string& downloadUrl, int fileSizeMB) :
            Book(isbn, title, author, genre), downloadUrl(downloadUrl),
            fileSizeMB(fileSizeMB)
        {
        }

        std::string getDownloadUrl() const
        {
            return downloadUrl;
        }
        int getFileSizeMB() const
        {
            return fileSizeMB;
        }

        double getLateFee(int daysLate) const override
        {
            return daysLate * 0.25; // Lower fee for e-books
        }

        int getMaxLoanDays() const override
        {
            return 21; // Longer loan period for e-books
        }

        void displayInfo() const override
        {
            Book::displayInfo();
            std::cout << "File Size: " << fileSizeMB << "MB (E-Book)" << std::endl;
        }
    };

} // namespace lms_sk

#endif // REFACTORING_LMS_SK_LIB_BOOK_H

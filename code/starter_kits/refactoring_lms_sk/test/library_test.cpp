// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include "library.h"

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <streambuf>

using namespace lms_sk;

// Test utility class to capture cout output
class CoutCapture
{
private:
    std::stringstream buffer;
    std::streambuf* old;

public:
    CoutCapture() : old(std::cout.rdbuf(buffer.rdbuf()))
    {
    }

    ~CoutCapture()
    {
        std::cout.rdbuf(old);
    }

    std::string GetOutput() const
    {
        return buffer.str();
    }

    void clear()
    {
        buffer.str("");
        buffer.clear();
    }
};

// Test Fixtures
class LibraryTestFixture
{
protected:
    Library library;

public:
    LibraryTestFixture() : library("Test Library")
    {
        setupTestData();
    }

private:
    void setupTestData()
    {
        // Add test books
        library.addBook(
            std::make_unique<PhysicalBook>("978-0134685991", "Effective Modern C++",
                                           "Scott Meyers", "Programming", "A1-23"));
        library.addBook(std::make_unique<EBook>(
            "978-1449373320", "Designing Data-Intensive Applications", "Martin Kleppmann",
            "Technology", "https://library.com/ebooks/ddia", 15));
        library.addBook(std::make_unique<PhysicalBook>(
            "978-0132350884", "Clean Code", "Robert C. Martin", "Programming", "A2-10"));

        // Add test members
        library.addMember(new Member("M001", "John Doe", "john@email.com", "555-0101"));
        library.addMember(new StudentMember("M002", "Alice Smith", "alice@university.edu",
                                            "555-0102", "S12345", "Tech University"));
        library.addMember(new FacultyMember("M003", "Dr. Bob Johnson", "bob@university.edu",
                                            "555-0103", "Computer Science", "Professor"));
    }
};

// Book Class Tests
TEST_CASE("Book - Basic Properties", "[book]")
{
    PhysicalBook book("978-0134685991", "Effective Modern C++", "Scott Meyers",
                      "Programming", "A1-23");

    SECTION("Book has correct initial properties")
    {
        REQUIRE(book.getIsbn() == "978-0134685991");
        REQUIRE(book.getTitle() == "Effective Modern C++");
        REQUIRE(book.getAuthor() == "Scott Meyers");
        REQUIRE(book.getGenre() == "Programming");
        REQUIRE(book.getAvailability() == true);
        REQUIRE(book.getLocation() == "A1-23");
    }

    SECTION("Book availability can be changed")
    {
        book.setAvailability(false);
        REQUIRE(book.getAvailability() == false);

        book.setAvailability(true);
        REQUIRE(book.getAvailability() == true);
    }
}

TEST_CASE("Book - Polymorphic Behavior", "[book][polymorphism]")
{
    auto physicalBook = std::make_unique<PhysicalBook>(
        "978-0134685991", "Effective Modern C++", "Scott Meyers", "Programming", "A1-23");
    auto eBook =
        std::make_unique<EBook>("978-1449373320", "Design Patterns", "Gang of Four",
                                "Programming", "https://example.com/book", 20);

    SECTION("Physical books have higher late fees")
    {
        REQUIRE(physicalBook->getLateFee(5) == 5 * 0.75);
        REQUIRE(eBook->getLateFee(5) == 5 * 0.25);
    }

    SECTION("E-books have longer loan periods")
    {
        REQUIRE(physicalBook->getMaxLoanDays() == 14);
        REQUIRE(eBook->getMaxLoanDays() == 21);
    }
}

TEST_CASE("EBook - Specific Properties", "[ebook]")
{
    EBook ebook("978-1449373320", "Design Patterns", "Gang of Four", "Programming",
                "https://example.com/book", 20);

    REQUIRE(ebook.getDownloadUrl() == "https://example.com/book");
    REQUIRE(ebook.getFileSizeMB() == 20);
}

// Member Class Tests
TEST_CASE("Member - Basic Properties", "[member]")
{
    Member member("M001", "John Doe", "john@email.com", "555-0101");

    SECTION("Member has correct initial properties")
    {
        REQUIRE(member.getMemberId() == "M001");
        REQUIRE(member.getName() == "John Doe");
        REQUIRE(member.getEmail() == "john@email.com");
        REQUIRE(member.getPhone() == "555-0101");
    }

    SECTION("Regular member has default limits")
    {
        REQUIRE(member.getMaxBooks() == 3);
        REQUIRE(member.getMaxLoanDays() == 14);
        REQUIRE(member.getDiscountRate() == 0.0);
    }
}

TEST_CASE("Member - Polymorphic Behavior", "[member][polymorphism]")
{
    auto regularMember =
        std::make_unique<Member>("M001", "John Doe", "john@email.com", "555-0101");
    auto studentMember =
        std::make_unique<StudentMember>("M002", "Alice Smith", "alice@university.edu",
                                        "555-0102", "S12345", "Tech University");
    auto facultyMember =
        std::make_unique<FacultyMember>("M003", "Dr. Bob Johnson", "bob@university.edu",
                                        "555-0103", "Computer Science", "Professor");

    SECTION("Different member types have different book limits")
    {
        REQUIRE(regularMember->getMaxBooks() == 3);
        REQUIRE(studentMember->getMaxBooks() == 5);
        REQUIRE(facultyMember->getMaxBooks() == 10);
    }

    SECTION("Different member types have different loan periods")
    {
        REQUIRE(regularMember->getMaxLoanDays() == 14);
        REQUIRE(studentMember->getMaxLoanDays() == 21);
        REQUIRE(facultyMember->getMaxLoanDays() == 30);
    }

    SECTION("Different member types have different discount rates")
    {
        REQUIRE(regularMember->getDiscountRate() == 0.0);
        REQUIRE(studentMember->getDiscountRate() == 0.10);
        REQUIRE(facultyMember->getDiscountRate() == 0.20);
    }
}

// Loan Class Tests
TEST_CASE("Loan - Basic Functionality", "[loan]")
{
    Loan loan("L1001", "978-0134685991", "M001", 14);

    SECTION("Loan has correct initial properties")
    {
        REQUIRE(loan.getLoanId() == "L1001");
        REQUIRE(loan.getBookIsbn() == "978-0134685991");
        REQUIRE(loan.getMemberId() == "M001");
        REQUIRE(loan.getIsReturned() == false);
        REQUIRE(loan.getLateFee() == 0.0);
    }

    SECTION("Loan can be returned")
    {
        loan.returnBook();
        REQUIRE(loan.getIsReturned() == true);
    }

    SECTION("Late fee can be set")
    {
        loan.setLateFee(5.50);
        REQUIRE(loan.getLateFee() == 5.50);
    }

    SECTION("Days late calculation when not returned")
    {
        // Note: This test might be flaky due to time dependencies
        // In a real scenario, you'd inject a time provider for testing
        int daysLate = loan.getDaysLate();
        REQUIRE(daysLate >= 0);
    }
}

// Catalog Class Tests
TEST_CASE("Catalog - Book Management", "[catalog]")
{
    Catalog catalog;

    SECTION("Empty catalog has no books")
    {
        REQUIRE(catalog.getBookCount() == 0);
        REQUIRE(catalog.findBookByIsbn("978-0134685991") == nullptr);
    }

    SECTION("Books can be added to catalog")
    {
        catalog.addBook(
            std::make_unique<PhysicalBook>("978-0134685991", "Effective Modern C++",
                                           "Scott Meyers", "Programming", "A1-23"));

        REQUIRE(catalog.getBookCount() == 1);

        Book* found = catalog.findBookByIsbn("978-0134685991");
        REQUIRE(found != nullptr);
        REQUIRE(found->getTitle() == "Effective Modern C++");
    }

    SECTION("Search functionality works correctly")
    {
        catalog.addBook(
            std::make_unique<PhysicalBook>("978-0134685991", "Effective Modern C++",
                                           "Scott Meyers", "Programming", "A1-23"));
        catalog.addBook(
            std::make_unique<PhysicalBook>("978-0321563842", "The C++ Programming Language",
                                           "Bjarne Stroustrup", "Programming", "A1-24"));
        catalog.addBook(std::make_unique<PhysicalBook>(
            "978-0132350884", "Clean Code", "Robert C. Martin", "Programming", "A2-10"));

        auto titleResults = catalog.searchBooks("C++", "title");
        REQUIRE(titleResults.size() == 2);
        // "Effective Modern C++" and "The C++ Programming Language"

        auto authorResults = catalog.searchBooks("Martin", "author");
        REQUIRE(authorResults.size() == 1); // "Clean Code" by Robert C. Martin

        auto isbnResults = catalog.searchBooks("978-0134685991", "isbn");
        REQUIRE(isbnResults.size() == 1);

        auto genreResults = catalog.searchBooks("Programming", "genre");
        REQUIRE(genreResults.size() == 3);

        auto noResults = catalog.searchBooks("NonExistent", "title");
        REQUIRE(noResults.empty());
    }
}

// Library Class Tests
TEST_CASE_METHOD(LibraryTestFixture, "Library - Book Borrowing", "[library][borrowing]")
{
    SECTION("Valid book borrowing succeeds")
    {
        CoutCapture capture;
        bool result = library.borrowBook("M001", "978-0134685991");

        REQUIRE(result == true);
        std::string output = capture.GetOutput();
        REQUIRE(output.find("Book borrowed successfully") != std::string::npos);
        REQUIRE(output.find("L1000") != std::string::npos);
    }

    SECTION("Borrowing nonexistent member fails")
    {
        CoutCapture capture;
        bool result = library.borrowBook("M999", "978-0134685991");

        REQUIRE(result == false);
        std::string output = capture.GetOutput();
        REQUIRE(output.find("Member not found") != std::string::npos);
    }

    SECTION("Borrowing nonexistent book fails")
    {
        CoutCapture capture;
        bool result = library.borrowBook("M001", "978-9999999999");

        REQUIRE(result == false);
        std::string output = capture.GetOutput();
        REQUIRE(output.find("Book not found") != std::string::npos);
    }

    SECTION("Borrowing unavailable book fails")
    {
        // First borrow the book
        library.borrowBook("M001", "978-0134685991");

        // Try to borrow the same book again
        CoutCapture capture;
        bool result = library.borrowBook("M002", "978-0134685991");

        REQUIRE(result == false);
        std::string output = capture.GetOutput();
        REQUIRE(output.find("Book is not available") != std::string::npos);
    }

    SECTION("Borrowing limit enforcement works")
    {
        // Regular member can borrow up to 3 books
        REQUIRE(library.borrowBook("M001", "978-0134685991") == true);
        REQUIRE(library.borrowBook("M001", "978-1449373320") == true);
        REQUIRE(library.borrowBook("M001", "978-0132350884") == true);

        // Add another book to test limit
        library.addBook(
            std::make_unique<PhysicalBook>("978-0321563842", "The C++ Programming Language",
                                           "Bjarne Stroustrup", "Programming", "A1-24"));

        CoutCapture capture;
        bool result = library.borrowBook("M001", "978-0321563842");

        REQUIRE(result == false);
        std::string output = capture.GetOutput();
        REQUIRE(output.find("borrowing limit") != std::string::npos);
    }
}

TEST_CASE_METHOD(LibraryTestFixture, "Library - Book Returning", "[library][returning]")
{
    SECTION("Valid book return succeeds")
    {
        // First borrow a book
        library.borrowBook("M001", "978-0134685991");

        CoutCapture capture;
        bool result = library.returnBook("L1000");

        REQUIRE(result == true);
        std::string output = capture.GetOutput();
        REQUIRE(output.find("Book returned successfully") != std::string::npos);
    }

    SECTION("Returning nonexistent loan fails")
    {
        CoutCapture capture;
        bool result = library.returnBook("L9999");

        REQUIRE(result == false);
        std::string output = capture.GetOutput();
        REQUIRE(output.find("Loan not found") != std::string::npos);
    }

    SECTION("Returning already returned book fails")
    {
        // Borrow and return a book
        library.borrowBook("M001", "978-0134685991");
        library.returnBook("L1000");

        // Try to return again
        CoutCapture capture;
        bool result = library.returnBook("L1000");

        REQUIRE(result == false);
        std::string output = capture.GetOutput();
        REQUIRE(output.find("Book already returned") != std::string::npos);
    }

    SECTION("Book becomes available after return")
    {
        // Borrow a book (makes it unavailable)
        library.borrowBook("M001", "978-0134685991");

        // Return the book
        library.returnBook("L1000");

        // Should be able to borrow the same book again
        CoutCapture capture;
        bool result = library.borrowBook("M002", "978-0134685991");
        REQUIRE(result == true);
    }
}

TEST_CASE_METHOD(LibraryTestFixture, "Library - Search Functionality", "[library][search]")
{
    SECTION("Search displays results when books found")
    {
        CoutCapture capture;
        library.searchBooks("C++", "title");

        std::string output = capture.GetOutput();
        REQUIRE(output.find("Search results:") != std::string::npos);
        REQUIRE(output.find("Effective Modern C++") != std::string::npos);
    }

    SECTION("Search displays no results message when nothing found")
    {
        CoutCapture capture;
        library.searchBooks("NonExistent", "title");

        std::string output = capture.GetOutput();
        REQUIRE(output.find("No books found matching your search") != std::string::npos);
    }
}

TEST_CASE_METHOD(LibraryTestFixture, "Library - Member Loan Display", "[library][loans]")
{
    SECTION("Display loans for member with loans")
    {
        library.borrowBook("M001", "978-0134685991");
        library.borrowBook("M001", "978-1449373320");

        CoutCapture capture;
        library.displayMemberLoans("M001");

        std::string output = capture.GetOutput();
        REQUIRE(output.find("Loans for member M001") != std::string::npos);
        REQUIRE(output.find("L1000") != std::string::npos);
        REQUIRE(output.find("L1001") != std::string::npos);
        REQUIRE(output.find("Active") != std::string::npos);
    }

    SECTION("Display loans shows returned status")
    {
        library.borrowBook("M001", "978-0134685991");
        library.returnBook("L1000");

        CoutCapture capture;
        library.displayMemberLoans("M001");

        std::string output = capture.GetOutput();
        REQUIRE(output.find("Returned") != std::string::npos);
    }
}

TEST_CASE_METHOD(LibraryTestFixture, "Library - Statistics", "[library][stats]")
{
    SECTION("Library statistics are accurate")
    {
        CoutCapture capture;
        library.displayLibraryStats();

        std::string output = capture.GetOutput();
        REQUIRE(output.find("Test Library") != std::string::npos);
        REQUIRE(output.find("Total Books: 3") != std::string::npos);
        REQUIRE(output.find("Available Books: 3") != std::string::npos);
        REQUIRE(output.find("Borrowed Books: 0") != std::string::npos);
        REQUIRE(output.find("Total Members: 3") != std::string::npos);
        REQUIRE(output.find("Active Loans: 0") != std::string::npos);
    }

    SECTION("Statistics update after borrowing")
    {
        library.borrowBook("M001", "978-0134685991");
        library.borrowBook("M002", "978-1449373320");

        std::string output;
        {
            CoutCapture capture;
            library.displayLibraryStats();

            output = capture.GetOutput();
        }
        std::cout << "Output:\n" << output << std::endl; // For debugging purposes
        REQUIRE(output.find("Available Books: 1") != std::string::npos);
        REQUIRE(output.find("Borrowed Books: 2") != std::string::npos);
        REQUIRE(output.find("Active Loans: 2") != std::string::npos);
    }
}

// Integration Tests
TEST_CASE("Library - Complete Borrowing and Returning Workflow", "[library][integration]")
{
    Library library("Integration Test Library");

    // Setup
    library.addBook(std::make_unique<PhysicalBook>("978-0134685991", "Effective Modern C++",
                                                   "Scott Meyers", "Programming", "A1-23"));
    library.addMember(new StudentMember("M002", "Alice Smith", "alice@university.edu",
                                        "555-0102", "S12345", "Tech University"));

    SECTION("Complete workflow: borrow, check status, return")
    {
        // Initial state
        CoutCapture capture;
        library.displayLibraryStats();
        std::string initialStats = capture.GetOutput();
        REQUIRE(initialStats.find("Available Books: 1") != std::string::npos);
        REQUIRE(initialStats.find("Active Loans: 0") != std::string::npos);

        // Borrow book
        capture.clear();
        bool borrowResult = library.borrowBook("M002", "978-0134685991");
        REQUIRE(borrowResult == true);

        // Check loans
        capture.clear();
        library.displayMemberLoans("M002");
        std::string loanDisplay = capture.GetOutput();
        REQUIRE(loanDisplay.find("Active") != std::string::npos);

        // Check updated stats
        capture.clear();
        library.displayLibraryStats();
        std::string borrowStats = capture.GetOutput();
        REQUIRE(borrowStats.find("Available Books: 0") != std::string::npos);
        REQUIRE(borrowStats.find("Active Loans: 1") != std::string::npos);

        // Return book
        capture.clear();
        bool returnResult = library.returnBook("L1000");
        REQUIRE(returnResult == true);

        // Check final stats
        capture.clear();
        library.displayLibraryStats();
        std::string finalStats = capture.GetOutput();
        REQUIRE(finalStats.find("Available Books: 1") != std::string::npos);
        REQUIRE(finalStats.find("Active Loans: 0") != std::string::npos);
    }
}

// Edge Cases and Error Handling
TEST_CASE("Library - Edge Cases", "[library][edge_cases]")
{
    Library library("Edge Case Library");

    SECTION("Empty library operations")
    {
        CoutCapture capture;

        // Try to borrow from empty library
        bool borrowResult = library.borrowBook("M001", "978-0134685991");
        REQUIRE(borrowResult == false);

        // Try to return non-existent loan
        bool returnResult = library.returnBook("L1000");
        REQUIRE(returnResult == false);

        // Search in empty library
        library.searchBooks("test", "title");
        std::string output = capture.GetOutput();
        REQUIRE(output.find("No books found") != std::string::npos);
    }

    SECTION("Different member types borrowing behavior")
    {
        // Add same book multiple times for testing
        library.addBook(
            std::make_unique<PhysicalBook>("978-0001", "Book1", "Author1", "Genre1", "A1"));
        library.addBook(
            std::make_unique<PhysicalBook>("978-0002", "Book2", "Author2", "Genre2", "A2"));
        library.addBook(
            std::make_unique<PhysicalBook>("978-0003", "Book3", "Author3", "Genre3", "A3"));
        library.addBook(
            std::make_unique<PhysicalBook>("978-0004", "Book4", "Author4", "Genre4", "A4"));
        library.addBook(
            std::make_unique<PhysicalBook>("978-0005", "Book5", "Author5", "Genre5", "A5"));
        library.addBook(
            std::make_unique<PhysicalBook>("978-0006", "Book6", "Author6", "Genre6", "A6"));

        library.addMember(
            new Member("M001", "Regular Member", "regular@email.com", "555-0001"));
        library.addMember(new StudentMember("M002", "Student Member", "student@email.com",
                                            "555-0002", "S001", "University"));
        library.addMember(new FacultyMember("M003", "Faculty Member", "faculty@email.com",
                                            "555-0003", "CS", "Professor"));

        // Regular member: 3 books max
        REQUIRE(library.borrowBook("M001", "978-0001") == true);
        REQUIRE(library.borrowBook("M001", "978-0002") == true);
        REQUIRE(library.borrowBook("M001", "978-0003") == true);

        CoutCapture capture;
        REQUIRE(library.borrowBook("M001", "978-0004") == false); // Should exceed limit
        std::string output = capture.GetOutput();
        REQUIRE(output.find("borrowing limit") != std::string::npos);

        // Student member: 5 books max
        REQUIRE(library.borrowBook("M002", "978-0004") == true);
        REQUIRE(library.borrowBook("M002", "978-0005") == true);
        // Would need more books to test student limit fully
    }
}

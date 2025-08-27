// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include "library.h"

#include <iostream>
#include <memory>

using namespace lms_sk;

// Demo function to show the system in action
void demonstrateLibrarySystem()
{
    Library library("Central City Library");

    // Add books using smart pointers
    library.addBook(
        std::make_unique<PhysicalBook>(
            "978-0134685991", "Effective Modern C++", "Scott Meyers", "Programming",
            "A1-23"));
    library.addBook(
        std::make_unique<PhysicalBook>(
            "978-0321563842", "The C++ Programming Language", "Bjarne Stroustrup",
            "Programming", "A1-24"));
    library.addBook(
        std::make_unique<EBook>(
            "978-1449373320", "Designing Data-Intensive Applications", "Martin Kleppmann",
            "Technology", "https://library.com/ebooks/ddia", 15));
    library.addBook(
        std::make_unique<PhysicalBook>(
            "978-0132350884", "Clean Code", "Robert C. Martin", "Programming", "A2-10"));

    // Add members using raw pointers (the one case for manual memory management)
    library.addMember(new Member("M001", "John Doe", "john@email.com", "555-0101"));
    library.addMember(
        new StudentMember(
            "M002", "Alice Smith", "alice@university.edu", "555-0102", "S12345",
            "Tech University"));
    library.addMember(
        new FacultyMember(
            "M003", "Dr. Bob Johnson", "bob@university.edu", "555-0103", "Computer Science",
            "Professor"));

    std::cout << "=== Welcome to the Library Management System Demo ===" << std::endl;

    // Display initial stats
    library.displayLibraryStats();
    std::cout << std::endl;

    // Demonstrate borrowing
    std::cout << "=== Borrowing Books ===" << std::endl;
    library.borrowBook("M001", "978-0134685991");
    library.borrowBook("M002", "978-1449373320");
    library.borrowBook("M003", "978-0132350884");
    std::cout << std::endl;

    // Search functionality
    std::cout << "=== Searching Books ===" << std::endl;
    library.searchBooks("C++", "title");
    std::cout << std::endl;

    // Display member loans
    std::cout << "=== Member Loans ===" << std::endl;
    library.displayMemberLoans("M001");
    std::cout << std::endl;

    // Return books
    std::cout << "=== Returning Books ===" << std::endl;
    library.returnBook("L1000");
    std::cout << std::endl;

    // Final stats
    library.displayLibraryStats();
}

int main()
{
    demonstrateLibrarySystem();
    return 0;
}
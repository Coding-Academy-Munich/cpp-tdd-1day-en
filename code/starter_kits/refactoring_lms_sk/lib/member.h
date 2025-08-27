// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef REFACTORING_LMS_SK_LIB_MEMBER_H
#define REFACTORING_LMS_SK_LIB_MEMBER_H

#include <ctime>
#include <iostream>
#include <string>

namespace lms_sk
{
    // Base Member class with inheritance opportunities
    class Member
    {
    protected:
        std::string memberId;
        std::string name;
        std::string email;
        std::string phone;
        std::time_t membershipDate;

    public:
        Member(const std::string& memberId, const std::string& name,
               const std::string& email, const std::string& phone) :
            memberId(memberId), name(name), email(email), phone(phone)
        {
            membershipDate = std::time(nullptr);
        }

        virtual ~Member() = default;

        // Getters - potential encapsulation opportunities
        std::string getMemberId() const
        {
            return memberId;
        }
        std::string getName() const
        {
            return name;
        }
        std::string getEmail() const
        {
            return email;
        }
        std::string getPhone() const
        {
            return phone;
        }

        // Virtual methods for polymorphism
        virtual int getMaxBooks() const
        {
            return 3; // Magic number - refactoring opportunity
        }

        virtual int getMaxLoanDays() const
        {
            return 14; // Magic number - refactoring opportunity
        }

        virtual double getDiscountRate() const
        {
            return 0.0; // No discount for regular members
        }

        virtual void displayInfo() const
        {
            std::cout << "Member: " << name << " (ID: " << memberId << ")" << std::endl;
            std::cout << "Email: " << email << ", Phone: " << phone << std::endl;
        }
    };

    class StudentMember : public Member
    {
    private:
        std::string studentId;
        std::string university;

    public:
        StudentMember(const std::string& memberId, const std::string& name,
                      const std::string& email, const std::string& phone,
                      const std::string& studentId, const std::string& university) :
            Member(memberId, name, email, phone), studentId(studentId),
            university(university)
        {
        }

        int getMaxBooks() const override
        {
            return 5; // Students can borrow more books
        }

        int getMaxLoanDays() const override
        {
            return 21; // Longer loan period for students
        }

        double getDiscountRate() const override
        {
            return 0.10; // 10% discount on late fees
        }

        void displayInfo() const override
        {
            Member::displayInfo();
            std::cout << "Student ID: " << studentId << ", University: " << university
                      << std::endl;
        }
    };

    class FacultyMember : public Member
    {
    private:
        std::string department;
        std::string position;

    public:
        FacultyMember(const std::string& memberId, const std::string& name,
                      const std::string& email, const std::string& phone,
                      const std::string& department, const std::string& position) :
            Member(memberId, name, email, phone), department(department), position(position)
        {
        }

        int getMaxBooks() const override
        {
            return 10; // Faculty can borrow many books
        }

        int getMaxLoanDays() const override
        {
            return 30; // Longest loan period for faculty
        }

        double getDiscountRate() const override
        {
            return 0.20; // 20% discount on late fees
        }

        void displayInfo() const override
        {
            Member::displayInfo();
            std::cout << "Department: " << department << ", Position: " << position
                      << std::endl;
        }
    };
} // namespace lms_sk

#endif // REFACTORING_LMS_SK_LIB_MEMBER_H

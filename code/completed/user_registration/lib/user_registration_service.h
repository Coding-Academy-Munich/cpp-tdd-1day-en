// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef LIB_USER_REGISTRATION_H
#define LIB_USER_REGISTRATION_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace user_registration
{

    struct User
    {
        std::string name;
        std::string email;
        int age;
        std::string role;
    };

    // Interfaces for external dependencies
    class IUserRepository
    {
    public:
        virtual ~IUserRepository() = default;
        virtual void save(const User& user) = 0;
    };

    class IEmailService
    {
    public:
        virtual ~IEmailService() = default;
        virtual void send_welcome_email(const User& user) = 0;
    };

    // 1. Pure business logic - easily testable
    class UserProcessor
    {
    public:
        struct ProcessingResult
        {
            bool is_valid;
            User processed_user;
            std::string error_message;
        };

        ProcessingResult process_user(const User& user)
        {
            ProcessingResult result;
            result.processed_user = user;

            // Validation business logic
            if (!is_valid_user(user))
            {
                result.is_valid = false;
                result.error_message = "Invalid user data";
                return result;
            }

            // Business rules
            result.processed_user.role = assign_role(user);
            result.is_valid = true;
            return result;
        }

        // Now these methods are easily testable
        bool is_valid_user(const User& user)
        {
            return !user.name.empty() &&
                user.email.find('@') != std::string::npos && user.age >= 18 &&
                user.age <= 120;
        }

        std::string assign_role(const User& user)
        {
            if (user.age >= 65)
            {
                return "senior";
            }
            if (user.age >= 18)
            {
                return "adult";
            }
            return "minor";
        }
    };

    // 2. Humble Object - only handles infrastructure
    class UserRegistrationService
    {
    private:
        UserProcessor processor;
        IUserRepository* repository;
        IEmailService* email_service;

    public:
        UserRegistrationService(IUserRepository* repo, IEmailService* email) :
            repository(repo), email_service(email)
        {
        }

        void register_users_from_file(const std::string& file_path)
        {
            // Only handles file I/O
            std::ifstream file(file_path);
            if (!file)
            {
                throw std::runtime_error("Could not open file");
            }

            std::string line;
            while (std::getline(file, line))
            {
                User user = parse_user_line(line);

                // Delegate to business logic
                auto result = processor.process_user(user);

                if (!result.is_valid)
                {
                    std::cout << "Invalid user (" << result.processed_user.name
                              << "): " << result.error_message << std::endl;
                    continue;
                }

                // Handle infrastructure
                repository->save(result.processed_user);
                email_service->send_welcome_email(result.processed_user);
            }
        }

    private:
        User parse_user_line(const std::string& line)
        {
            std::stringstream ss(line);
            std::string name, email, age_str;

            std::getline(ss, name, ',');
            std::getline(ss, email, ',');
            std::getline(ss, age_str, ',');

            return {name, email, std::stoi(age_str), ""};
        }
    };

    // 3. Test implementations
    class MockUserRepository : public IUserRepository
    {
    public:
        std::vector<User> saved_users;

        void save(const User& user) override
        {
            saved_users.push_back(user);
        }
    };

    class MockEmailService : public IEmailService
    {
    public:
        std::vector<std::string> sent_emails;

        void send_welcome_email(const User& user) override
        {
            sent_emails.push_back(user.email);
        }
    };

} // namespace user_registration
#endif // LIB_USER_REGISTRATION_H

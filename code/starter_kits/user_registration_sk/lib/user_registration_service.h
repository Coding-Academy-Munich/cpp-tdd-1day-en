// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef LIB_USER_REGISTRATION_SERVICE
#define LIB_USER_REGISTRATION_SERVICE

#include <string>

namespace user_registration_sk
{
    struct User
    {
        std::string name;
        std::string email;
        int age;
        std::string role;
    };

    // Original monolithic class - hard to test
    class UserRegistrationService
    {
    public:
        void register_users_from_file(const std::string& file_path);

    private:
        User parse_user_line(const std::string& line);

        // Business logic - should be easily testable
        bool is_valid_user(const User& user);

        // Business logic - should be easily testable
        std::string assign_role(const User& user);

        // Infrastructure - hard to test
        void save_to_database(const User& user);

        // Infrastructure - hard to test
        void send_welcome_email(const User& user);
    };

} // namespace user_registration_sk
#endif // LIB_USER_REGISTRATION_SERVICE

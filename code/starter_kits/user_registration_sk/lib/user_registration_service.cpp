// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include <fstream>
#include <iostream>
#include <sstream>

#include "user_registration_service.h"


namespace user_registration_sk
{
    void UserRegistrationService::register_users_from_file(
        const std::string& file_path)
    {
        // 1. Read from file (infrastructure)
        std::ifstream file(file_path);
        if (!file)
        {
            throw std::runtime_error("Could not open file");
        }

        std::string line;
        while (std::getline(file, line))
        {
            // 2. Parse user data (could be business logic)
            User user = parse_user_line(line);

            // 3. Business logic validation
            if (!is_valid_user(user))
            {
                std::cout << "Invalid user: " << user.name << std::endl;
                continue;
            }

            // 4. Apply business rules
            std::string assigned_role = assign_role(user);
            user.role = assigned_role;

            // 5. Save to database (infrastructure)
            save_to_database(user);

            // 6. Send email (infrastructure)
            send_welcome_email(user);
        }
    }

    User UserRegistrationService::parse_user_line(const std::string& line)
    {
        std::stringstream ss(line);
        std::string name, email, age_str;

        std::getline(ss, name, ',');
        std::getline(ss, email, ',');
        std::getline(ss, age_str, ',');

        return {name, email, std::stoi(age_str), ""};
    }

    bool UserRegistrationService::is_valid_user(const User& user)
    {
        return !user.name.empty() && user.email.find('@') != std::string::npos &&
            user.age >= 18 && user.age <= 120;
    }

    std::string UserRegistrationService::assign_role(const User& user)
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

    void UserRegistrationService::save_to_database(const User& user)
    {
        std::cout << "Saving to DB: " << user.name << std::endl;
        // Simulate database save
    }

    void UserRegistrationService::send_welcome_email(const User& user)
    {
        std::cout << "Sending email to: " << user.email << std::endl;
        // Simulate email sending
    }

} // namespace user_registration_sk

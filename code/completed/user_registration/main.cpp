// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include "user_registration_service.h"

using namespace user_registration;

class DemoUserRepository : public IUserRepository
{
public:
    void save(const User& user) override
    {
        std::cout << "Saving user to database: " << user.name << std::endl;
        // Simulate database save
    }
};

class DemoEmailService : public IEmailService
{
public:
    void send_welcome_email(const User& user) override
    {
        std::cout << "Sending welcome email to: " << user.email << std::endl;
        // Simulate email sending
    }
};

void demonstrate_humble_object_solution()
{
    // Create services
    DemoUserRepository user_repository;
    DemoEmailService email_service;

    // Create the humble object
    UserRegistrationService service(&user_repository, &email_service);

    // Process users from a file (simulated)
    try
    {
        service.register_users_from_file("users.txt");
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main()
{
    demonstrate_humble_object_solution();
}

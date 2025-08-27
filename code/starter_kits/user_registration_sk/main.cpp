// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include <iostream>

#include "user_registration_service.h"

void demonstrate_user_registration_service()
{
    user_registration_sk::UserRegistrationService service;
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
    demonstrate_user_registration_service();
}

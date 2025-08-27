// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include "user_registration_service.h"

#include <catch2/catch_test_macros.hpp>

using namespace user_registration;


TEST_CASE("Business logic unit tests")
{
    UserProcessor processor;

    SECTION("Test valid user")
    {
        User valid_user{"John Doe", "john@example.com", 30, ""};
        auto result = processor.process_user(valid_user);

        REQUIRE(result.is_valid);
        REQUIRE(result.processed_user.role == "adult");
    }

    SECTION("Test invalid user")
    {
        User invalid_user{"", "invalid-email", 17, ""};
        auto invalid_result = processor.process_user(invalid_user);

        REQUIRE(!invalid_result.is_valid);
    }

    SECTION("Test senior user")
    {
        User senior_user{"Jane Smith", "jane@example.com", 70, ""};
        auto senior_result = processor.process_user(senior_user);

        REQUIRE(senior_result.is_valid);
        REQUIRE(senior_result.processed_user.role == "senior");
    }
}

TEST_CASE("Integration test")
{
    MockUserRepository mock_repo;
    MockEmailService mock_email;

    UserRegistrationService service(&mock_repo, &mock_email);

    UserProcessor processor;
    User test_user{"Alice Johnson", "alice@example.com", 25, ""};

    auto result = processor.process_user(test_user);
    if (result.is_valid)
    {
        mock_repo.save(result.processed_user);
        mock_email.send_welcome_email(result.processed_user);
    }

    REQUIRE(mock_repo.saved_users.size() == 1);
    REQUIRE(mock_email.sent_emails.size() == 1);
    REQUIRE(mock_repo.saved_users[0].role == "adult");
}

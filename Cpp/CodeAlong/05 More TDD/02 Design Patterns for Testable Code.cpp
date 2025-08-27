// -*- coding: utf-8 -*-
// %% [markdown]
//
// <div style="text-align:center; font-size:200%;">
//   <b>Design Patterns for Testable Code</b>
// </div>
// <br/>
// <div style="text-align:center; font-size:120%;">Dr. Matthias Hölzl</div>
// <br/>
// <div style="text-align:center;">Coding-Academy Munich</div>
// <br/>
// <!-- 02 Design Patterns for Testable Code.cpp -->
// <!-- slides/module_410_unit_testing/topic_210_design_patterns_for_tests.cpp -->


// %% [markdown]
//
// ## Seams
//
// - Points in the code where we can change behavior for testing without
//   modifying the code itself.
// - Important for introducing test doubles.
// - Examples:
//   - Virtual functions/interfaces
//   - Template parameters
//   - Function pointers
//   - Functions from dynamic libraries

// %% [markdown]
//
// ## Patterns for Testability
//
// - **Dependency Injection (DI)**
//   - Introduces seams by injecting dependencies from the outside.
// - **Dependency Inversion Principle (DIP):**
//   - Allows controlling the direction of dependencies.
//   - Introduces interfaces that improve testability.
// - **Humble Object Pattern:**
//   - Isolates complex, hard-to-test logic from the outside world.

// %% [markdown]
//
// ### Dependency Injection
//
// - A class should not create its own dependencies.
// - Instead, they are "injected" from the outside (e.g., via the constructor).

// %%
#include <iostream>
#include <memory>

// %%
class IDependency
{
public:
    virtual ~IDependency() = default;
    virtual void perform_work() const = 0;
};

// %%
class Dependency : public IDependency
{
public:
    void perform_work() const override
    {
        std::cout << "Performing work in Dependency" << std::endl;
    }
};

// %%
class MyClassWithoutDI
{
public:
    MyClassWithoutDI() : dependency{std::make_unique<Dependency>()} {}

    void do_something() const { dependency->perform_work(); }

private:
    std::unique_ptr<IDependency> dependency;
};

// %%

// %%

// %%

// %%

// %%

// %% [markdown]
//
// # Dependency Inversion Principle
//
// - The core functionality of a system does not depend on its environment
//   - **Concrete artifacts depend on abstractions** (not vice versa)
//   - **Unstable artifacts depend on stable artifacts** (not vice versa)
//   - **Outer layers** of the architecture **depend on inner layers** (not vice
//     versa)
//   - Classes/Modules depend on abstractions (e.g., interfaces) not on other
//     classes/modules
// - Dependency inversion achieves this by introducing interfaces that “reverse
//   the dependencies”

// %% [markdown]
//
// ## Dependencies
//
// - We have to distinguish two kinds of dependencies:
//   - Data and control flow
//   - Source code dependencies
// - Data and control flow dependencies are inherent in the logic
// - Source code dependencies can be controlled by the architecture

// %% [markdown]
//
// The source code dependency goes in the same direction as the data flow:
//
// `MyModule.cpp` ⟹ `Database.h`
//
// <img src="img/db-example-01.svg"
//      style="display:block;margin:auto;width:75%"/>

// %% [markdown]
//
// ### Before
// <img src="img/dependency-01.svg"
//      style="display:block;margin:auto;width:75%"/>
//
// ### After
// <img src="img/dependency-02.svg"
//      style="display:block;margin:auto;width:75%"/>

// %% [markdown]
//
// <img src="img/dip-01.svg"
//      style="display:block;margin:auto;width:95%"/>

// %% [markdown]
//
// <img src="img/dip-02.svg"
//      style="display:block;margin:auto;width:95%"/>

// %% [markdown]
//
// <img src="img/dip-03.svg"
//      style="display:block;margin:auto;width:95%"/>

// %% [markdown]
//
// ## How DIP and DI work together:
//
// - DIP: abstract interface
// - DI: injection of the concrete implementation at runtime
//
// **Effect:** Ability to bring test doubles into play

// %% [markdown]
//
// ### Humble Object Pattern
//
// **Problem:**
// - How do you test code that is heavily intertwined with "inconvenient"
//   infrastructure?
//   - UI
//   - Database
//   - API
//   - ...

// %% [markdown]
//
// ### Humble Object Pattern
//
// **Solution:** Split the class into two parts:
// 1.  **The Humble Object:**
//     - A very thin wrapper at the boundary to the external system.
//     - Contains *no* logic (no `if` statements, loops, etc.).
//     - Its only job: shuttle data back and forth.
//     - Is so simple that it doesn't need to be tested.
//
// 2.  **The Testable Logic:**
//     - All the complex code (business logic, decisions).
//     - Is extracted into a separate class that has no knowledge of the infrastructure.
//     - This class is easily and fully testable.

// %% [markdown]
//
// ## Refactoring to a Testable Object
//
// **Goal:** Refactor a hard-to-test class that mixes business logic and
// external dependencies using the described patterns.
//
// **Scenario:** An `OrderProcessor` that:
//
// - reads order data from a file,
// - calculates discounts and checks inventory,
// - saves orders to a database,
// - updates inventory.
//
// This is difficult to test because it depends on file system and database.
//
// A starter kit is available in the repository under
// `code/starter_kits/order_processor_sk`. A (partial) solution is available
// under `code/completed/order_processor`.

// %% [markdown]
//
// ## Workshop: Refactoring to a Testable Object
//
// **Goal:** Refactor a hard-to-test class that mixes business logic and external
// dependencies using the patterns we discussed.
//
// **Scenario:** A `UserRegistrationService` that:
//
// - reads user data from a file,
// - applies validation and business rules,
// - saves users to a database,
// - sends email notifications.
//
// This is difficult to test because it depends on file system, database, and email
// service.

// %% [markdown]
//
// Here is the class we will refactor. Notice how the business logic
// is mixed with external dependencies.
//
// A starter kit is available in the repository under
// `code/starter_kits/user_registration_sk`.

// %%
#include "check.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// %%
struct User
{
    std::string name;
    std::string email;
    int age;
    std::string role;
};

// %%
// Original monolithic class - hard to test
class UserRegistrationService
{
public:
    void register_users_from_file(const std::string& file_path)
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

    // Business logic - should be easily testable
    bool is_valid_user(const User& user)
    {
        return !user.name.empty() && user.email.find('@') != std::string::npos &&
               user.age >= 18 && user.age <= 120;
    }

    // Business logic - should be easily testable
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

    // Infrastructure - hard to test
    void save_to_database(const User& user)
    {
        std::cout << "Saving to DB: " << user.name << std::endl;
        // Simulate database save
    }

    // Infrastructure - hard to test
    void send_welcome_email(const User& user)
    {
        std::cout << "Sending email to: " << user.email << std::endl;
        // Simulate email sending
    }
};

// %%
void demonstrate_user_registration_service()
{
    UserRegistrationService service;
    try
    {
        service.register_users_from_file("users.txt");
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// %%
demonstrate_user_registration_service();

// %% [markdown]
//
// ### Your Task: Refactor & Test
//
// 1.  **Extract the Business Logic:** Create a `UserProcessor` class that encapsulates
// the pure business logic (validation, role assignment).
// 2.  **Create the Humble Object:** The original `UserRegistrationService` becomes
// the Humble Object. It only handles I/O and delegates business logic.
// 3.  **Abstract the Infrastructure:** Use interfaces for database and email service
// to improve testability.
// 4.  **Write Tests:** Write unit tests for the `UserProcessor` class.

// %%

// %%

// %%

// %%

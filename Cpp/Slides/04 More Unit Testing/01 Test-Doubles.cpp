// -*- coding: utf-8 -*-
// %% [markdown]
//
// <div style="text-align:center; font-size:200%;">
//   <b>Test-Doubles</b>
// </div>
// <br/>
// <div style="text-align:center; font-size:120%;">Dr. Matthias Hölzl</div>
// <br/>
// <div style="text-align:center;">Coding-Academy Munich</div>
// <br/>
// <!-- 01 Test-Doubles.cpp -->
// <!-- slides/module_410_unit_testing/topic_162_test_doubles.cpp -->


// %% [markdown]
//
// ## Test Doubles
//
// - Simplified version of a dependency in the system
//   - e.g. replace a database query with a fixed value
// - Test Doubles are important for simplifying tests
// - They typically require an interface that they implement
// - But: too many or complex test doubles make tests confusing
//   - What is actually being tested by a test?

// %% [markdown]
//
// ## Types of Test Doubles
//
// - Outgoing dependencies ("Mocks")
//   - Mocks
//   - Spies
// - Incoming dependencies ("Stubs")
//   - Dummies
//   - Stubs
//   - Fakes

// %% [markdown]
//
// ## Dummy
//
// - Object that only serves as a placeholder
// - Passed, but not used
// - In C++ sometimes `nullptr`
// - Also for outgoing dependencies

// %% [markdown]
//
// ## Stub
//
// - Object that provides a minimal implementation of a dependency
// - Typically always returns the same value
// - Used to
//   - replace complex dependencies
//   - make tests deterministic

// %% [markdown]
//
// ## Fake
//
// - Object that provides a simpler implementation of a dependency
// - Can be e.g. an in-memory database
// - Used to
//   - speed up tests
//   - simplify test configuration

// %% [markdown]
//
// ## Spy
//
// - Object that stores information about the interaction with it
// - Used to
//   - check if a dependency is used correctly

// %% [markdown]
//
// ## Mock
//
// - Object that stores information about the expected interaction
// - Typically declaratively configurable
// - Automated implementation of spies
// - Used to
//   - check if a dependency is used correctly
// %% [markdown]
// ## Example: E-Commerce System
//
// We want to add an item to a shopping cart.
//
// - The `CartManager` is the class to be tested (System Under Test).
// - It uses a `ProductPriceProvider` to get the price of an item (incoming dependency).
// - It uses a `ShoppingCart` to add the item (outgoing dependency).
//
// First, we define the interfaces for our dependencies:

// %%
#include <string>


// %%
class ProductPriceProvider
{
public:
    virtual ~ProductPriceProvider() = default;
    virtual double get_price(const std::string& product_id) = 0;
};

// %%
class ShoppingCart
{
public:
    virtual ~ShoppingCart() = default;
    virtual void add_item(const std::string& product_id, double price) = 0;
};

// %% [markdown]
//
// ## The Class Under Test: `CartManager`
//
// The `CartManager` gets the price and adds the item to the cart.

// %%
struct CartManager
{
    ProductPriceProvider& price_provider;
    ShoppingCart& cart;

    void add_to_cart(const std::string& product_id)
    {
        double price{price_provider.get_price(product_id)};
        cart.add_item(product_id, price);
    }
};

// %% [markdown]
//
// ## The Test Doubles: Stub and Spy
//
// - For the `ProductPriceProvider` we use a **Stub** that returns a fixed
//   price.
// - For the `ShoppingCart` we use a **Spy** that records which items were
//   added.

// %%
class ProductPriceProviderStub : public ProductPriceProvider
{
public:
    double get_price(const std::string& product_id) override { return 99.99; }
};

// %%
#include <vector>

// %%
class ShoppingCartSpy : public ShoppingCart
{
public:
    struct AddedItem {
        std::string product_id;
        double price;
    };
    std::vector<AddedItem> items;

    void add_item(const std::string& product_id, double price) override
    {
        items.push_back({product_id, price});
    }
};

// %% [markdown]
//
// In the test, we verify that the `CartManager` used the `ShoppingCart`
// correctly.

// %%
#include "check.h"
#include <string>
#include <vector>

// %%
void test_cart_manager_adds_item_with_correct_price()
{
    ProductPriceProviderStub price_provider; // Our Stub
    ShoppingCartSpy cart;                    // Our Spy
    CartManager manager{price_provider, cart};
    const std::string product_id = "book-123";

    manager.add_to_cart(product_id);

    check(cart.items.size() == 1);
    check(cart.items[0].product_id == product_id);
    check(cart.items[0].price == 99.99);
}

// %%
test_cart_manager_adds_item_with_correct_price();

// %% [markdown]
//
// ## Typical use of test doubles:
//
// - database access, file system access
// - time, random values
// - non-determinism
// - hidden state

// %% [markdown]
//
// ## Workshop: Testing a Spacecraft Controller
//
// Your task is to implement a test suite for a `SpacecraftCommandController`.
// This class sends commands to a spacecraft. Its responsibilities are:
//
// - Mission safety is paramount: Check the system status (`TelemetrySystem`)
//   before executing commands.
// - Execute maneuvers with the thrusters (`ThrusterControl`).
// - Notify ground control about command status (`GroundControlLink`).
//
// **Note:** A starter kit is available in
// `code/starter_kits/spacecraft_controller_sk`.

// %% [markdown]
// First, the interfaces for the spacecraft's subsystems:

// %%
#include <string>
#include <vector>

// %%
enum class SubSystem { Core, Thrusters, ScienceBay };

// %%
class TelemetrySystem {
public:
    virtual ~TelemetrySystem() = default;
    virtual int get_power_level_percent(SubSystem system) = 0;
};

// %%
class ThrusterControl {
public:
    virtual ~ThrusterControl() = default;
    virtual void fire_thrusters(int duration_ms) = 0;
};

// %%
class GroundControlLink {
public:
    virtual ~GroundControlLink() = default;
    virtual void send_status_report(const std::string& report) = 0;
};


// %% [markdown]
// The class under test: `SpacecraftCommandController`.

// %%
class SpacecraftCommandController {
private:
    TelemetrySystem& telemetry;
    ThrusterControl& thrusters;
    GroundControlLink& ground_control;

public:
    SpacecraftCommandController(TelemetrySystem& tel, ThrusterControl& thr, GroundControlLink& gc)
        : telemetry{tel}, thrusters{thr}, ground_control{gc} {}

    void execute_burn_maneuver(int duration_ms) {
        int power_level{telemetry.get_power_level_percent(SubSystem::Thrusters)};
        if (power_level < 50) {
            ground_control.send_status_report("ERROR: Thruster power too low for maneuver.");
            return;
        }

        thrusters.fire_thrusters(duration_ms);
        ground_control.send_status_report("SUCCESS: Maneuver executed.");
    }
};

// %% [markdown]
//
// ## Your Task
//
// Write tests for the following scenarios. Implement the necessary test
// doubles.
//
// 1.  **Successful Maneuver:** The thruster system has sufficient power (>50%).
//     Verify that the `fire_thrusters` command is sent and a success report is
//     sent to ground control.
// 2.  **Maneuver Aborted (Low Power):** The thruster system has insufficient
//     power (<50%). Verify that the thrusters are **not** fired and an error
//     report is sent to ground control.

// %% [markdown]
// ## Solution: Test Doubles
//
// We need a configurable stub for `TelemetrySystem` and spies for
// `ThrusterControl` and `GroundControlLink`.

// %%
// A configurable stub for the telemetry system.
class TelemetrySystemStub : public TelemetrySystem
{
public:
    int power_level{100};
    int get_power_level_percent(SubSystem system) override { return power_level; }
};

// %%
// A spy to record thruster commands.
class ThrusterControlSpy : public ThrusterControl
{
public:
    int burn_duration_ms{0};
    int times_fired{0};

    void fire_thrusters(int duration_ms) override {
        times_fired++;
        burn_duration_ms = duration_ms;
    }
};

// %%
// A spy to record reports sent to ground control.
class GroundControlLinkSpy : public GroundControlLink
{
public:
    std::vector<std::string> reports;
    void send_status_report(const std::string& report) override {
        reports.push_back(report);
    }
};

// %%
// ## Solution: Tests

// %%
#include "check.h"


// %%
void test_successful_burn_maneuver()
{
    TelemetrySystemStub telemetry;
    telemetry.power_level = 75; // Set sufficient power

    ThrusterControlSpy thrusters;
    GroundControlLinkSpy ground_control;

    SpacecraftCommandController controller{telemetry, thrusters, ground_control};

    controller.execute_burn_maneuver(500);

    check(thrusters.times_fired == 1);
    check(thrusters.burn_duration_ms == 500);
    check(ground_control.reports.size() == 1);
    check(ground_control.reports[0] == "SUCCESS: Maneuver executed.");
}

// %%
void test_aborted_maneuver_due_to_low_power()
{
    TelemetrySystemStub telemetry;
    telemetry.power_level = 40; // Set insufficient power

    ThrusterControlSpy thrusters;
    GroundControlLinkSpy ground_control;

    SpacecraftCommandController controller{telemetry, thrusters, ground_control};

    controller.execute_burn_maneuver(500);

    check(thrusters.times_fired == 0); // Thrusters should not be fired!
    check(ground_control.reports.size() == 1);
    check(ground_control.reports[0] == "ERROR: Thruster power too low for maneuver.");
}


// %%
test_successful_burn_maneuver();
test_aborted_maneuver_due_to_low_power();

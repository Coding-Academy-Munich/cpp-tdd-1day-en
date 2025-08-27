// -*- coding: utf-8 -*-
// %% [markdown]
//
// <div style="text-align:center; font-size:200%;">
//   <b>Isolation of Unit Tests</b>
// </div>
// <br/>
// <div style="text-align:center; font-size:120%;">Dr. Matthias Hölzl</div>
// <br/>
// <div style="text-align:center;">Coding-Academy Munich</div>
// <br/>
// <!-- 02 Isolation of Unit Tests.cpp -->
// <!-- slides/module_410_unit_testing/topic_160_test_isolation.cpp -->


// %% [markdown]
//
// ## Unit Test: A Definition
//
// - Tests a small piece of code (a **"unit"**)
// - Runs quickly
// - Is **isolated**

// %% [markdown]
//
// ## What is a "Unit"?
//
// - **A Behavior (Chicago/Classicist School):**
//   - A "Unit of Behavior".
//   - Often a group of collaborating classes that achieve a specific outcome.
//   - Focuses on the *outcome* of an operation.
//
// - **A Class (London/Mockist School):**
//   - A "Unit of Code", typically a single class.
//   - Focuses on the *interactions* of a class with its dependencies.

// %% [markdown]
//
// ## What does "isolated" test mean?
//
// - **Isolation between test cases (Chicago School):**
//   - No test influences the outcome of another test.
//   - Tests can be run in parallel and in any order.
//   - Uses real objects as dependencies as long as they are fast and deterministic.
//
// - **Isolation of the unit under test (London School):**
//   - The class under test is isolated from the rest of the *production system*.
//   - All dependencies are replaced by test doubles (especially mocks).

// %% [markdown]
// ## Trade-offs: Chicago (Classicist) vs. London (Mockist)
//
// |Feature                  |Chicago School (Classicist)                                  |London School (Mockist)                                     |
// |-------------------------|-------------------------------------------------------------|------------------------------------------------------------|
// |**Focus**                |State Verification                                           |Behavior Verification                                       |
// |**Unit Under Test**      |A behavior (often multiple classes)                          |A single class                                              |
// |**Test Doubles**         |Sparingly, for "inconvenient" dependencies (Stubs, Fakes)    |Extensively, for all dependencies (Mocks)                   |
// |**Strengths**            |- Tests are resilient to refactoring                         |- Precise defect localization                               |
// |                         |- Higher confidence in integration                           |- Drives decoupled design (Dependency Inversion)            |
// |**Weaknesses**           |- Defect localization can be hard (cascading failures)       |- Tests are brittle to refactoring                          |
// |                         |- Can require complex test setup                             |- Potential for integration gaps                            |
// |**Design Direction**     |Often Inside-Out                                             | Often Outside-In                                           |

// %% [markdown]
//
// ## Example: Detroit/Chicago School
//
// - The `TicketOffice` class is tested together with the real `Event` class.
// - The test verifies the *state* after the purchase.

// %%
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <map>
#include "check.h"

// %%
namespace classicist {
class Event
{
private:
    std::string name{"Unnamed Event"};
    int capacity{};

public:
    Event() = default;
    Event(std::string name, int capacity) : name{name}, capacity{capacity} {}

    std::string get_name() const { return name; }
    int get_capacity() const { return capacity; }
    void purchase(int num_tickets) {
        if (num_tickets > capacity) {
            throw std::runtime_error("Not enough capacity");
        }
        capacity -= num_tickets;
    }
};
} // namespace classicist

// %%
namespace classicist {
class TicketOffice
{
private:
    std::unordered_map<std::string, Event> events;

public:
    void add_event(Event event) { events[event.get_name()] = event; }
    Event get_event(const std::string& event_name) const { return events.at(event_name); }
    bool purchase_tickets(const std::string& event_name, int num_tickets) {
        if (events.count(event_name)) {
            try {
                events.at(event_name).purchase(num_tickets);
                return true;
            } catch (const std::runtime_error&) {
                return false;
            }
        }
        return false;
    }
};
} // namespace classicist

// %%

// %%

// %% [markdown]
// ## Example: London School
//
// - `TicketOffice` is isolated, `Event` is replaced by a mock.
// - The test verifies the *interaction* with the mock.

// %%
namespace mockist {
class Event {
public:
    virtual ~Event() = default;
    virtual std::string get_name() const = 0;
    virtual void purchase(int num_tickets) = 0;
};

// Actual implementation of Event interface skipped for brevity...
} // namespace mockist

// %%
namespace mockist {
class TicketOffice {
private:
    std::unordered_map<std::string, std::unique_ptr<Event>> events;
public:
    void add_event(std::unique_ptr<Event> event) {
        events[event->get_name()] = std::move(event);
    }
    Event& get_event(const std::string& event_name) const {
        return *events.at(event_name);
    }
    bool purchase_tickets(const std::string& event_name, int num_tickets) {
        if (events.count(event_name)) {
            events.at(event_name)->purchase(num_tickets);
            return true;
        }
        return false;
    }
};
} // namespace mockist

// %%
namespace mockist
{
class EventMock : public Event {
public:
    std::vector<int> purchase_call_args;
    std::string name = "CppCon";

    std::string get_name() const override { return name; }
    void purchase(int num_tickets) override {
        purchase_call_args.push_back(num_tickets);
    }
};
} // namespace mockist

// %%

// %%

// %% [markdown]
//
// ## Recommendation: A Pragmatic Middle Ground
//
// The choice between Chicago and London is not dogma, but a context-dependent
// decision.

// %% [markdown]
//
// - **Use the Chicago (Classicist) style for your core application logic:**
//   - For domain models, value objects, algorithms.
//   - Here, the outcome is important, and tests should survive refactoring.
//
// - **Use the London (Mockist) style at the boundaries of your system:**
//   - For controllers, service orchestrators, gateways to external services.
//   - Here, coordination is the main responsibility, so testing interactions is meaningful.

// %% [markdown]
//
// **The Golden Rule:**
//
// - Isolate only when it becomes painful.
// - Start with the simpler classicist approach
// - Introduce mocks only when you have a dependency that is
//   - slow,
//   - non-deterministic, or
//   - difficult to set up.


// %% [markdown]
//
// ## Workshop: Intelligent Vending Machine
//
// - **Goal:** To test a `VendingMachine` that manages its own stock.
// - We will do this in both the Chicago and London styles.
//
// - **Scenario:**
//   - A `VendingMachine` checks its `Inventory`.
//   - If an item's stock is low, an `OrderStrategy` is used to determine a
//     reorder.
//   - This order is then sent to an `IOrderService`.
//
// - **Notes:**
//   - You can also approach this task using TDD.
//   - A starter kit is available at `code/starter_kits/vending_machine_sk`.

// %% [markdown]
// ### Part 1: Chicago (Classicist) Style
//
// **Task:**
// - Define the classes as described below.
// - Use test-driven development.
// - Try to write the tests in the Chicago style, using real objects and
//   avoiding mocks where possible.

// %%
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <map>
#include "check.h"

// %%
namespace chicago_vending {
struct Item
{
    std::string name;
    int current_stock;
    int capacity;
};
}

// %%
namespace chicago_vending {
using Order = std::map<std::string, int>;
}

// %% [markdown]
//
// Define the `Inventory` class, which contains a collection of `Item` objects.
// It should have the following methods:
//
// - `void add_item(const Item& item)`: Adds an `Item` to the inventory.
// - `const Item& get_item(const std::string& name) const`: Returns an `Item`
//   by its name. If the `Item` is not found, it should throw an exception.
//
// Use TDD to write the code.

// %%

// %%

// %%

// %% [markdown]
//
// Define the `OrderStrategy` class, which has the following method:
//
// - `Order compute_order(const Inventory& inventory, double threshold) const`:
//   - This method takes an `Inventory` object and a threshold (between 0 and 1).
//   - It should return an `Order` containing all items whose current stock is
//     below the threshold.

// %%

// %%

// %%

// %% [markdown]
//
// - Define an `IOrderService` interface, with the following pure virtual
//   method:
// - `bool place_order(const Order& order)`.
//   - This method should accept and process an order.
//   - It should return `true` if the order was successfully placed, or `false`
//     if there was an error.

// %%


// %% [markdown]
//
// Implement a `FakeOrderService` that implements the `IOrderService`
// interface and stores all orders in a vector.


// %%

// %% [markdown]
//
// Define the `VendingMachine` class, which has the following methods:
//
// - `int get_stock(const std::string& item_name) const`:
//   - This method should return the current stock of an item.
//   - If the item is not found, it should throw an exception.
// - `void sell(const std::string& item_name, int quantity)`:
//   - This method should sell an item if enough stock is available.
//   - If there is not enough stock, it should throw an exception.
// - `void check_and_restock(double threshold)`:
//   - This method should check the inventory and trigger a reorder if needed.
//   - If the order is successful, it should update the stock of the items
//     in the inventory.
//   - If the order fails, it should throw an exception.
//
// Use test-driven development and write the tests in the Chicago style,
// using real objects and avoiding mocks where possible.

// %%

// %%

// %%

// %%

// %%

// %%

// %%

// %%

// %% [markdown]
// ### Part 2: London (Mockist) Style
//
// **Task:**
// - Refactor the code. `VendingMachine` should depend on interfaces
//   (`IInventory`, `IOrderStrategy`, `IOrderService`), not concrete classes.
// - Implement mocks for all three interfaces. The mocks should record which
//   methods were called.
// - Write tests in the London style, i.e., replace the real objects with mocks
//   and verify the interactions.

// %%

// %%


// %%

// %%

// %%

// %%

// %%

// %%

// %%

// %%

// %%

// %%

// %%

// %%

// %%

// %%

// %%

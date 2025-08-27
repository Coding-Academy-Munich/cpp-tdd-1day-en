// -*- coding: utf-8 -*-
// %% [markdown]
//
// <div style="text-align:center; font-size:200%;">
//   <b>Writing good Unit Tests</b>
// </div>
// <br/>
// <div style="text-align:center; font-size:120%;">Dr. Matthias Hölzl</div>
// <br/>
// <div style="text-align:center;">Coding-Academy Munich</div>
// <br/>
// <!-- 03 Writing good Unit Tests.cpp -->
// <!-- slides/module_410_unit_testing/topic_165_writing_good_unit_tests.cpp -->


// %% [markdown]
//
// ## Mechanics of Unit-Tests
//
// Unit tests should
// - be automated: no manual interaction
// - be self-testing: pass/fail
// - be fine-grained
// - be fast
// - be isolated
// - be executable successfully at any time

// %% [markdown]
//
// ## Simple structure!
//
// <ul>
//   <li>Simple, standardized structure
//     <table style="display:inline;margin:20px 20px;">
//     <tr><td style="text-align:left;width:60px;padding-left:15px;">Arrange</td>
//         <td style="text-align:left;width:60px;padding-left:15px;border-left:1px solid
//         black;">Given</td> <td
//         style="text-align:left;width:300px;padding-left:15px;border-left:1px solid
//         black;">
//           Prepare the test environment</td></tr>
//     <tr><td style="text-align:left;padding-left:15px;">Act</td>
//         <td style="text-align:left;width:60px;padding-left:15px;border-left:1px solid
//         black;">
//            When</td>
//         <td style="text-align:left;width:300px;padding-left:15px;border-left:1px
//         solid black;">
//            Execute the action for the test (if any)</td></tr>
//     <tr><td style="text-align:left;padding-left:15px;">Assert</td>
//         <td style="text-align:left;width:60px;padding-left:15px;border-left:1px solid
//         black;">
//            Then</td>
//         <td style="text-align:left;width:300px;padding-left:15px;border-left:1px
//         solid black;">
//            Check the results of the action/setup</td></tr>
//     </table>
//   </li>
//   <li>Little code
//     <ul>
//       <li>Little boilerplate</li>
//       <li>Factories, etc. for tests</li>
//     </ul>
//   </li>
// </ul>

// %%
#include "check.h"

// %%
#include <vector>

// %%
void test_insert()
{
    std::vector<int> x = {1, 2, 3}; // arrange
    std::vector<int> y = {10, 20};

    x.insert(x.end(), y.begin(), y.end()); // act

    check(x == std::vector<int>{1, 2, 3, 10, 20}); // assert
}

// %% [markdown]
//
// - How many tests do we want to have?
// - How many values do we want to check?

// %% [markdown]
//
// ## Try: Exhaustive testing
//
// - We write exhaustive tests, i.e. tests that cover all possible inputs of a program

// %% [markdown]
//
// - Exhaustive testing is not possible
// - Example: password input:
//   - Suppose passwords with a maximum of 20 characters are allowed,
//     80 input characters are allowed (upper and lower case letters, special
//     characters)
//   - This results in $80^{20}$ = 115,292,150,460,684,697,600,000,000,000,000,000,000
//     possible inputs
//   - At 10ns for a test, it would take about $10^{24}$ years to test all inputs
//   - The universe is about $1.4 \times 10^{10}$ years old

// %% [markdown]
//
// ## Effectiveness and efficiency of tests
//
// - Unit tests should be effective and efficient
//   - Effective: The tests should find as many bugs as possible
//   - Efficient: We want to find the largest number of bugs with the fewest number of
//     tests that are as simple as possible
// - Efficiency is important because Tests themselves are code that requires
//   maintenance and may contain bugs

// %% [markdown]
//
// ## How to write good unit tests?
//
// - Test observable behavior, not implementation
// - Prefer tests of values to tests of states
// - Prefer tests of states to tests of interaction
// - Use test doubles if (but only if) a dependency "launches a missile"
// - (These rules assume that the code allows such tests)

// %% [markdown]
//
// ### Why test observable behavior and not implementation?
//
// Observable behavior
// -  is easier to understand
// -  is more stable than implementation
// -  is closer to customer benefit

// %% [markdown]
//
// ## Test observable behavior, not implementation
//
// - Abstract implementation details as much as possible
//   - Also at unit test level
// - Often different methods test each other
// - This sometimes requires the introduction of additional methods
//     - These methods should be useful for users not only for testing
//     - Often "abstract state" of objects
//     - **Do not** simply make the concrete state public.

// %%
#include <vector>

// %%
class Stack
{
private:
    std::vector<int> _items;

public:
    void push(int new_item) { _items.push_back(new_item); }

    int pop();

    // Good extension: useful, doesn't expose implementation
    int size() const { return _items.size(); }

    // Bad extension: exposes implementation
    std::vector<int>& get_items() { return _items; }
};

// %%
int Stack::pop()
{
    if (_items.empty())
    {
        throw std::out_of_range("Stack is empty");
    }
    int val = _items.back();
    _items.pop_back();
    return val;
}

// %% [markdown]
//
// ### Tests when only `push()` and `pop()` are available

// %%
void test_stack_1()
{
    Stack s;
    s.push(5);
    check(s.pop() == 5);
}

// %%
test_stack_1();

// %%
void test_stack_2()
{
    Stack s;
    s.push(5);
    s.push(10);
    check(s.pop() == 10);
    check(s.pop() == 5);
}

// %%
test_stack_2();

// %%
void test_stack_3()
{
    Stack s;
    try
    {
        s.pop();
        check(false);
    }
    catch (const std::out_of_range&)
    {
        check(true);
    }
}

// %%
test_stack_3();

// %% [markdown]
//
// ## Values > State > Interaction
//
// - More understandable
// - Easier to test
// - Often more stable compared to refactorings
//
// Exception: testing protocols

// %% [markdown]
//
// ### Functions/Values

// %%
int add(int x, int y) { return x + y; }

// %%
check(add(2, 3) == 5);

// %% [markdown]
//
// ### State

// %%
class Adder
{
public:
    void set_x(int x) { x_ = x; }
    void set_y(int y) { y_ = y; }
    void add() { result_ = x_ + y_; }
    int get_result() const { return result_; }

private:
    int x_{0};
    int y_{0};
    int result_{0};
};

// %%
Adder adder;

// %%
adder.set_x(2);
adder.set_y(3);

// %%
adder.add();

// %%
check(adder.get_result() == 5);

// %% [markdown]
//
// ### Side effect/Interaction
//
// - With interface

// %%
class AbstractAdder
{
public:
    virtual void add(int x, int y) = 0;
};

// %%
class InteractionAdder
{
public:
    InteractionAdder(AbstractAdder& adder) : adder_{adder} {}

    void add(int x, int y) { adder_.add(x, y); }

private:
    AbstractAdder& adder_;
};

// %% [markdown]
//
// Test requires mock/spy

// %%
#include <utility>
#include <vector>

// %%
struct AdderSpy : AbstractAdder
{
    std::vector<std::pair<int, int>> calls;
    void add(int x, int y) override { calls.push_back({x, y}); };
};

// %%
AdderSpy spy;

// %%
InteractionAdder interaction_adder{spy};

// %%
interaction_adder.add(2, 3);

// %%
check(spy.calls.size() == 1);

// %%
check(spy.calls[0].first == 2);
check(spy.calls[0].second == 3);

// %% [markdown]
//
// ### Side effect/Interaction
//
// - Without interface

// %%
void add_and_print(int x, int y) { std::cout << x + y << std::endl; }

// %% [markdown]
//
// - See `code/completed/test_examples/fun_state_interact_test.cpp` for
//   the test code

// %% [markdown]
//
// ## How do you write testable code?
//
// - Move from less-testable to more-testable style
//   - Observability (`state_machine.h`)
//   - No global or static data
//   - Immutable data structures (values)
// - Good object-oriented design
//   - High cohesion
//   - Low coupling, management of dependencies
// - Etc.

// %% [markdown]
//
// ## Process
//
// - Iterative approach
//   - Small steps with tests
// - Test-Driven Development (TDD)
//   - Writing tests before code

// %% [markdown]
//
// ## Mini-workshop: Better testability
//
// - How can you write tests for the following functions/classes?
// - How can you improve the following functions/classes to make them more
//   testable?
// - What disadvantages result from this?
//
// **Note:**
// You can also find the examples in `code/starter_kits/testability_sk`.

// %%
#include <iostream>

// %%
int count()
{
    static int c = 0;
    return c++;
}

// %%
for (int i = 0; i < 3; ++i)
{
    std::cout << count() << std::endl;
}

// %%
class Counter
{
public:
    int operator()() { return c_++; }

private:
    int c_{};
};

// %%
Counter counter;

// %%
for (int i = 0; i < 3; ++i)
{
    std::cout << counter() << std::endl;
}

// %%
enum class State
{
    OFF,
    ON
};

// %%
class Switch
{
public:
    void toggle()
    {
        state_ = state_ == State::OFF ? State::ON : State::OFF;
        std::cout << "Switch is " << (state_ == State::OFF ? "OFF" : "ON") << std::endl;
    }

private:
    State state_{State::OFF};
};

// %%
Switch s;

// %%
for (int i = 0; i < 3; ++i)
{
    s.toggle();
}

// %%
class SwitchWithGetter
{
public:
    void toggle()
    {
        state_ = state_ == State::OFF ? State::ON : State::OFF;
        std::cout << "Switch is " << (state_ == State::OFF ? "OFF" : "ON") << std::endl;
    }

    State get_state() const { return state_; }

private:
    State state_{State::OFF};
};

// %%
SwitchWithGetter sg;

// %%
for (int i = 0; i < 3; ++i)
{
    sg.toggle();
}

// %%
std::cout << "Switch is " << (sg.get_state() == State::OFF ? "OFF" : "ON") << std::endl;


// %%
class ObservableSwitch
{
public:
    void toggle()
    {
        state_ = state_ == State::OFF ? State::ON : State::OFF;
        notify(state_);
    }

    void register_observer(std::function<void(State)> f) { observers_.push_back(f); }

private:
    void notify(State s)
    {
        for (auto& f : observers_)
        {
            f(s);
        }
    }

    State state_{State::OFF};
    std::vector<std::function<void(State)>> observers_;
};

// %%
ObservableSwitch os;

// %%
os.register_observer([](State s) {
    std::cout << "Switch is " << (s == State::OFF ? "OFF" : "ON") << std::endl;
});

// %%
for (int i = 0; i < 3; ++i)
{
    os.toggle();
}

// %%
void print_fib(int n)
{
    int a{0};
    int b{1};
    for (int i{0}; i < n; ++i)
    {
        std::cout << "fib(" << i << ") = " << b << std::endl;
        int tmp{a};
        a = b;
        b = tmp + b;
    }
}

// %%
print_fib(5);

// %%
int fib1(int n)
{
    int a{0};
    int b{1};
    for (int i{0}; i < n; ++i)
    {
        int tmp{a};
        a = b;
        b = tmp + b;
    }
    return b;
}

// %%
void print_fib1(int n)
{
    for (int i{0}; i < n; ++i)
    {
        std::cout << "fib(" << i << ") = " << fib1(i) << std::endl;
    }
}

// %%
print_fib1(5);

// %%
void fib_gen(int n, std::function<void(int, int)> f)
{
    int a{0};
    int b{1};
    for (int i{0}; i < n; ++i)
    {
        f(i, b);
        int tmp{a};
        a = b;
        b = tmp + b;
    }
}

// %%
void print_fib2(int n)
{
    fib_gen(n, [](int i, int x) {
        std::cout << "fib(" << i << ") = " << x << std::endl;
    });
}

// %%
print_fib2(5);

// %%

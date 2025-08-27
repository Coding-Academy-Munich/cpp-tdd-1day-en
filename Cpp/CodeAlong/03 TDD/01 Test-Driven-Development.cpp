// -*- coding: utf-8 -*-
// %% [markdown]
//
// <div style="text-align:center; font-size:200%;">
//   <b>Test-Driven-Development</b>
// </div>
// <br/>
// <div style="text-align:center; font-size:120%;">Dr. Matthias Hölzl</div>
// <br/>
// <div style="text-align:center;">Coding-Academy Munich</div>
// <br/>
// <!-- 01 Test-Driven-Development.cpp -->
// <!-- slides/module_410_unit_testing/topic_170_test_driven_development.cpp -->


// %% [markdown]
//
// ## Idea
//
// - Use tests to drive the design and feature development of the program
// - Each new test describes a feature increment of the program
// - (Good testable code is created as a by-product)

// %% [markdown]
//
// ## Problem
//
// How can tests drive the design of the program?

// %% [markdown]
//
// ## Possible answers
//
// - Tests use the functionality and therefore highlight clumsy interfaces
// - Tests enable refactoring

// %% [markdown]
//
// ## Refactoring
//
// - Improve the code structure without changing the behavior
//   - Proceed in small steps
//   - After each step, the code is executable again
// - Objectives:
//   - Improve the code
//   - Improve the design

// %% [markdown]
//
// ## Refactoring and Tests
//
// - Refactoring improves the design of the program in small steps
// - The correctness of these steps is verified by tests

// %% [markdown]
//
// ## So what???
//
// <img src="img/velocity-tests-03.png"
//      style="display:block;margin:auto;width:70%"/>

// %% [markdown]
//
// ## Test-Driven Development
//
// - The goal of TDD is not primarily to achieve high test coverage
// - The goal of TDD is to discover a good design through testing
//   - When writing the tests, one tries to design the interfaces of classes and
//     functions in such a way that it is easy to use
//   - Because all essential parts of the program are protected by tests,
//     one can permanently adapt the design to the current feature set through
//     refactoring

// %% [markdown]
//
// ## The TDD Cycle
// - Write a (minimal) test
//   - The test only tests one new (partial) feature: **Baby Steps**
//   - This test fails
// - Implement the minimal functionality to get the test to work
//   - You don't have to pay attention to clean code or good design
//   - But: **Solve Simply**
// - Improve the code
//   - Remove the dirty constructs introduced in the previous step
//   - Generalize the implementation if there is too much repetition
//   - **This step is not optional!!!**

// %% [markdown]
//
// ## The TDD cycle
//
// - <span style="color: red"><b>Red (failing test)</b></span>
// - <span style="color: green"><b>Green (all tests are green again)</b></span>
// - <span style="color: blue"><b>Clean/Refactor (the code is clean again)</b></span>

// %% [markdown]
//
// ## Baby steps
//
// - The system does not spend hours or days in a state in which it is not buildable,
//   testable or executable
// - This allows you to quickly get feedback from the code with every change
// - Frequent merging and CI becomes possible

// %% [markdown]
//
// ## Why Solve Simply?
//
// - A flexible, generic solution often increases the complexity of the system
// - It is only worthwhile if the flexibility is actually needed
// - Developers usually have a hard time predicting where flexibility/extensibility is
//   needed
// - A flexible, generic solution is often much more difficult to implement than
//   a simple solution for a more specific use case
// - The most obvious flexible, generic solution is often not the cleanest and
//   most maintainable code

// %% [markdown]
//
// ## Assumptions of Solve Simply
// - It is possible to refactor code into a clean, maintainable state without changing
//   functionality
// - It is possible to extend code iteratively and make it more flexible when needed
// - It is easier to carry out the refactoring and iteration steps than to develop
//   the final solution right away
// - These assumptions are only fulfilled if a sufficient number of good unit tests
//   are available

// %% [markdown]
//
// ## Even better: TDD + preparation step
//
// - Refactor the code so that the change becomes easy
//   - This is often not that easy...
//   - If during the refactoring it becomes clear that tests are missing, they are added
// - Do the easy change with the TDD cycle
// - Repeat these steps over and over again

// %% [markdown]
//
// ## Guided Kata: Mars Rover (or Grid World)
//
// - An exercise in TDD that shows how tests can drive the design
// - The important thing is the procedure, not just the final solution
// - Goal: Learn to work incrementally and iteratively!

// %% [markdown]
//
// ## Guided Kata: Mars Rover
//
// We will program a rover that can navigate a grid.
// - The rover has
//   - a position `(x, y)` and
//   - a direction (North, East, South, or West).
// - It can receive a sequence of commands:
//   - `L` (turn left 90 degrees),
//   - `R` (turn right 90 degrees), and
//   - `M` (move forward one grid point).

// %% [markdown]
//
// ## Final Result: Separated Responsibilities
//
// #### Rover
// - Knows its own position and direction.
// - Knows how to turn left or right.
// - Knows how to interpret commands (`L`, `R`, `M`).
// - Delegates the movement calculation to the `Grid`.
//
// ```cpp
// Inside Rover::move()
// position = grid->calculateNextPosition(position, direction);
// ```
//
// #### Grid
// - Knows the world's dimensions (width and height).
// - Knows how to calculate the next position given a current position and
//   direction.
// - Encapsulates the "wrapping" logic.

// %% [markdown]
//
// ## Kata: FizzBuzz
//
// Write a function
// ```cpp
// void fizz_buzz(int n);
// ```
// that outputs the numbers from 1 to `n` on the screen but
//
// - replaces any number divisible by 3 with `fizz`
// - replaces every number divisible by 5 with `buzz`
// - replaces every number divisible by 3 and 5 with `FizzBuzz`
//
// For example, `fizz_buzz(16)` should produce the following output:
//
// ```plaintext
// 1
// 2
// Fizz
// 4
// Buzz
// Fizz
// 7
// 8
// Fizz
// Buzz
// 11
// Fizz
// 13
// 14
// FizzBuzz
// 16
// ```

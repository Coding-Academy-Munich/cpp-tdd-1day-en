// -*- coding: utf-8 -*-
// %% [markdown]
//
// <div style="text-align:center; font-size:200%;">
//   <b>Design Patterns for TDD</b>
// </div>
// <br/>
// <div style="text-align:center; font-size:120%;">Dr. Matthias Hölzl</div>
// <br/>
// <div style="text-align:center;">Coding-Academy Munich</div>
// <br/>
// <!-- 01 Design Patterns for TDD.cpp -->
// <!-- slides/module_410_unit_testing/topic_200_tdd_design_patterns.cpp -->


// %% [markdown]
//
// <img src="img/emergent-design-tdd-car.png"
//      style="display:block;margin:auto;width:100%"/>

// %% [markdown]
// ## Principles for Emergent Design
//
// - Iteratively improving design through tests and refactoring.
// - Key techniques:
//   - **YAGNI** (You Ain't Gonna Need It)
//   - **DRY** (Don't Repeat Yourself)
//   - **Last Responsible Moment**
//   - **Simple Design**

// %% [markdown]
//
// ### YAGNI (You Ain't Gonna Need It)
//
// - Only implement functionality
//   - when you **actually** need it,
//   - not when you **might** need it.

// %% [markdown]
//
// ### YAGNI (You Ain't Gonna Need It)
//
// - **What it is:**
//   - A filter against accidental complexity.
// - **Why it matters:**
//   - Every feature has costs (development, maintenance, cognitive load).
//   - YAGNI maximizes the amount of work that is *not* done.
// - **Relation to TDD:**
//   - The TDD cycle enforces YAGNI.
//   - Write code only for failing tests.
//   - Write tests only for real requirements.

// %% [markdown]
//
// ### DRY (Don't Repeat Yourself)
//
// Every piece of knowledge must have a single, unambiguous, authoritative
// representation within a system.

// %% [markdown]
//
// ### DRY (Don't Repeat Yourself)
//
// - **What it is:**
//   - A principle for eliminating duplication in logic and structure.
// - **Why it matters:**
//   - Duplicated code leads to maintenance nightmares.
//   - Each change must be made in multiple places.
// - **Relation to TDD:**
//   - **Refactor** phase: DRY as a criterion for good design.
//   - **Triangulation**: Use tests to identify and eliminate duplication.

// %% [markdown]
//
// ### Triangulation
//
// - Use tests to drive design.
// - Multiple tests for similar behavior to understand the structure of the
//   code.

// %%
#include "check.h"
#include <vector>
#include <numeric>
#include <iostream>

// %% [markdown]
//
// Test:
// ```cpp
// check(sum({}) == 0);
// ```
//
// Code:
// ```cpp
// int sum(const std::vector<int>& numbers)
// {
//     return 0;
// }
// ```

// %% [markdown]
//
// Test:
// ```cpp
// check(sum({}) == 0);
// check(sum({1}) == 1);
// ```
//
// Code:
// ```cpp
// int sum(const std::vector<int>& numbers)
// {
//     if (numbers.empty())
//         return 0;
//     return numbers[0];
// }
// ```

// %% [markdown]
//
// Test:
// ```cpp
// check(sum({}) == 0);
// check(sum({1}) == 1);
// check(sum({1, 2, 3}) == 6);
// ```


// %% [markdown]
//
// Code:
// ```cpp
// int sum(const std::vector<int>& numbers)
// {
//     if (numbers.empty())
//         return 0;
//     if (numbers.size() == 1)
//         return numbers[0];
//     return numbers[0] + sum(std::vector<int>(numbers.begin() + 1, numbers.end()));
// }
// ```

// %%
int sum(const std::vector<int>& numbers)
{
    return std::accumulate(numbers.begin(), numbers.end(), 0);
}

// %%
void test_sum()
{
    check(sum({}) == 0);
    check(sum({1}) == 1);
    check(sum({1, 2, 3}) == 6);
}

// %%

// %% [markdown]
//
// ### Last Responsible Moment (LRM)
//
// Make decisions with far-reaching consequences as late as possible.

// %% [markdown]
//
// ### Last Responsible Moment (LRM)
//
// - **What it is:**
//   - A risk mitigation strategy.
// - **Why it matters:**
//   - When we make decisions early, we have little information.
//   - Errors are more likely.
//   - Some decisions are hard to reverse ("one-way doors," e.g., framework
//     choice).
//   - Decisions often become more expensive the later they are made.
// - **Relation to TDD:**
//   - Evolutionary architecture allows for later decisions.

// %% [markdown]
//
// ### Simple Design according to Kent Beck
//
// Prioritized rules for good design:
//
// 1. **Passes all the tests:**
//    - Correctness is non-negotiable.
// 2. **Reveals the intention:**
//    - Code must be understandable to humans. Clear names, logical structure.
// 3. **No duplication:**
//    - Apply DRY rigorously.
// 4. **Fewest elements:**
//    - Do not add complexity that is not required by the first three rules.
//    - Combats over-engineering.

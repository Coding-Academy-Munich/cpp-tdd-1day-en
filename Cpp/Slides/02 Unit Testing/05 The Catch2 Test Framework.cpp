// -*- coding: utf-8 -*-
// %% [markdown]
//
// <div style="text-align:center; font-size:200%;">
//   <b>The Catch2 Test Framework</b>
// </div>
// <br/>
// <div style="text-align:center; font-size:120%;">Dr. Matthias Hölzl</div>
// <br/>
// <div style="text-align:center;">Coding-Academy Munich</div>
// <br/>
// <!-- 05 The Catch2 Test Framework.cpp -->
// <!-- slides/module_410_unit_testing/topic_150_catch2.cpp -->


// %% [markdown]
//
// ## What is Catch2?
//
// - Catch2 is a modern test framework for C++
// - Open-source
// - Easy to integrate into projects
// - Many features
// - Different structure than xUnit test frameworks

// %% [markdown]
//
// ## Features of Catch2
//
// - Management of tests and test suites
// - Assertion library for test cases
// - Execution of tests (Test Runner)
// - Basic performance tests

// %% [markdown]
//
// ## A simple test with Catch2
//
// ### CMake project
//
// ```cmake
// # ...
// add_executable(catch2_basics catch2_basics.cpp)
// target_link_libraries(catch2_basics Catch2WithMain)
// # ...
// ```

// %% [markdown]
//
// ## The test file
//
// - `TEST_CASE` macro to define tests
// - `REQUIRE` and `CHECK` macros to check conditions
//   - `REQUIRE` stops the test on failure
//   - `CHECK` continues the test
// - `REQUIRE_FALSE` and `CHECK_FALSE` to negate conditions
//
// See `code/starter_kits/catch2_intro/basics/catch2_basics.cpp`

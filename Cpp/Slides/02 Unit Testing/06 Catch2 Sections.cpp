// -*- coding: utf-8 -*-
// %% [markdown]
//
// <div style="text-align:center; font-size:200%;">
//   <b>Catch2 Sections</b>
// </div>
// <br/>
// <div style="text-align:center; font-size:120%;">Dr. Matthias Hölzl</div>
// <br/>
// <div style="text-align:center;">Coding-Academy Munich</div>
// <br/>
// <!-- 06 Catch2 Sections.cpp -->
// <!-- slides/module_410_unit_testing/topic_152_catch2_sections.cpp -->


// %% [markdown]
//
// ## Macros
//
// - `TEST_CASE` macro to define tests
// - `REQUIRE` and `CHECK` macros to check conditions
//   - `REQUIRE` stops the test on failure
//   - `CHECK` continues the test
// - `REQUIRE_FALSE` and `CHECK_FALSE` to negate conditions

// %% [markdown]
//
// ## Sections
//
// - `TEST_CASE` can
//   - group multiple tests together
//   - provide common state for the tests
// - `SECTION` macro for grouping tests
//   - Sections can be nested
//
// See `code/starter_kits/catch2_intro/leap_year/`

// %% [markdown]
//
// ## Workshop: Catch2 Basics
//
// In the last videos, we wrote exemplary tests for a very simple online shopping
// system without using a test framework.
//
// In the folder `code/starter_kits/catch2_intro/order/` you will find a slightly
// extended version of this system.
//
// Write tests with Catch2 for this system.
//
// Evaluate the tests based on the criteria we discussed in the last videos.

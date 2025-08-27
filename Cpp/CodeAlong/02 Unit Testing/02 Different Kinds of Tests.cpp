// -*- coding: utf-8 -*-
// %% [markdown]
//
// <div style="text-align:center; font-size:200%;">
//   <b>Different Kinds of Tests</b>
// </div>
// <br/>
// <div style="text-align:center; font-size:120%;">Dr. Matthias Hölzl</div>
// <br/>
// <div style="text-align:center;">Coding-Academy Munich</div>
// <br/>
// <!-- 02 Different Kinds of Tests.cpp -->
// <!-- slides/module_410_unit_testing/topic_120_test_classification.cpp -->


// %% [markdown]
//
// ### By size of the system under test (SuT)
//
// - Unit tests:
//   - Test individual methods or classes,
//   - Typically isolated
// - Component/integration tests:
//   - Test individual components in isolation
// - End-to-end/system tests:
//   - Test the complete system.

// %% [markdown]
//
// ### By focus (test quadrants)
//
// <img src="img/testing-styles.png"
//      alt="Velocity vs. Tests 1"
//      style="width: 75%; margin-left: auto; margin-right: auto;"/>


// %% [markdown]
//
// ## Other classifications/names/types of tests
//
// - Performance tests
//   - Load tests, stress tests, spike tests, ...
// - Usability tests (usability tests)
//   - How well can users work with the system?

// %% [markdown]
//
// ## Regression tests
//
// - Tests that test bugs that have already been fixed
// - Prevent the re-introduction of errors

// %% [markdown]
//
// ## White Box vs. Black Box
//
// - How much knowledge about the system do the testers have?

// %% [markdown]
//
// ## White-Box Tests
//
// - Also called glass box or structural testing
// - Testers can access the
//   - design and
//   - implementation of the system

// %% [markdown]
//
// ## Black-Box Tests
//
// - Testers have no access to system internals
// - Test the system behavior against specification
// - (Classical) fuzzing is automated black-box testing

// %% [markdown]
//
// ## Tip: White-Box vs. Black-Box Tests
//
// - Write tests as black-box tests
// - Evaluate them as white-box tests

// -*- coding: utf-8 -*-
// %% [markdown]
//
// <div style="text-align:center; font-size:200%;">
//   <b>Introduction to Testing</b>
// </div>
// <br/>
// <div style="text-align:center; font-size:120%;">Dr. Matthias Hölzl</div>
// <br/>
// <div style="text-align:center;">Coding-Academy Munich</div>
// <br/>
// <!-- 01 Introduction to Testing.cpp -->
// <!-- slides/module_410_unit_testing/topic_110_testing_intro_combined.cpp -->


// %% [markdown]
//
// # Why do we write tests?
//
// - Do you write tests?
// - Why/why not?
// - How many?
// - What advantages do your tests bring you?
// - What difficulties do you have with them?

// %% [markdown]
//
// - Avoiding errors/regressions
// - Regulations (ISO 26262, DO-178C, ...)
// - Documentation
// - **Driving/validating the design**
// - **Enabling refactoring $\Rightarrow$ constant speed**
// - ...

// %% [markdown]
//
// <img src="img/velocity-tests-01.png"
//      alt="Velocity vs. Tests 1"
//      style="width: 75%; margin-left: auto; margin-right: auto;"/>

// %% [markdown]
//
// <img src="img/velocity-tests-02.png"
//      alt="Velocity vs. Tests 2"
//      style="width: 75%; margin-left: auto; margin-right: auto;"/>

// %% [markdown]
//
// <img src="img/velocity-tests-03.png"
//      alt="Velocity vs. Tests 3"
//      style="width: 75%; margin-left: auto; margin-right: auto;"/>

// %% [markdown]
//
// - Tests are code
// - Code is a liability, not an asset!
// - Tests should bring more value than they cost

// %% [markdown]
//
// ## Classification of Tests
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
// ## Other Types of Tests
//
// - Performance tests
//   - Load tests, stress tests, spike tests, ...
// - Usability tests (usability tests)
//   - How well can users work with the system?
// - ...

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
// - White Box:
//   - Specification
//   - Design
//   - Implementation
// - Black Box:
//   - Specification

// %% [markdown]
//
// ## Tip: White-Box vs. Black-Box Tests
//
// - Write tests as black-box tests
// - Evaluate them as white-box tests


// %% [markdown]
//
// ## Good Tests vs. Bad Tests
//
// <img src="img/velocity-tests-03.png"
//      alt="Velocity vs. Tests 3"
//      style="width: 75%; margin-left: auto; margin-right: auto;"/>

// %% [markdown]
//
// ## Properties of a good test
//
// <ul>
// <li class="fragment">Shows many errors/regressions in the Code</li>
// <li class="fragment">Identifies the error location precisely</li>
// <li class="fragment">Is robust, easy to maintain and understand</li>
// <li class="fragment"><b>Is insensitive to refactoring</b></li>
// <li class="fragment">Gives fast feedback</li>
// <li class="fragment">Is deterministic</li>
// </ul>
//
// <p class="fragment">
//   Unfortunately, these properties are often in conflict with each
//   other!
// </p>

// %% [markdown]
//
// # Unit Tests

// %% [markdown]
//
// ## What is a unit test?
//
// <ul>
//   <li class="fragment"> Tests a small piece of code (a "unit")</li>
//   <li class="fragment"> Runs quickly</li>
//   <li class="fragment"> Is isolated</li>
// </ul>

// %% [markdown]
//
// ## Properties of (good) Unit Tests
//
// <ul>
// <li class="fragment" style="color: red;">Shows many errors/regressions in the Code</li>
// <li class="fragment" style="color: blue;">Identifies the error location precisely</li>
// <li class="fragment" style="color: green;">Is robust, easy to maintain and understand</li>
// <li class="fragment" style="color: green;"><b>Is insensitive to refactoring</b></li>
// <li class="fragment" style="color: green;">Gives fast feedback</li>
// <li class="fragment" style="color: green;">Is deterministic</li>
// </ul>
//
// <p class="fragment">
//   Unit tests provide fast feedback, but find (per test) only a few errors
// </p>

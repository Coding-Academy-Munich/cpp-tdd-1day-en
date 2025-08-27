// -*- coding: utf-8 -*-
// %% [markdown]
//
// <div style="text-align:center; font-size:200%;">
//   <b>Code Smells</b>
// </div>
// <br/>
// <div style="text-align:center; font-size:120%;">Dr. Matthias Hölzl</div>
// <br/>
// <div style="text-align:center;">Coding-Academy Munich</div>
// <br/>
// <!-- 03 Code Smells.cpp -->
// <!-- slides/module_550_refactoring/topic_150_code_smells.cpp -->


// %% [markdown]
//
// # What are Code Smells?
//
// Code smells are hints that we have bad code and should refactor.

// %% [markdown]
//
// ## Code Smells
//
// - Mysterious Name
//   - Names obfuscate instead of clarifying
// - Duplicated Code
//   - Multiple occurrences of identical or similar code
// - Long Function
// - Long Parameter List
// - Global Data
// - Mutable Data
//   - Encapsulating access to mutable data
//   - Command-Query Separation


// %% [markdown]
//
// - Divergent Change
//   - One module changes for many different changes
// - Shotgun Surgery
//   - Even simple changes impact many modules
// - Feature Envy
//   - A function communicates with many functions from another module
// - Data Clumps
//   - The same data items appear together in many places without being grouped
//     into a class

// %% [markdown]
//
// - Primitive Obsession
//   - Extensive use of built-in types instead of meaningful classes
// - Repeated Switches
//   - Switches over the same data in many places
// - Loops
//   - Can often be replaced by pipelines
// - Lazy Element
//   - Program elements that do not add value

// %% [markdown]
//
// - Speculative Generality
//   - Flexibility that is not currently needed
// - Temporary Field
//   - Attributes that are only used/valid temporarily
// - Message Chains
//   - Long chains of getter calls or temp variables
// - Middle Man
//   - Most methods of a class only delegate to another class

// %% [markdown]
//
// - Insider Trading
//   - Classes have too much knowledge about the internals of other classes
// - Large Class
//   - Too many responsibilities
// - Alternative Classes with Different Interfaces
//   - Classes that should be interchangeable but are not
// - Data Class
//   - Classes that only have getters and setters
// - Refused Bequest
//   - Subclasses inherit functionality that they do not need
// - Comments
//   - If they are needed because the code is bad

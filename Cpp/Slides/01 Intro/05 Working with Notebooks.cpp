// -*- coding: utf-8 -*-
// %% [markdown]
//
// <div style="text-align:center; font-size:200%;">
//   <b>Working with Notebooks</b>
// </div>
// <br/>
// <div style="text-align:center; font-size:120%;">Dr. Matthias Hölzl</div>
// <br/>
// <div style="text-align:center;">Coding-Academy Munich</div>
// <br/>
// <!-- 05 Working with Notebooks.cpp -->
// <!-- slides/module_110_introduction/topic_180_working_with_notebooks.cpp -->
//
//

// %% [markdown]
//
// # Starting the Docker container
//
// ```bash
// docker ps --all  # Show containers
// docker start <container-name>
// ```

// %% [markdown]
//
// # Notebooks
//
// - Notebooks allow interactive evaluation of code and text
// - This way of working is not so common in C++
// - But it is very convenient for training courses


// %% [markdown]
//
// ## Working with notebooks
//
// - The notebook server shows us a list of files in the current directory
// - By clicking on a notebook file, we can open it
// - Notebooks are divided into cells
// - Cells can contain either text or C++ code
// - Unlike C++ programs, cells can contain expressions
// - When running the cell, the expressions are evaluated and the result is
//   displayed

// %%
#include <iostream>

// %%
std::cout << 123;

// %%
std::cout << 17 + 4;

// %% [markdown]
//
// - Cells can also contain statements, e.g. function definitions
// - When executing a cell that defines a function, the function is available for
//   the rest of the notebook

// %%
#include <iostream>

void say_hello(const std::string& name) {
    std::cout << "Hello " << name << "!\n";
}

// %%
say_hello("World");

// %%
say_hello("you");

// %% [markdown]
//
// - The same applies to structs and classes:

// %%
struct Point {
    int x;
    int y;
};

// %%
Point p{1, 2};

// %%
std::cout << p.x;

// %%
std::cout << p.y;

// %% [markdown]
//
// - There are two modes: command and edit mode (`Esc` / `Enter`)
// - Some keyboard shortcuts:
//   - `Ctrl`-`Enter`
//   - `Shift`-`Enter`
//   - (`Tab`)
//   - (`Shift-Tab`)

// %%
std::cout << 123;

// %%
std::cout << 17 + 4;

// %%
int answer{42};

// %%
std::cout << answer;

// %%
std::cout << answer;

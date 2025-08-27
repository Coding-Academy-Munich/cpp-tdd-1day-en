// -*- coding: utf-8 -*-
// %% [markdown]
//
// <div style="text-align:center; font-size:200%;">
//   <b>Visual Studio Code</b>
// </div>
// <br/>
// <div style="text-align:center; font-size:120%;">Dr. Matthias Hölzl</div>
// <br/>
// <div style="text-align:center;">Coding-Academy Munich</div>
// <br/>
// <!-- 03 Visual Studio Code.cpp -->
// <!-- slides/module_110_introduction/topic_134_vscode.cpp -->


// %% [markdown]
//
// - Install the following extensions in VS Code:
//   - C/C++ (`ms-vscode.cpptools`)
//   - C/C++ Extension Pack (`ms-vscode.cpptools-extension-pack`)
//   - CMake Tools (`ms-vscode.cmake-tools`)

// %% [markdown]
//
// - Open the project:
//   - `File` $\rightarrow$ `Open Folder...` $\rightarrow$ select `code` folder
//   - Dialog: "Multiple Visual Studio Projects": select "Do not Load any"
// - Select CMake Preset:
// - `x64 Debug` or `x64 Release` for 64-bit-Windows-Systems
// - `x86 Debug` or `x86 Release` for 32-bit-Windows-Systems
// - `Linux GCC` or `Linux Clang` for Linux-Systems
// - `MacOS Debug` for MacOS-Systems

// %% [markdown]
//
// - If necessary, Select the top-level `CMakeLists.txt` file
// - If necessary, Command-Palette: select `CMake: Configure` or `CMake:
//   Delete Cache and Reconfigure` (`Ctrl+Shift+P`)
// - Select `code` as active `cmake` project
// - Select build and launch target
// - More information: [Visual Studio Code Documentation](https://code.visualstudio.com/docs/languages/cpp)

// %% [markdown]
//
// ## Some Targets
//
// - `hello_world`: Hello-World program to test the build process
// - `hello_world_sk`: Hello-World starter kit
// - `blocks_sk`: Refactoring workshop with graphical output
//   - Final workshop for refactorings
//   - Uses [raylib](https://github.com/raysan5/raylib)
//   - Please let me know if the example causes problems when compiling
//   - Then we can choose a different workshop


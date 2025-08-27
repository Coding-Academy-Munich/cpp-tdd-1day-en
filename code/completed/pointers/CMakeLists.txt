cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

add_library("pointers_lib")

target_sources("pointers_lib"
        PUBLIC
        "include/pointers.hpp" "include/array_dangers.hpp" "include/utils.hpp" "include/shapes.hpp")

target_sources("pointers_lib"
        PRIVATE
        "src/pointers.cpp" "src/array_dangers.cpp" "src/shapes.cpp")

target_include_directories("pointers_lib"
        PUBLIC
        "include")

target_link_libraries("pointers_lib"
        "GSL")


add_executable("pointers")

target_sources("pointers" PRIVATE
        "src/pointers_main.cpp")

target_link_libraries("pointers"
        "GSL"
        "pointers_lib")

add_subdirectory(test)

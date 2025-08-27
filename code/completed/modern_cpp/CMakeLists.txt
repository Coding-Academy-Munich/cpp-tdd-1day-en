cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

add_library("modern_cpp_lib")

target_sources("modern_cpp_lib"
        PUBLIC
        "include/modern_cpp.hpp")

target_sources("modern_cpp_lib"
        PRIVATE
        "src/modern_cpp.cpp")

target_include_directories("modern_cpp_lib"
        PUBLIC
        "include")

target_link_libraries("modern_cpp_lib"
        "GSL")


add_executable("modern_cpp")

target_sources("modern_cpp" PRIVATE
        "src/modern_cpp_main.cpp")

target_link_libraries("modern_cpp"
        "GSL"
        "modern_cpp_lib")

add_subdirectory(test)

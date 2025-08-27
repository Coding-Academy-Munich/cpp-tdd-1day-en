cmake_minimum_required(VERSION 3.20)
project(MemoryAndPolymorphism)

set(CMAKE_CXX_STANDARD 20)
set(MEMORY_SOURCES
        "src/memory_main.cpp"
        "src/print_memory_layout.cpp"
        "include/print_memory_layout.hpp"
        "include/polymorphic_array.hpp")

option(ASAN_ENABLED "Build all targets with AddressSanitizer" OFF)

add_executable(pam_simple "src/simple_inheritance_main.cpp" "include/simple_inheritance.hpp")
target_link_libraries(pam_simple "GSL")
target_include_directories(pam_simple PUBLIC "include")

add_executable(pam_memory ${MEMORY_SOURCES})
target_link_libraries(pam_memory "GSL")
target_include_directories(pam_memory PUBLIC "include")

add_executable(pam_polymorphism "src/polymorphism_main.cpp" "include/animal.hpp" "include/dog.hpp" "include/cat.hpp")
target_link_libraries(pam_polymorphism "GSL")
target_include_directories(pam_polymorphism PUBLIC "include")

add_executable(pam_copy_move "src/copy_move_main.cpp" "include/animal.hpp" "include/dog.hpp" "include/cat.hpp")
target_link_libraries(pam_copy_move "GSL")
target_include_directories(pam_copy_move PUBLIC "include")

add_library(pam_raii_lib INTERFACE "include/raii.hpp")
target_include_directories(pam_raii_lib INTERFACE "include")

add_executable(pam_raii_main "src/raii_main.cpp" "include/animal.hpp" "include/dog.hpp" "include/cat.hpp")
target_link_libraries(pam_raii_main pam_raii_lib "GSL")
target_include_directories(pam_raii_main PUBLIC "include")

add_executable(pam_raii_test "test/raii_test.cpp" "include/animal.hpp" "include/dog.hpp" "include/cat.hpp")
target_link_libraries(pam_raii_test "Catch2WithMain" "GSL")
target_include_directories(pam_raii_test PUBLIC "include")


if (ASAN_ENABLED)
    if (MSVC)
        target_compile_options(pam_simple PUBLIC /fsanitize=address)
        target_compile_options(pam_memory PUBLIC /fsanitize=address)
        target_compile_options(pam_polymorphism PUBLIC /fsanitize=address)
        target_compile_options(pam_copy_move PUBLIC /fsanitize=address)
    else ()
        target_compile_options(pam_simple PUBLIC -fsanitize=address)
        target_link_options(pam_simple PUBLIC -fsanitize=address)
        target_compile_options(pam_memory PUBLIC -fsanitize=address)
        target_link_options(pam_memory PUBLIC -fsanitize=address)
        target_compile_options(pam_polymorphism PUBLIC -fsanitize=address)
        target_link_options(pam_polymorphism PUBLIC -fsanitize=address)
        target_compile_options(pam_copy_move PUBLIC -fsanitize=address)
        target_link_options(pam_copy_move PUBLIC -fsanitize=address)
    endif ()
endif ()

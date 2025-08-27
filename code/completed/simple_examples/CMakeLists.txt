add_library("simple_examples_lib")

target_sources("simple_examples_lib"
        PUBLIC
        "include/simple_examples.hpp")

target_sources("simple_examples_lib"
        PRIVATE
        "src/simple_examples.cpp")

target_include_directories("simple_examples_lib"
        PUBLIC
        "include")

target_link_libraries("simple_examples_lib"
        "GSL")


add_executable("simple_examples")

target_sources("simple_examples" PRIVATE
        "src/simple_examples_main.cpp")

target_link_libraries("simple_examples"
        "GSL"
        "simple_examples_lib")

add_subdirectory(test)

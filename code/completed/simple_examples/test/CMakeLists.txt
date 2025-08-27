add_executable("simple_examples_test")

target_sources("simple_examples_test" PRIVATE
        "simple_examples_test.cpp"
)

target_link_libraries("simple_examples_test"
        "Catch2WithMain"
        "simple_examples_lib"
)
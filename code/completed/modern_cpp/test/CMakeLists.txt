add_executable("modern_cpp_test")

target_sources("modern_cpp_test" PRIVATE
        "modern_cpp_test.cpp"
)

target_link_libraries("modern_cpp_test"
        "Catch2WithMain"
        "modern_cpp_lib"
)
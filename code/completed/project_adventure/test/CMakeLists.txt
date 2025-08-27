enable_testing()

add_executable(project_adventure_test test_utils.h
        test_utils.cpp
        acceptance_tests.cpp
        unit_tests_section_1.cpp
        fixtures.cpp
        fixtures.h
)

target_link_libraries(project_adventure_test
        PRIVATE
        project_adventure_lib
        Catch2::Catch2WithMain
)

include(CTest)
add_test(NAME project_adventure_test
        COMMAND project_adventure_test
)

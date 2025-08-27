enable_testing()

add_executable(two_loop_cycle_sk_test acceptance_tests.cpp
        unit_tests.cpp)

target_link_libraries(two_loop_cycle_sk_test
        PRIVATE
        two_loop_cycle_sk_lib
        Catch2::Catch2WithMain
)

include(CTest)
add_test(NAME two_loop_cycle_sk_test
        COMMAND two_loop_cycle_sk_test
)

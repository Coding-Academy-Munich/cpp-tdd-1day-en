enable_testing()

add_executable(vending_machine_sk_test
        chicago_test.cpp
        london_test.cpp
)

target_link_libraries(vending_machine_sk_test
        PRIVATE
        vending_machine_sk_lib
        Catch2::Catch2WithMain
)

include(CTest)
add_test(NAME vending_machine_sk_test
        COMMAND vending_machine_sk_test
)

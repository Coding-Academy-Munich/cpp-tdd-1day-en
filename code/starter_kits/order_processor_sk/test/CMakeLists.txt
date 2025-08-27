enable_testing()

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/orders.txt
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/../orders.txt
        ${CMAKE_CURRENT_BINARY_DIR}/orders.txt
    # This command depends on the original file
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../orders.txt
    COMMENT "Copying orders.txt to binary directory"
)

add_custom_target(copy_orders_for_tests_sk ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/orders.txt
)


add_executable(non_testable_order_processor_test_sk non_testable_order_processor_test.cpp)
target_link_libraries(non_testable_order_processor_test_sk
    PRIVATE
	non_testable_order_processor_sk_lib
    Catch2::Catch2WithMain
)
add_dependencies(non_testable_order_processor_test_sk
    copy_orders_for_tests_sk
)

include(CTest)
add_test(NAME non_testable_order_processor_test_sk
         COMMAND non_testable_order_processor_test_sk
)

add_executable(testable_order_processor_test_sk testable_order_processor_test.cpp)
target_link_libraries(testable_order_processor_test_sk
    PRIVATE
	testable_order_processor_sk_lib
    Catch2::Catch2WithMain
)
add_dependencies(testable_order_processor_test_sk
    copy_orders_for_tests_sk
)

include(CTest)
add_test(NAME testable_order_processor_test_sk
         COMMAND testable_order_processor_test_sk
)

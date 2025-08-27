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

add_custom_target(copy_orders_for_tests ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/orders.txt
)


add_executable(non_testable_order_processor_test non_testable_order_processor_test.cpp)
target_link_libraries(non_testable_order_processor_test
    PRIVATE
	non_testable_order_processor_lib
    Catch2::Catch2WithMain
)
add_dependencies(non_testable_order_processor_test
    copy_orders_for_tests
)

include(CTest)
add_test(NAME non_testable_order_processor_test
         COMMAND non_testable_order_processor_test
)

add_executable(testable_order_processor_test testable_order_processor_test.cpp)
target_link_libraries(testable_order_processor_test
    PRIVATE
	testable_order_processor_lib
    Catch2::Catch2WithMain
)
add_dependencies(testable_order_processor_test
    copy_orders_for_tests
)

include(CTest)
add_test(NAME testable_order_processor_test
         COMMAND testable_order_processor_test
)

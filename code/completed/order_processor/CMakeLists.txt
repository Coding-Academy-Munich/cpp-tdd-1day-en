set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
add_subdirectory(test)

add_executable(order_processor main.cpp)
target_link_libraries(order_processor
    PRIVATE
    non_testable_order_processor_lib
    testable_order_processor_lib)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/orders.txt
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/orders.txt
        ${CMAKE_CURRENT_BINARY_DIR}/orders.txt
    # This command depends on the original file
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/orders.txt
    COMMENT "Copying orders.txt to binary directory"
)

add_custom_target(copy_orders ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/orders.txt
)

add_dependencies(order_processor copy_orders)

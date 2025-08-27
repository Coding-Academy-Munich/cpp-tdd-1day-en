add_library(
    non_testable_order_processor_lib
    non_testable_order_processor.cpp
    non_testable_order_processor.h
)
target_include_directories(non_testable_order_processor_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(
    testable_order_processor_lib
    testable_order_processor.cpp
    testable_order_processor.h
)
target_include_directories(testable_order_processor_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

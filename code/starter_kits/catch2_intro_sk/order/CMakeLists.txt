add_library(order_lib_sk order.h order.cpp item.h item.cpp)

add_executable(order_test_sk
        item_test.cpp
        order_test.cpp
)
target_link_libraries(order_test_sk order_lib_sk Catch2WithMain)

add_executable(order_scenario_test_sk
        order_scenario_test.cpp
        item_scenario_test.cpp
)
target_link_libraries(order_scenario_test_sk order_lib_sk Catch2WithMain)

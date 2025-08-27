add_library(order_lib order.h order.cpp item.h item.cpp)

add_executable(order_test
        item_test.cpp
        order_test.cpp
)
target_link_libraries(order_test order_lib Catch2WithMain)

add_executable(order_scenario_test
        order_scenario_test.cpp
        item_scenario_test.cpp
)
target_link_libraries(order_scenario_test order_lib Catch2WithMain)

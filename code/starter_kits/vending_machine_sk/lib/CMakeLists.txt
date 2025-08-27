add_library(vending_machine_sk_lib
        chicago/vending_machine.cpp
        chicago/vending_machine.h
        chicago/item.cpp
        chicago/item.h
        chicago/order.h
)
target_include_directories(vending_machine_sk_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

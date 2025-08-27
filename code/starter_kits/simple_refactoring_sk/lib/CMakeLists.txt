add_library(simple_refactoring_sk_lib
        orders.cpp
        orders.h
)
target_include_directories(simple_refactoring_sk_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

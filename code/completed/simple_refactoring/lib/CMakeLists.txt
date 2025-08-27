add_library(simple_refactoring_lib
        orders.cpp
        orders.h
)
target_include_directories(simple_refactoring_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

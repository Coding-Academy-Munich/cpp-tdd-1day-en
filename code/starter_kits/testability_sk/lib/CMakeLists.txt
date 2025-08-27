add_library(testability_sk_lib
        testability_sk.cpp
        testability_sk.h
)
target_include_directories(testability_sk_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

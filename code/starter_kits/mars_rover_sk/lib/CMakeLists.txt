add_library(mars_rover_sk_lib
        mars_rover_sk.cpp
        mars_rover_sk.h
)
target_include_directories(mars_rover_sk_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

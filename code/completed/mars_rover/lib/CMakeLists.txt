add_library(mars_rover_lib
        mars_rover.cpp
        mars_rover.h
)
target_include_directories(mars_rover_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

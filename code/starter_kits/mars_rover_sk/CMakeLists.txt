SET(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
add_subdirectory(test)

add_executable(mars_rover_sk main.cpp)
target_link_libraries(mars_rover_sk PRIVATE mars_rover_sk_lib)

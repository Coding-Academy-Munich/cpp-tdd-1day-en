SET(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
add_subdirectory(test)

add_executable(two_loop_cycle main.cpp)
target_link_libraries(two_loop_cycle PRIVATE two_loop_cycle_lib)

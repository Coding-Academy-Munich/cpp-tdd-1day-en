SET(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
add_subdirectory(test)

add_executable(two_loop_cycle_sk main.cpp)
target_link_libraries(two_loop_cycle_sk PRIVATE two_loop_cycle_sk_lib)

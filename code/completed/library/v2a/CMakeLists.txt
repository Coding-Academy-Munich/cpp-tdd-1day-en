cmake_minimum_required(VERSION 3.20)

add_subdirectory(lib)
add_subdirectory(test)

add_executable(library_v2a main.cpp)
target_link_libraries(library_v2a PRIVATE library_data)
target_link_libraries(library_v2a PRIVATE library_v2a_lib)

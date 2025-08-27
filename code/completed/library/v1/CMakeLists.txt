cmake_minimum_required(VERSION 3.20)

add_subdirectory(lib)
add_subdirectory(test)

add_executable(library_v1 main.cpp)
target_link_libraries(library_v1 PRIVATE library_data)
target_link_libraries(library_v1 PRIVATE library_v1_lib)

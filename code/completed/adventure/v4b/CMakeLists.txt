cmake_minimum_required(VERSION 3.20)
project(adventure_v4b)

add_subdirectory(lib)
add_subdirectory(test)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE adventure_v4b_lib)
target_link_libraries(${PROJECT_NAME} PRIVATE adventure_data)

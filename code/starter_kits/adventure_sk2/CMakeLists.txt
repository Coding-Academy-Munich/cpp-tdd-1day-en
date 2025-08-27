cmake_minimum_required(VERSION 3.20)
project(adventure_sk2)

add_subdirectory(data)
add_subdirectory(lib)
add_subdirectory(test)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE adventure_sk2_data)
target_link_libraries(${PROJECT_NAME} PRIVATE adventure_sk2_lib)

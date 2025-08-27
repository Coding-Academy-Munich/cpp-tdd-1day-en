cmake_minimum_required(VERSION 3.20)
project(adventure_v3c_test)

add_executable(${PROJECT_NAME} TestLocation.cpp
        TestWorld.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE adventure_v3c_lib)
target_link_libraries(${PROJECT_NAME} PRIVATE adventure_data)
target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2WithMain)

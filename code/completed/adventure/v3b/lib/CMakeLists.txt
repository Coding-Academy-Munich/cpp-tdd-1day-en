cmake_minimum_required(VERSION 3.20)
project(adventure_v3b_lib)

add_library(${PROJECT_NAME} Location.cpp Location.h World.cpp World.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE adventure_data)

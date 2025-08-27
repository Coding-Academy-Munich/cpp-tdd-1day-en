cmake_minimum_required(VERSION 3.20)
project(library_sk_lib)

add_library(${PROJECT_NAME} DeleteMe.cpp DeleteMe.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE library_sk_data)

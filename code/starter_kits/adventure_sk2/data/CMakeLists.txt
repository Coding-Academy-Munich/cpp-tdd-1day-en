cmake_minimum_required(VERSION 3.20)
project(adventure_sk2_data)

add_library(${PROJECT_NAME} LocationData.cpp LocationData.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

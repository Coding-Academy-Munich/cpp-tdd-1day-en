cmake_minimum_required(VERSION 3.20)
project(adventure_data)

add_library(adventure_data LocationData.cpp LocationData.h)
target_include_directories(adventure_data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

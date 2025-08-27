cmake_minimum_required(VERSION 3.20)

add_library(library_data BookData.cpp BookData.h)
target_include_directories(library_data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

cmake_minimum_required(VERSION 3.20)
project(library_sk_data)

add_library(${PROJECT_NAME} BookData.cpp BookData.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
